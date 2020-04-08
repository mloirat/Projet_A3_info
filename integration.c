#include "fichiers.h"
#include "affichage.h"
#include "define.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
void integrationTest(char* filename){
    int etat_fichier=0;
    absorp myAbsorp;
    oxy myOxy;
    float** buffer= init_fir(); //tableau 2 dimension qui va garder en mÃ©moire les 51entrÃ©es x(n) de acr du filtre FIR sur la premiÃ¨re ligne et celles de acir sur la deuxiÃ¨me ligne
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
    printf("sp02=%d, BMP=%d",myOxy.spo2,myOxy.pouls);
    finFichier(fichier);
    fin_iir(param_iir);
    fin_fir(buffer) ;
    fin_mesure(mesure.tab_bpm,mesure.tab_sp02);
}