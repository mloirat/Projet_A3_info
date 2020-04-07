#include "iir.h"
#include "fichiers.h"


absorp iirTest(char* filename){
	absorp	myAbsorp;
	initFichier(record1_fir.dat);
	lireFichier(record1_fir.dat);
	IIR(myAbsorp);
	if ( feof(record1_fir.dat)!=0){
	    finFichier(record1_fir.dat);
	}

	return myAbsorp;

}

absorp IIR(absorp myAbsorp){
    float alpha= 0.992;
    float valeurACR;
    float valeurACIR;
    float Yacr=0;
    float Yacir=0;
    float Xacr=0;
    float Xacir=0;


    //filtrage acR:
    valeurACR = myAbsorp.acr - Xacr  + alpha *Yacr; //on filtre la valeur de ACr
    Xacr=myAbsorp.acr; //Xacr mémorise la valeur précédente de acr
    Yacr=valeurACR; //Yacr mémorise la précédente valeur filtrée

    //filtrage acIR:
    valeurACIR = myAbsorp.acir - Xacir + alpha *Yacir; //on filtre la valeur de ACir
    Xacir=myAbsorp.acir;//Xacir mémorise la valeur précédente de acir
    Yacir=valeurACIR; //Yacir mémorise la pécédente valeur filtrée
}
