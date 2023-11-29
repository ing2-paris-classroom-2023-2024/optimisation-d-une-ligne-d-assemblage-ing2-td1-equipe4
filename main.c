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

int main() {
    int tempsmax=0,nombresommets,nbexclu=0,nbnexclu=0,numm=0,pasdexclu=0 ,nummf;
    _som sommet;
    recup();
    // int tab[nombresommets][nombresommets];
    _som tabnexclu[nombresommets],tabexclusion[nombresommets];
    for (int i = 0; i < nombresommets ; ++i) {
        if (sommet.exclusions[1]==-1) {
            tabnexclu[i] = sommet;
            nbnexclu+=1;
        }
        if (sommet.exclusions[1]!=-1) {    //-1 si c vide initialiser a -1
        tabexclusion[i] = sommet;
        nbexclu += 1;
        }

            // WP ca colorie apres avori colorier on place sur les machine comme si  une machine etait une couleur et apres ca tu rentre des sommets qui ont pas d'exclusion
    }
    for (int i = 0; i <nbexclu ; ++i) {
        for (int j = 0; j < nbexclu - 1; ++j) {
            if ((tabexclusion[j].nexclusion < tabexclusion[j+1].nexclusion)||((tabexclusion[j].nexclusion == tabexclusion[j+1].nexclusion)&&(tabexclusion[j].temps < tabexclusion[j+1].temps))){
                sommet=tabexclusion[j];
                tabexclusion[j]=tabexclusion[j+1];
                tabexclusion[j+1]=sommet;
            }
        }
    }

    for (int i = 0; i < nbexclu; ++i) {

        while (tabexclusion[i].placee==0) {
            pasdexclu = 0;
            for (int k = 0; k < 10; ++k) {
                for (int j = 0; j < tabm[numm].nbsommets; ++j) {
                    if (tabexclusion[i].exclusions[k] == tabm[numm].sommets[j].nom) {
                        pasdexclu = 1;
                    }
                }
            }
            if ((tabexclusion[i].temps + tabm[numm].temps <= tempsmax) && (pasdexclu == 0)) {
                tabm[numm].sommets[tabm[numm].nbsommets] = tabexclusion[i];
                tabm[numm].nbsommets += 1;
                tabm[numm].vide = 1;
                tabm[numm].temps += tabexclusion[i].temps;
                tabexclusion[i].placee = 1;
            } else {
                if (numm < 10) {
                    numm += 1;
                    if (numm > nummf) {
                    nummf = numm;
                    }
                } else {
                    printf("pas asser de machine(+de10)");
                }
            }
        }
    }

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

    printf("\nl'operation a marccher avec succes il faut %d machine pour cette usine\n",nummf);

//execution + temps 
    //aplication de prime avec optimisation des ligne de suivie 
// aucasionemment 
    //file de priorite ordonance pause 
    //pethonde de 011


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


    return 0;
}
