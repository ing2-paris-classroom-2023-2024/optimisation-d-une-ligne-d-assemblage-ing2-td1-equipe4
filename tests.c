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
    char actuel = 0;
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
    int max = 0;
    for (int i = 0; i<graphe->taille;i++){
        nbpresent[i] = 0;
    }
    for (int i = 0; i<graphe->taille;i++){
        present = 0;
        if (max < sommet[i][0] || max < sommet[i][1]){
            if (sommet[i][0]>sommet[i][1]){
                max = sommet[i][0];
            } else max = sommet[i][1];
        }
        for (int j = 0; j<i;j++) {
            if (sommet[i][0] == sommet[j][0]) {
                nbpresent[i] = nbpresent[j];
                present = 1;
            }
        }
        if (!present) {
            nbpresent[i] = cpt;
            nom[cpt]=sommet[i][0];
            printf("\nnbpresesent = %d, nom = %d cpt = %d i = %d",nbpresent[i],nom[cpt],cpt,i);
            cpt++;
        }
    }
    int premier = cpt;
    int nbpresent2[graphe->taille];
    for (int i = 0; i<graphe->taille;i++){
        present = 0;
        for (int j = 0; j<cpt;j++) {
            if (sommet[i][1] == nom[j]) {
                nbpresent2[i] = nbpresent2[j];
                present = 1;
            }
        }
        if (!present) {
            nbpresent2[i] = cpt;
            nom[cpt]=sommet[i][1];
            printf("\nnbpresesent2 = %d, nom = %d cpt = %d i = %d",nbpresent2[i],nom[cpt],cpt,i);
            cpt++;
        }

    }

    ordre = cpt;
    for (int i = 0; i<cpt;i++){
        printf ("\ni = %d : cpt = %d, nbpresent %d",i,nom[i],nbpresent[i]);
    }

    graphe->ordre = cpt;
    graphe->max = max;
    printf ("ordre = %d",ordre);
    graphe->position = malloc(max *sizeof (int ));
    graphe->source = malloc(max*sizeof (bool));
    for (int i = 0; i<max;i++){
        graphe->position[i] = -1;
        graphe->source[i] = 0;
    }

    for (int i = 0; i<graphe->ordre;i++){

        graphe->position[nom[i]] = i;
    }
    bool prems, deux;
    for (int i = 0; i<graphe->ordre;i++) {
        prems = 0,deux = 0;
        for (int j = 0; j < taille; j++) {
            if (nom[i] == sommet[j][0]) {
                prems = 1;
            }
            if (nom[i] == sommet[j][1]) {
                deux = 1;
            }
        }
        if (prems && !deux) {
            graphe->source[nom[i]] = 1;
        }
    }
    for (int i = 0; i<graphe->ordre;i++){
        printf ("\ni = %d, nom = %d position = %d source = %d ",i,nom[graphe->position[i]],graphe->position[i],graphe->source[i]);
    }
    for (int i = 0; i<max;i++){
        printf ("\ni = %d : %d ",i,graphe->position[i]);
    }

    graphe->sommet = malloc(graphe->ordre *sizeof (t_sommet*));
    for (int i = 0; i<graphe->ordre;i++){
        graphe->sommet[i] = malloc( sizeof (t_sommet));
        graphe->sommet[i]->nom = nom[i];
    }
    for (int i =0;i<taille;i++){
       // printf("\n%d %d nom =%d",sommet[i][0],sommet[i][1],nom[i]);
    }
    printf ("\ntest : position = %d : %d et %d",26,graphe->position[26],graphe->sommet[graphe->position[26]]->nom);

    for (int i = 0;i<graphe->taille;i++){
        //printf("\n??? %d %d",nbpresent[i],sommet[i][1]);
        graphe->sommet = creerarrete(graphe->sommet, nbpresent[i], sommet[i][1]);

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

t_graphe *lecture_exclu ( char *file,int ordre){
    printf ("\nmax = %d",ordre);
    t_graphe *graphe = malloc (sizeof (t_graphe ));
    FILE *fichier = fopen(file,"r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    int orientation;
    int taille;

    int sommet[50][2];
    int h = 0;
    char actuel = 0;
    while (actuel != EOF){
        actuel = fgetc(fichier);
        if (actuel >= '0' && actuel<= '9') {
            fseek(fichier, -1,SEEK_CUR);
            fscanf(fichier, "%d %d", &sommet[h][0],&sommet[h][1]);
            h++;
        }
    }
    taille = h;
    graphe->ordre = ordre+1;
    graphe->taille = taille;
    graphe->sommet = malloc((ordre)*sizeof (t_sommet));
    for (int i = 0; i<graphe->ordre;i++) {
        graphe->sommet[i] = malloc(sizeof(t_sommet));
    }

    for (int i = 0;i<graphe->taille;i++){
        graphe->sommet = creerarrete(graphe->sommet,sommet[i][0],sommet[i][1]);
        graphe->sommet = creerarrete(graphe->sommet, sommet[i][1],sommet[i][0]);
    }
    printf ("\nexclusion");
    for (int i = 0;i<h;i++){
        printf ("\n%d %d",sommet[i][0],sommet[i][1]);
    }
    for (int i = 0;i< graphe->ordre;i++){
        printf ("\nnom : %d, adjacents : ",i);
        t_arc *actuel = graphe->sommet[i]->arc;
        while (actuel !=NULL){
            printf("%d ",actuel->sommet);
            actuel = actuel->arc_suivant;
        }
    }
    return graphe;
}

t_temps *lecture_temps ( char *file){
    t_temps *temps = malloc (sizeof (t_temps ));
    FILE *fichier = fopen(file,"r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    int taille;

    int sommet1[50];
    float sommet2[50];
    int h = 0;
    char actuel = 0;
    while (actuel != EOF){
        actuel = fgetc(fichier);
        if (actuel >= '0' && actuel<= '9') {
            fseek(fichier, -1,SEEK_CUR);
            fscanf(fichier, "%d %f", &sommet1[h],&sommet2[h]);
            h++;
        }
    }
    taille = h;

    temps->taille = taille;
    temps->valnom = malloc((taille)*sizeof (t_valnom));

    for (int i = 0;i<temps->taille;i++){
        temps->valnom[i].nom = sommet1[i];
        temps->valnom[i].valeur = sommet2[i];
    }
    printf ("\ntemps");
    printf ("\ntaille = %d",taille);
    for (int i = 0;i<h;i++){
        printf ("\n%d %.2f",sommet1[i],sommet2[i]);
    }
    return temps;
}

void assimilation (t_graphe *graphe, t_temps *temps,char *file){
    for (int i = 0; i<graphe->ordre;i++){
        graphe->sommet[i]->temps = 0;
    }
    for (int i = 0; i<temps->taille;i++){
        graphe->sommet[graphe->position[temps->valnom[i].nom]]->temps = temps->valnom[i].valeur;
    }
    for (int i = 0; i<temps->taille;i++){
        printf("\nnom sommet = %d, temps = %.2f",graphe->sommet[i]->nom,graphe->sommet[i]->temps);
    }
    FILE *fichier = fopen(file,"r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    fscanf(fichier,"%f",&graphe->tmpcycle);
    printf ("\ntemps de cycle = %f",graphe->tmpcycle);
}

/*void ordre (t_graphe *graphe){
    int sortie = 26;
    int valeur;
    printf ("\n");
    bool passe;
    while (sortie != -1){
        valeur = graphe->position[sortie];


        if (valeur != -1) {
            passe = 0;
            for (int i = 0; i < graphe->ordre && passe !=1; i++) {
                t_arc *actuel = graphe->sommet[i]->arc;
                while (actuel != NULL && actuel->sommet != graphe->sommet[valeur]->nom) {
                    printf("%d ", actuel->sommet);
                    if (actuel->sommet == graphe->sommet[valeur]->nom ) {
                        passe = 1;
                        printf("\nprecede %d\n", actuel->sommet);
                    }
                    actuel = actuel->arc_suivant;
                }
            }
            if (passe == 0){
                sortie = -1;
                printf ("\neeeeeeee");
            }
        }
        printf ("\nsortie : %d",sortie);
    }
}*/

t_machines * creervaleur (t_machines *machine,int nom){
    t_valeur *valeur = malloc(sizeof (t_valeur *));
    valeur->nom = nom;
    valeur->suivant =  NULL;
    if (machine->nom == NULL){
        machine->nom = valeur;
        return machine;
    }
    t_valeur *actuel = machine->nom;
    while (actuel->suivant !=NULL){
        actuel = actuel->suivant;
    }
    actuel->suivant = valeur;
    return machine;
}

t_machines *creermachines (){
    t_machines *machines = malloc(sizeof (t_machines ));
    machines->nom = NULL;
    machines->suivant = NULL;
    machines->tempstot = 0;
    return machines;
}

t_elem *creerelem (){
    t_elem *file = malloc (sizeof (t_elem));
    // file->nombre = nombre;
    file->suivant = NULL;
    return file;
}

void enfiler (File *file,int nombre, t_graphe *graphe) {
    //printf("\nenfile2 = %d", nombre);
    //printf("\nnombre?? = %d", file->sommet);
    t_elem *actuel = file->premier;
    t_elem *ancien;
    bool continu = 0;
    int cpt = 0;
    if (actuel != NULL) {
    //if (actuel->suivant != NULL) {
        //printf("\nsommet = %d", actuel->sommet);
        while (continu == 0) {
           // printf ("\nenfile3 = %d et %f et %f",nombre,graphe->sommet[graphe->position[actuel->sommet]]->temps,graphe->sommet[graphe->position[nombre]]->temps);
            //if (graphe->sommet[graphe->position[nombre]]->temps < graphe->sommet[graphe->position[actuel->sommet]]->temps) {
            if (graphe->sommet[graphe->position[nombre]]->temps < graphe->sommet[graphe->position[actuel->sommet]]->temps && graphe->sommet[graphe->position[nombre]]->rang >= graphe->sommet[graphe->position[actuel->sommet]]->rang) {
                cpt++;
                printf ("\nechange = %d -> %d",actuel->sommet,nombre);
                ancien = actuel;
                actuel = actuel->suivant;
            } else continu = 1;
            //if (actuel->suivant == NULL)
            if (actuel == NULL)
                continu = 1;
        }
    }
    //printf("\ncpt = %d",cpt);
    //if (continu == 1 && actuel->suivant != NULL){
    if (continu && !cpt){
       // printf ("\n\nentre\n");
        t_elem *nouv = creerelem();
        nouv->sommet = nombre;
        nouv->suivant = actuel;
        file->premier = nouv ;
        //file->premier->suivant = actuel;
    } else if (continu && cpt>0){
       // printf ("\n\nentre2");
        t_elem *nouv = creerelem();
        nouv->sommet = nombre;
        nouv->suivant = actuel;
        ancien->suivant = nouv ;
    }else{
        t_elem *nouv = creerelem();
        nouv->sommet = nombre;
        file->premier = nouv ;
        //printf("\nfin = %d", nombre);
        /*t_elem *nouv = creerelem();
        actuel->sommet = nombre;
        actuel->suivant = nouv;*/
    }
   // printf("\nnouv->sommet = %d", file->premier->sommet);
    //printf("\nnouv->sommet2 = %d", file->suivant->sommet);

}

void enfilrang (File *file,int nombre){
    t_elem *nouv = creerelem();
    nouv->sommet = nombre;
    if (file->premier != NULL) {
        t_elem *actuel = file->premier;
        while (actuel->suivant != NULL) {
            actuel = actuel->suivant;
        }

        actuel->suivant = nouv;
    }else file->premier = nouv;
}

int defiler (File *file){
    int nombre =-1;
    if (file->premier != NULL) {
        t_elem *element = file->premier;
        nombre = element->sommet;
        file->premier = element->suivant;
        free(element);
    }

    return nombre;
}

void un_et_deux (t_graphe *graphe, t_temps *temps){
    t_machines *machines = creermachines();
    File *file= malloc(sizeof (File));
   // file->premier= creerelem();
    File *rangement = malloc(sizeof (File));
    rangement->premier= creerelem();
    for (int i = 0; i<graphe->ordre;i++){
        if (graphe->source[i]){
            graphe->sommet[i]->rang = 0;
            printf ("\nenfile1 = %d rang = %d",graphe->sommet[graphe->position[i]]->nom,graphe->sommet[graphe->position[i]]->rang);
            enfiler(file, graphe->sommet[graphe->position[i]]->nom,graphe );
            enfilrang(rangement, graphe->sommet[graphe->position[i]]->nom );
        }
    }

    int defilement = 1;
    defiler(rangement);
    while (defilement != -1&& defilement != 0){
        defilement = defiler(rangement);
       // printf ("\npasse + defile = %d + %d",defilement, graphe->position[defilement]);
        if (defilement != -1&& defilement != 0) {
            //printf ("\ndefile1 = %d position = %d rang = %d",defilement,graphe->sommet[graphe->position[defilement]]->nom,graphe->sommet[graphe->position[defilement]]->rang);
            t_arc *arcactu = graphe->sommet[graphe->position[defilement]]->arc;
            //printf("\ntest sommet :");
            while (arcactu != NULL) {
                enfilrang(rangement, arcactu->sommet);
                if (graphe->sommet[graphe->position[defilement]]->rang + 1 >graphe->sommet[graphe->position[arcactu->sommet]]->rang)
                    graphe->sommet[graphe->position[arcactu->sommet]]->rang = graphe->sommet[graphe->position[defilement]]->rang + 1;
                arcactu = arcactu->arc_suivant;
            }
        }
    }
    for (int i = 0;i<graphe->ordre;i++){
        printf ("\nnom = %d rang = %d",graphe->sommet[i]->nom,graphe->sommet[i]->rang);
    }

    defilement = 1;
    int nbtour = 0;
    while (defilement != -1 && defilement != 0) {
        defilement = defiler(file);
        nbtour++;
        printf("\ndefilement : %d", defilement);
        printf ("\nfile = ");
        t_elem *testfile = file->premier;
        while (testfile != NULL){
            printf("%d ",testfile->sommet);
            testfile = testfile->suivant;
        }
        if (defilement != -1&& defilement != 0) {
            int pos = 0;


            bool fin = 0;
            t_machines *machineactu = machines;
            ////Ancienne version en cherchant les noms des sommets pour vérifier s'il y a son prédesseceur
            if (machineactu->nom != NULL) {
                while (!fin && machineactu != NULL) {
                    bool passage = 0;
                    t_valeur *valeur = machineactu->nom;
                    if (!graphe->source[defilement]) {
                        while (valeur != NULL && !passage) {
                            t_arc *arcactu = graphe->sommet[graphe->position[valeur->nom]]->arc;
                           // printf ("\ntest sommet :");
                            while (arcactu != NULL && !passage) {
                                //printf (" %d",arcactu->sommet);
                                if (arcactu->sommet == defilement) {
                                   // printf(" bon");
                                    passage = 1;
                                }
                                arcactu = arcactu->arc_suivant;
                            }
                            valeur = valeur->suivant;
                        }
                    } else passage = 1;
                    //if (!passage) printf("\npassage");
                    if (graphe->sommet[graphe->position[defilement]]->temps + machineactu->tempstot >=
                        graphe->tmpcycle || !passage) {
                        pos++;
                        machineactu = machineactu->suivant;
                    } else fin = 1;
                }
            }

            if (machineactu == NULL) {
                t_machines *test = machines;
                while (test->suivant != NULL)
                    test = test->suivant;
                test->suivant = creermachines();
                test->suivant->tempstot += graphe->sommet[graphe->position[defilement]]->temps;
                test->suivant = creervaleur(test->suivant, defilement);
                /*machineactu = creermachines();
                printf ("\nnouveau\n\n");
                if (machineactu != NULL)
                    printf ("fonctionne");*/
            }else{
            machineactu->tempstot += graphe->sommet[graphe->position[defilement]]->temps;
            machineactu = creervaleur(machineactu, defilement);
            }
            t_arc *arcactu = graphe->sommet[graphe->position[defilement]]->arc;
            while (arcactu != NULL) {
                if (graphe->sommet[graphe->position[arcactu->sommet]]->couleur == 0) {
                    printf("\n      enfilement : %d", arcactu->sommet);
                    enfiler(file, arcactu->sommet, graphe);
                    graphe->sommet[graphe->position[arcactu->sommet]]->couleur = 1;


                }
                arcactu = arcactu->arc_suivant;
            }
        }
    }
    printf("\ntour = %d",nbtour);
    t_machines *machineactu = machines;
    int cpt = 0;
    while (machineactu != NULL){
        t_valeur *valeur = machineactu->nom;
        printf ("\nmachine %d : ",cpt);
        while (valeur != NULL){
            printf ("%d ",valeur->nom);
            valeur = valeur->suivant;
        }
        printf ("temps total = %f",machineactu->tempstot);
        cpt++;
        machineactu = machineactu->suivant;
    }

   /* int nb;
    printf ("..nom = %d",nb);
    for (int i = 1; i<graphe->ordre;i++){
        printf ("\ni = %d",i);
        nb = graphe->position[i];
        if (nb !=-1)
            enfiler(file, graphe->sommet[graphe->position[i]]->nom,graphe );
    }
    int defilement = 1;
    while (defilement != -1){
        defilement = defiler(file);
        printf ("\ndefile = %d",defilement );
    }*/
    /*printf ("\nenfile1 = %d",2);
    enfiler(file, 2,graphe );
    printf ("\ndefile = %d", defiler(file));
    printf ("\ndefile = %d", defiler(file));
    printf ("\ndefile = %d", defiler(file));*/
}

int main() {
    char nom[20] = {"precedences.txt"};
    char nom2[20] = {"exclusions.txt"};
    char nom3[20] = {"operations.txt"};
    char nom4[20] = {"temps_cycle.txt"};
    //printf("donnez le nom du fichier\n");
    //scanf("%s",nom);
    t_graphe *graphe= lecture(nom);
    t_graphe *exclusion = lecture_exclu(nom2,graphe->max);
    t_temps *temps = lecture_temps(nom3);
    assimilation(graphe,temps,nom4);
    un_et_deux(graphe,temps);
    //ordre(graphe);
    //affichergraphe(graphe);
    return 0;
}
