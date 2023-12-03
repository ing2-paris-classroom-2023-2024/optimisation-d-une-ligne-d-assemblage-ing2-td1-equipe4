#include <stdio.h>
#include <stdlib.h>


typedef struct sommets {
    int nom;
    int exclusions[10]; //-1 si pas dexclusion
    float temps ;
    int placee ;//1=oui 0=nn
    int nexclusion;
    int precedant[10];
    int nprecedant;
    int pretprptrecedance;// initialise a 0
}_som;

typedef struct machine{
    _som sommets[20];
    float temps ;
    int vide ;//0=oui 1=non
    int nbsommets;

}_machine;

void rayan(){ 
    int nombresommets=0,nbexclu,numm=0,pasdexclu ,nummf,numtabvalide=0,fin=0,nmachine=0 ,actuel=0,nexclu=0,nprece=0;//nombresommets=0!!!!
    _som sommet;
    float tempsmax=0;

    FILE*fichier = fopen("operations.txt","r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    while (actuel != EOF){
        actuel = fgetc(fichier);
        if (actuel >= '0' && actuel<= '9') {
            fseek(fichier, -1,SEEK_CUR);
            fscanf(fichier, "%d %f", &sommet.nom,&sommet.temps);
            nombresommets++;
        }
    }
    fclose(fichier);
    fichier = fopen("temps_cycle.txt","r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    fscanf(fichier,"%f",&tempsmax);
    fclose(fichier);
    actuel=0;
    fichier = fopen("exclusions.txt","r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    while (actuel != EOF){
        actuel = fgetc(fichier);
        if (actuel >= '0' && actuel<= '9') {
            fseek(fichier, -1,SEEK_CUR);
            fscanf(fichier, "%d %f", &sommet.nom,&sommet.temps);
            nexclu++;
        }
    }
    fclose(fichier);
    actuel=0;
    fichier = fopen("precedance.txt","r");
    if (!fichier)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    while (actuel != EOF){
        actuel = fgetc(fichier);
        if (actuel >= '0' && actuel<= '9') {
            fseek(fichier, -1,SEEK_CUR);
            fscanf(fichier, "%d %f", &sommet.nom,&sommet.temps);
            nprece++;
        }
    }
    fclose(fichier);

    _som tab[nombresommets],tabexclusion[nombresommets];
    _machine tabm[nombresommets];
    int chiffre;
    char* nomfile="operations.txt";
    int h =nombresommets, ex=nexclu, np=nprece;

    int exclu1=0,exclu2=0;
    FILE*fichier2 = fopen(nomfile,"r");
    if (!fichier2)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    rewind(fichier2);
    sommet.placee=0;
    sommet.pretprptrecedance=0;
    sommet.nexclusion=0;
    sommet.nprecedant=0;

    for (int j = 0; j < 10; ++j) {
        sommet.precedant[j]=-1;
        sommet.exclusions[j]=-1;
    }

    for (int i = 0; i <h ; ++i){

        fscanf(fichier2, "%d %f", &sommet.nom,&sommet.temps);
        tab[i]=sommet;

    }
    fclose(fichier2);
    fichier2 = fopen("exclusions.txt","r");
    if (!fichier2)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    rewind(fichier2);
    for (int i = 0; i <ex ; ++i){

        fscanf(fichier2, "%d %d", &exclu1,&exclu2);
        for (int j = 0; j < h; ++j) {
            if(tab[j].nom==exclu1){
                tab[j].exclusions[tab[j].nexclusion]=exclu2;
                tab[j].nexclusion+=1;
            }
            if(tab[j].nom==exclu2){
                tab[j].exclusions[tab[j].nexclusion]=exclu1;
                tab[j].nexclusion+=1;

            }
        }

    }
    fclose(fichier2);
    printf("\n");
    fichier2 = fopen("precedance.txt","r");
    if (!fichier2)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    rewind(fichier2);
    for (int i = 0; i <np ; ++i){

        fscanf(fichier2, "%d %d", &exclu1,&exclu2);
        for (int j = 0; j < h; ++j) {
            if(tab[j].nom==exclu2){
                tab[j].precedant[tab[j].nprecedant]=exclu1;
                tab[j].nprecedant+=1;
            }
        }

    }
    fclose(fichier2);


    for (int i = 0 ;i< nombresommets ;i++){
    }

    while (fin==0) {
        nbexclu=0;
        for (int i = 0; i < nombresommets; ++i) {
            tabexclusion[i].nexclusion = 10;
        }


        for (int j = 0; j < tab[j].nprecedant; ++j) {
            tab[j].pretprptrecedance = 0;
        }
        for (int i = 0; i < nombresommets; ++i) {

            for (int j = 0; j < tab[i].nprecedant; ++j) {
                for (int k = 0; k <nombresommets ; ++k) {
                    if(tab[i].precedant[j]==tab[k].nom){
                        chiffre=k;
                    }
                }
                if (tab[chiffre].placee == 1) {
                    tab[i].pretprptrecedance += 1;
                }
            }
            if(tab[i].placee==0) {
                if ((tab[i].precedant[0] == -1) || (tab[i].pretprptrecedance >= tab[i].nprecedant)) {//>= est faux normalemment c == mais bon
                    //    tabvalide[numtabvalide]=tab[i];
                    //    numtabvalide+=1;
                    tabexclusion[nbexclu] = tab[i];//ntabvalide = nbexclu
                    nbexclu += 1;
                }
            }
        }

             // WP ca colorie apres avori colorier on place sur les machine comme si  une machine etait une couleur et apres ca tu rentre des sommets qui ont pas d'exclusion

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
                    if (tabexclusion[0].exclusions[k] != -1) {
                        if (tabexclusion[0].exclusions[k] == tabm[numm].sommets[j].nom) {
                            pasdexclu = 1;
                        }
                    }
                }
            }
            if ((tabexclusion[0].temps + tabm[numm].temps <= tempsmax) && (pasdexclu == 0)) {
                tabm[numm].sommets[tabm[numm].nbsommets] = tabexclusion[0];
                tabm[numm].nbsommets += 1;
                tabm[numm].vide = 1;
                tabm[numm].temps += tabexclusion[0].temps;
                tabexclusion[0].placee = 1;
                for (int i = 0; i < nombresommets; ++i) {
                    if(tab[i].nom==tabexclusion[0].nom){
                        tab[i].placee=1;
                    }
                }
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

    printf("\nl'operation a marccher avec succes il faut %d machine pour cette usine tel que on a :\n",nummf);

    while (tabm[nmachine].vide==1){
        printf("machine N %d :\n possede les %d sommets suivant :\n",nmachine,tabm[nmachine].nbsommets);
        for (int i = 0; i < tabm[nmachine].nbsommets; ++i) {
            printf("sommets : %d  \n",tabm[nmachine].sommets[i].nom);
        }
        printf("temp total sur temp max de la machine : %f sur %f \n",tabm[nmachine].temps,tempsmax);
        nmachine+=1;
    }

}

int main() {
    int prog=0;
    do{
    printf("Quel programme souhaitez-vous lancer ?\n1. Programme d'exclusion simple\n2.Programme de précédence\n3.Precedence+exclusion+Temps de cycle");
    scanf("%d", &prog);
    if (prog==1){
        exclusion();
    }
    else if (prog==2){
        precedance_temps();
    }
    else {
        rayan()
    }}while((prog!=1)||(prog!=2)||(prog!=3));
    return 0 ;
}
