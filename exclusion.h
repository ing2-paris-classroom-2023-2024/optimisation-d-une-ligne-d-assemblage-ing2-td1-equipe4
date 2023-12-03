#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD1_EQUIPE4_EXCLUSION_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD1_EQUIPE4_EXCLUION_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct Arc{
    int sommet;
    struct Arc* arc_suivant;
};

typedef struct Arc* pArc;

struct Sommet{
    struct Arc* arc;
};

typedef struct Sommet* pSommet;

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
