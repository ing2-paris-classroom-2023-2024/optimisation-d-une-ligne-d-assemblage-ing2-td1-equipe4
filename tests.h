//
// Created by Nathan Gaulle on 20/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD1_EQUIPE4_TESTS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD1_EQUIPE4_TESTS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct Arc{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int poids;
    struct Arc* arc_suivant;
}t_arc;



typedef struct Sommet{
    t_arc * arc;
    int nom;
    int position;
    char couleur;
    int distance;
    int predecesseur;
}t_sommet;

typedef struct graphe{
    int ordre;
    int taille;
    int orientation;
    t_sommet **sommet;
}t_graphe;

typedef struct arete{
    int sommet1,sommet2;
    int poids;
}t_arete;
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD1_EQUIPE4_TESTS_H
