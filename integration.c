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
    float* tableau_irr=init_iir(); //tableau de 4 éléments qui garde en mémoire les valeurs n-1 de x et y pour acR et acIR
    myMesures mesures = init_mesure(); //structure qui va garder en mémoire les valeurs utiles pour calculer le pouls et la saturation spO2
    FILE* fichier=initFichier(filename); //défini mon fichier ayant toutes les valeurs
    do{
        myAbsorp = lireFichier(fichier,&etat_fichier); //lecture de nouvelles valeurs
        myAbsorp = FIR(myAbsorp,buffer); //application du filtre FIR
        myAbsorp = IIR(myAbsorp, tableau_irr); //application du filtre IIR
        myOxy = MESURE(myAbsorp, &mesures, myOxy); //calcul du pouls et de la saturation spO2
        affichage(myOxy);
    }while( etat_fichier != EOF );
    finFichier(fichier);
    fin_iir(tableau_irr);
    fin_fir(buffer) ;
    fin_mesure(mesures.tab_bpm);
}