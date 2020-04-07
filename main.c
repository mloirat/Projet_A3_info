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

    //absorp myAbsorp=lireFichier(mon_fichier,NULL);//je récupère mon premier absorp
    /*absorp myAbsorp;
    myAbsorp.acr=1;
    myAbsorp.acir=2;
    myAbsorp.dcr=3;
    myAbsorp.dcir=4;*/


    absorp myAbsorp = iirTest("record1_fir.dat");
    printf("acr= %f \n acir= %f \n dcr= %f \n dcir= %f", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);



    return 0;
}

