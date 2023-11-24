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
