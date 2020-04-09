#include "fichiers.h"
#include "define.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"
#include "integration.h"

void integrationTest(char* filename){
    int etat_fichier=0;
    absorp myAbsorp;
    oxy myOxy;
    myOxy.spo2=0;
    myOxy.pouls=0;
    float** buffer= init_fir(); //tableau 2 dimensions qui va garder en mémoire les 51 entrées x(n) de acr du filtre FIR sur la première ligne et celles de acir sur la deuxième ligne
    float* param_iir=init_iir(); //tableau de 4 éléments qui garde en mémoire les valeurs n-1 de x et y pour acR et acIR
    myMesures mesure = init_mesure();
    FILE* fichier=initFichier(filename); //défini mon fichier ayant toutes les valeurs
    do{
        myAbsorp = lireFichier(fichier,&etat_fichier);
        myAbsorp = FIR(myAbsorp,buffer);
        myAbsorp = IIR(myAbsorp,param_iir);
        myOxy = MESURE(myAbsorp, &mesure, myOxy);
        affichage(myOxy);
    }while( etat_fichier != EOF );
    finFichier(fichier);
    fin_iir(param_iir);
    fin_fir(buffer) ;
    fin_mesure(mesure.tab_bpm);
}