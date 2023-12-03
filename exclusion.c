#include "tests.h"
#include <stdio.h>
#include <stdlib.h>

int lecture_fichier_exlusion(tf* tf1,char *nom_fichier){
    FILE* fichier = fopen(nom_fichier,"r");
    if (!fichier){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    int taille;
    int h = 0;
    char actuel;
    while (actuel != EOF){
        actuel = fgetc(fichier);
        int v1;
        int v2;
        if (actuel >= '0' && actuel<= '9') {
            fseek(fichier, -1,SEEK_CUR);
            fscanf(fichier, "%d %d", &v1,&v2);
            h++;
        }
    }
    taille = h;
    h = 0;
    tf1->tableau = (int**)malloc(taille*sizeof(int*));
    for(int i=0;i<taille;i++){
        tf1->tableau[i] = (int*)malloc(2*sizeof(int));
    }
    fseek(fichier, 0, SEEK_SET);
    char actuel1;
    while (actuel1 != EOF){
        actuel1 = fgetc(fichier);
        if (actuel1 >= '0' && actuel1<= '9') {
            fseek(fichier, -1,SEEK_CUR);
            fscanf(fichier, "%d %d", &tf1->tableau[h][0],&tf1->tableau[h][1]);
            printf("\n%d %d",tf1->tableau[h][0],tf1->tableau[h][1]);
            h++;
        }
    }
    fclose(fichier);
    return taille;
}


pSommet* CreerArete(pSommet* sommet,int s1,int s2){
    if(sommet[s1]->arc==NULL){
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;
        return sommet;
    }
    else{
        pArc temp=sommet[s1]->arc;
        while(temp->arc_suivant!=NULL){
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        if(temp->sommet>s2){
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }
        temp->arc_suivant=Newarc;
        return sommet;
    }
}

graphe* CreerGraphe(int ordre){
    graphe * Newgraphe=(graphe*)malloc(sizeof(graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));
    Newgraphe->pstation = (pstation*)malloc(ordre*sizeof(pstation));
    for(int i=0; i<ordre; i++){
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pstation[i]=(pstation)malloc(sizeof(struct station));
        Newgraphe->pSommet[i]->arc=NULL;
    }

    return Newgraphe;
}
int trouver_ordre(int ** tableau,int taille){
    int valeur_grande = 0;
    for(int i=0;i<taille;i++){
        for(int j=0;j<2;j++){
            if(tableau[i][j] > valeur_grande){
                valeur_grande = tableau[i][j];
            }
        }
    }
    return valeur_grande;
}

graphe* creation_graphe(graphe* g){
    char fichier_exclusion[50];
    int taille,ordre;
    printf("\n Nom du fichier exclusion :");
    scanf("%s",fichier_exclusion);
    tf* tf1;
    taille = lecture_fichier_exlusion(tf1,fichier_exclusion);
    ordre = trouver_ordre(tf1->tableau,taille)+1;
    printf("\nordre %d",ordre);
    g = CreerGraphe(ordre);
    g->ordre = ordre;
    printf("\n\n%d",g->ordre);
    for(int i=0;i<taille;i++){
        int s1 = tf1->tableau[i][0];
        int s2 = tf1->tableau[i][1];
        g->pSommet = CreerArete(g->pSommet,s1,s2);
        g->pSommet = CreerArete(g->pSommet,s2,s1);
    }
    return g;
}


int reperage_interdit(pstation machine,int sommet,graphe* g){
    pArc arcc=g->pSommet[sommet]->arc;
    while(arcc != NULL){
        int num = arcc->sommet;
        for(int i=0;i<machine->taille;i++){
            if(num == machine->etape[i]){
                return 0;
            }
        }
        arcc = arcc->arc_suivant;

    }
    return 1;
}

int contrainte_exclusion(graphe* g){
    int nbr_machine=0;
    for(int z=0;z<(g->ordre);z++){
        g->pstation[z]->taille = 0;
        g->pstation[z]->etape = (int*)malloc(g->ordre*sizeof(int));
    }
    printf("\nici");
    for(int i=0;i<(g->ordre);i++){
        int j=0;
        while(reperage_interdit(g->pstation[j],i,g) == 0 && j<nbr_machine){
            j++;
        }
        if(j<nbr_machine){
            g->pstation[j]->etape[g->pstation[j]->taille] = i;
            g->pstation[j]->taille++;
        }
        else{
            nbr_machine++;
            g->pstation[j]->etape[0] = i;
            g->pstation[j]->taille++;
        }
    }

    return nbr_machine;
}

void main_exclusion_simple() {
    graphe* g;
    int station;
    g = creation_graphe(g);
    station = contrainte_exclusion(g);
    printf("\n");
    for(int i=0;i<station;i++){
        printf("\nStation: %d\n",i);
        for(int j=0;j<g->pstation[i]->taille;j++){
            printf("%d ",g->pstation[i]->etape[j]);
        }
    }
    printf("\n\nIl y a besoin de %d station dans cette chaine de production avec la contrainte d'exclusion \n",station);
}
