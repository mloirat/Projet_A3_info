#include <stdio.h>
#include "affichage.h"
#include "define.h"
#include "fir.h"
#include "fichiers.h"
#include "iir.h"

int main() {

    ///TEST AFFICHAGE///
    oxy myOxygene ;
    myOxygene.spo2=91;
    myOxygene.pouls=130;
    affichage(myOxygene);


    ///FILTRE FIR///
    FILE* mon_fichier=initFichier("record1.dat"); //je défini mon fichier ayant toutes les valeurs
    //absorp myAbsorp=lireFichier(mon_fichier,NULL);//je récupère mon premier absorp
    absorp myAbsorp;
    myAbsorp.acr=1;
    myAbsorp.acir=2;
    myAbsorp.dcr=3;
    myAbsorp.dcir=4;

    //init du tableau buffer
    float** buffer= init_fir(); //tableau 2 dimension qui va garder en mémoire les 51entrées x(n) de acr du filtre FIR sur la première ligne et celles de acir sur la deuxième ligne
    FIR(myAbsorp, buffer);

    ///FILTRE IRR///
    FILE* fichier=initFichier("record1_fir.dat");
    float* param_iir=init_iir();
    absorp myAbsorp;
    IIR(myAbsorp, param_iir);

    return 0;
}

