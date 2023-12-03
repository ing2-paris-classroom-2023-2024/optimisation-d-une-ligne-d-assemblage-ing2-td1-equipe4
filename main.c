#include <stdio.h>
#include <stdlib.h>



typedef struct sommets {
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
void recup(char* nomfile,int h ,int ex,_som* tab){
    int exclu1=0,exclu2=0;
    _som sommet;
        FILE*fichier2 = fopen(nomfile,"r");
        if (!fichier2)
        {
            printf("Erreur de lecture fichier\n");
            exit(-1);
        }
        rewind(fichier2);
    sommet.placee=0;
    sommet.pretprptrecedance=0;
    for (int j = 0; j < 10; ++j) {
        sommet.precedant[j]=NULL;
        sommet.exclusions[j]=NULL;
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
                tab[j].exclusions[tab[j].nexclusion] = &sommet;
                tab[j].exclusions[tab[j].nexclusion]->nom=exclu2;
                tab[j].nexclusion+=1;
                printf(" %d", tab[j].exclusions[tab[j].nexclusion-1]->nom);
            }
            if(tab[j].nom==exclu2){
                tab[j].exclusions[tab[j].nexclusion] = &sommet;
                tab[j].exclusions[tab[j].nexclusion]->nom=exclu1;
                tab[j].nexclusion+=1;

            }
        }

    }

    fclose(fichier2);




}

void interface(){
    int prog=0;
    printf("Quel programme souhaitez-vous lancer ?\n1. Programme d'exclusion simple\n2.Programme de précédence\n3.Precedence+exclusion+Temps de cycle");
    scanf("%d", &prog);
    if (prog==1){
        //programme numéro 1
    }
    else if (prog==2){
        //programme numéro 2
    }
    else {
        //programme numéro 3
    }

}

int main() {
    int nombresommets=0,nbexclu=0,numm=0,pasdexclu ,nummf,numtabvalide=0,fin=0,nmachine=0 ,actuel=0,nexclu=0,nprece=0;//nombresommets=0!!!!
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
    printf("%d",nombresommets);
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
    printf("\n%f",tempsmax);
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
    printf("\n%d", nexclu);
    fclose(fichier);

    _som tab[nombresommets],tabexclusion[nombresommets];
    _machine tabm[nombresommets];

    recup("operations.txt",nombresommets,nexclu,tab);
    for (int i = 0 ;i< nombresommets ;i++){
        printf("\n %d %f",tab[i].nom,tab[i].temps);
    }
    // int tab[nombresommets][nombresommets];
    //_som tabvalide[nombresommets],tabnexclu[nombresommets];



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
    printf("\nl'operation a marcher avec succes il faut %d machine pour cette usine tel que on a :\n",nummf);

    while (tabm[nmachine].vide==1){
        printf("machine N %d :\n possede les %d sommets suivant :\n",nmachine,tabm[nmachine].nbsommets);
        for (int i = 0; i < tabm[nmachine].nbsommets; ++i) {
            printf("sommets : %d  \n",tabm[nmachine].sommets[i].nom);
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
