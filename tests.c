//
// Created by Nathan Gaulle on 20/11/2023.
//

#include "tests.h"
t_sommet ** creerarrete (t_sommet **sommet,int s1,int s2){
    t_arc *arc = malloc(sizeof (t_arc*));
    arc->sommet = s2;
    arc->arc_suivant =  NULL;
    if (sommet[s1]->arc == NULL){
        sommet[s1]->arc = arc;
        return sommet;
    }
    t_arc *actuel = sommet[s1]->arc;
    while (actuel->arc_suivant !=NULL){
        actuel = actuel->arc_suivant;
    }
    actuel->arc_suivant = arc;
    return sommet;
}

t_graphe *lecture (char *file){
    t_graphe *graphe = malloc (sizeof (t_graphe ));
    FILE *fichier = fopen(file,"r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    int orientation;
    int ordre;
    int taille;

    int sommet[50][2];
    int h = 0;
    char actuel;
    while (actuel != EOF){
        actuel = fgetc(fichier);
        if (actuel >= '0' && actuel<= '9') {
            fseek(fichier, -1,SEEK_CUR);
            fscanf(fichier, "%d %d", &sommet[h][0],&sommet[h][1]);
            h++;
        }
    }
    taille = h;
    graphe->taille= taille;

    int nbpresent[graphe->taille],nom[graphe->taille];
    int cpt = 0;
    bool present ;
    for (int i = 0; i<graphe->taille;i++){
        nbpresent[i] = 0;
        present =0;
        for (int j = 0; j<i;j++){
            if (sommet[i][0] == sommet[j][0]){
                nbpresent[i] = nbpresent[j];
                present =1;
            }
        }
        if (!present){
            nbpresent[i] = cpt;
            nom[cpt]=sommet[i][0];
            cpt++;
        }
    }
    ordre = cpt;
    graphe->ordre = cpt;
    printf ("ordre = %d",ordre);


    graphe->sommet = malloc(graphe->ordre *sizeof (t_sommet*));
    for (int i = 0; i<graphe->ordre;i++){
        graphe->sommet[i] = malloc( sizeof (t_sommet));
        graphe->sommet[i]->nom = nom[i];
    }
    for (int i =0;i<taille;i++){
        printf("\n%d %d",sommet[i][0],sommet[i][1]);
    }
    for (int i = 0;i<graphe->taille;i++){
        graphe->sommet = creerarrete(graphe->sommet,nbpresent[i],sommet[i][1]);
        /*if (orientation ==0) {
            graphe->sommet = creerarrete(graphe->sommet, s2, s1, poids);
        }*/
    }

    printf("\nordre : %d",graphe->ordre);
    for (int i = 0;i< graphe->ordre;i++){
        printf ("\nnom : %d, adjacents : ",graphe->sommet[i]->nom);
        t_arc *actuel = graphe->sommet[i]->arc;
        while (actuel !=NULL){
            printf("%d ",actuel->sommet);
            actuel = actuel->arc_suivant;
        }
    }

    return graphe;
}

int main() {
    char nom[20] = {"precedences.txt"};
    //printf("donnez le nom du fichier\n");
    //scanf("%s",nom);
    t_graphe *graphe= lecture(nom);
    //affichergraphe(graphe);
    return 0;
}
