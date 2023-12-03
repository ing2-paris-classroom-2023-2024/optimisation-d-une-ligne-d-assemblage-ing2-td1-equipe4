#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD1_EQUIPE4_EXCLUSION_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD1_EQUIPE4_EXCLUSION_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct eArc{
    int sommet;
    struct eArc* arc_suivant;
};

typedef struct eArc* pArc;

struct eSommet{
    struct eArc* arc;
};

typedef struct eSommet* pSommet;

typedef struct tableau_fichier{
    int** tableau;
}tf;

struct station{
    int *etape;
    int taille;
};

typedef struct station* pstation;

typedef struct Graphe{
    int ordre;
    pSommet* pSommet;
    pstation* pstation;
} graphe;

void exclusion();
