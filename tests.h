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
    int rang;
    char couleur;
    float temps;
    int predecesseur;
}t_sommet;


typedef struct graphe{
    int ordre;
    int taille;
    int max;
    int orientation;
    int *position;
    bool *source;
    t_sommet **sommet;
    float tmpcycle;
}t_graphe;


typedef struct valnom{
    float valeur;
    int nom;
}t_valnom;

typedef struct temps{
    t_valnom *valnom;
    int taille;
}t_temps;


typedef struct valeur{
    int nom;
    struct valeur *suivant;
}t_valeur;

typedef struct machines {
    t_valeur *nom;
    float tempstot;
    int rangactuel;
    struct machines *suivant;
}t_machines;

typedef struct elem{
    int sommet;
    struct elem *suivant;
}t_elem;
typedef struct file{
    t_elem *premier;
}File;



#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD1_EQUIPE4_TESTS_H
