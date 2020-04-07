#include <stdio.h>
#include "affichage.h"
#include "define.h"
#include "fir.h"
#include "fichiers.h"
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
    //init des buffers
    float * buffer_acr=malloc(50* sizeof(float));//garde toutes les valeurs des AC_R, correspond aux xn en entrée du filtre FIR
    float * buffer_acir=malloc(50* sizeof(float));// garde toutes les valeurs des AC_IR, correspond aux xn en entrée du filtre FIR
    FIR(myAbsorp, 1, &buffer_acr, &buffer_acir);

    return 0;
}