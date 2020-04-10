#include <stdio.h>
#include "affichage.h"
#include "define.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "integration.h"
#include "lecture.h"
#include "fichiers.h"
int main() {

    ///TEST AFFICHAGE///
    /*
    oxy myOxygene ;
    myOxygene.spo2=91;
    myOxygene.pouls=130;
    affichage(myOxygene);
    */

    ///FILTRE FIR///
    /*
    absorp myAbsorp = firTest("record1.dat");
    printf("Filtre FIR : \n");
    printf("acr= %f \n acir= %f \n dcr= %f \n dcir= %f", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);
    */

    ///FILTRE IIR///
    /*
    absorp myAbsorp = iirTest("record1_fir.dat");
    printf("Filtre IIR : \n");
    printf("acr= %f \n acir= %f \n dcr= %f \n dcir= %f \n", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);
    */

    //MESURE//
    /*
    oxy myOxy = mesureTest("record1_iir.dat");
    printf("spo2 = %d %\npouls = %d bpm\n", myOxy.spo2, myOxy.pouls);
    */

    //INTEGRATION//
    /*
    integrationTest("record1.dat");
    */

    //LECTURE//
    /*
    FILE* fichier=initFichier("record1_bin.dat");
    int etat=0;
    absorp myAbs= lecture(fichier, &etat);
    printf("acr= %f \nacir= %f \ndcr= %f \ndcir= %f \n", myAbs.acr, myAbs.acir, myAbs.dcr, myAbs.dcir);
    */

    return 0;
}

