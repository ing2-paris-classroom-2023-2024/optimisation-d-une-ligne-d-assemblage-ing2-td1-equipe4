//
// Created by Nathan Gaulle on 13/11/2023.
//

#include "main.h"


t_graphe lecture (charfile){
    t_graphe graphe = malloc (sizeof (t_graphe ));
    FILEfichier = fopen(file,"r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    int orientation;
    int ordre;


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
    ordre = h;
    
    for (int i =0;i<ordre;i++){
        printf("\n%d %d",sommet[i][0],sommet[i][1]);
    }
return graphe
}
#include <stdio.h>
typedef struct sommets {
    int nom;
    int exclusions[10]; //-1 si pas dexclusion
    int temps ;
    int placee ;
    int nexclusion;
}_som;

typedef struct machine{
    _som sommets[20];
    int temps ;
    int vide ;//0=oui 1=non
    int nbsommets;

}_machine;
void recup() {

}

#include <stdio.h>
#include <stdlib.h>


typedef struct sommets {
    char vrainom[20];
    int nom;
    struct sommets* exclusions[10]; //-1 si pas dexclusion
    float temps ;
    int placee ;//1=oui 0=nn
    int nexclusion;
    struct sommets* precedant[10];
    int nprecedant;
    int pretprptrecedance;// initialise a 0
}_som;

typedef struct machine{
    _som sommets[20];
    float temps ;
    int vide ;//0=oui 1=non
    int nbsommets;

}_machine;
void recup() {

}

int main() {
    int nombresommets=1,nbexclu=0,numm=0,pasdexclu ,nummf,numtabvalide=0,fin=0,nmachine=0;//nombresommets=0!!!!
    _som sommet;
    float tempsmax=0;

    recup();
    // int tab[nombresommets][nombresommets];
    //_som tabvalide[nombresommets],tabnexclu[nombresommets];
    _som tab[nombresommets],tabexclusion[nombresommets];
    _machine tabm[nombresommets];


    while (fin==0) {
        for (int i = 0; i < nombresommets; ++i) {

            for (int j = 0; j < tab[i].nprecedant; ++j) {
                if (tab[i].precedant[j]->placee == 1) {
                    tab[i].pretprptrecedance += 1;
                }
            }
            if ((tab[i].precedant[0] == NULL) || (tab[i].pretprptrecedance == tab[i].nprecedant)) {
                //    tabvalide[numtabvalide]=tab[i];
                //    numtabvalide+=1;
                tabexclusion[numtabvalide] = tab[i];
                nbexclu += 1;
            }
        }
/**
    for (int i = 0; i < numtabvalide ; ++i) {
        if (tabvalide[i].exclusions[0]==NULL) {
            tabnexclu[nbnexclu] = tabvalide[i];
            nbnexclu+=1;
        }
        if (tabvalide[i].exclusions[0]!=NULL) {    //-1 si c vide initialiser a -1
        tabexclusion[nbexclu] = tabvalide[i];
        nbexclu += 1;
        }
     }
            */ // WP ca colorie apres avori colorier on place sur les machine comme si  une machine etait une couleur et apres ca tu rentre des sommets qui ont pas d'exclusion

        for (int i = 0; i < nbexclu; ++i) {
            for (int j = 0; j < nbexclu - 1; ++j) {
                if ((tabexclusion[j].nexclusion < tabexclusion[j + 1].nexclusion) ||
                    ((tabexclusion[j].nexclusion == tabexclusion[j + 1].nexclusion) &&
                     (tabexclusion[j].temps < tabexclusion[j + 1].temps))) {
                    sommet = tabexclusion[j];
                    tabexclusion[j] = tabexclusion[j + 1];
                    tabexclusion[j + 1] = sommet;
                }
            }
        }

        while (tabexclusion[0].placee == 0) {
            pasdexclu = 0;
            for (int k = 0; k < tabexclusion[0].nexclusion; ++k) {
                for (int j = 0; j < tabm[numm].nbsommets; ++j) {
                    if (tabexclusion[0].exclusions[k]->nom == tabm[numm].sommets[j].nom) {
                        pasdexclu = 1;
                    }
                }
            }
            if ((tabexclusion[0].temps + tabm[numm].temps <= tempsmax) && (pasdexclu == 0)) {
                tabm[numm].sommets[tabm[numm].nbsommets] = tabexclusion[0];
                tabm[numm].nbsommets += 1;
                tabm[numm].vide = 1;
                tabm[numm].temps += tabexclusion[0].temps;
                tabexclusion[0].placee = 1;
            } else {
                if (numm < nombresommets) {
                    numm += 1;
                    if (numm > nummf) {
                        nummf = numm;
                    }
                } else {
                    printf("ce sommet ne peux pas rentrer dans aucune machhine meme si elle est vide");
                    exit(-1);
                }
            }
        }
        for (int i = 0; i < nombresommets; ++i) {
            if (tab[i].placee==1){
                fin+=1;
            }
        }
        if (fin != nombresommets){
            fin=0;
        }

    }

/**
    for (int i = 0; i < nbnexclu; ++i) {
        while (tabnexclu[i].placee==0) {
            if (tabnexclu[i].temps + tabm[numm].temps <= tempsmax) {
                tabm[numm].sommets[tabm[numm].nbsommets] = tabnexclu[i];
                tabm[numm].nbsommets += 1;
                tabm[numm].vide = 1;
                tabm[numm].temps += tabnexclu[i].temps;
                tabnexclu[i].placee = 1;
            } else {
                if (numm < 10) {
                    numm += 1;
                    if(numm>nummf) {
                        nummf = numm;
                    }
                } else {
                    printf("pas asser de machine(+de10)");
                }
            }
        }
    }
*/
    printf("\nl'operation a marccher avec succes il faut %d machine pour cette usine tel que on a :\n",nummf);

    while (tabm[nmachine].vide==1){
        printf("machine N %d :\n possede les %d sommets suivant :\n",nmachine,tabm[nmachine].nbsommets);
        for (int i = 0; i < tabm[nmachine].nbsommets; ++i) {
            printf("sommets : %s  \n",tabm[nmachine].sommets[i].vrainom);
        }
        printf("temp total sur temp max de la machine : %f sur %f \n",tabm[nmachine].temps,tempsmax);
    }
    for (int i = 0; i <nombresommets ; ++i) {
        if(tabm[i].vide==1){
            nmachine+=1;
        }
    }







    return 0;
}
