#include "iir.h"
#include "fichiers.h"


absorp iirTest(char* filename){
	absorp	myAbsorp;
	int etat=0;
    FILE* fichier=initFichier(filename);
    float* param_iir=init_iir();
    myAbsorp=lireFichier(fichier, &etat);
    while(etat!= EOF){
        myAbsorp=IIR(myAbsorp, param_iir);
        myAbsorp=lireFichier(fichier, &etat);
    }
    finFichier(fichier);
    fin_iir(param_iir);
	return myAbsorp;

}

absorp IIR(absorp myAbsorp, float* param_iir){
    float alpha= 0.992;
    float valeurACR;
    float valeurACIR;

    //filtrage acR:
    valeurACR = myAbsorp.acr - param_iir[0]  + alpha *param_iir[3]; //on filtre la valeur de ACr
    param_iir[0]=myAbsorp.acr; //la précédente valeur de acR est mémorisée dans myIIR indice 0
    param_iir[1]=valeurACR; //la précédente valeur filtrée de acR est mémorisée dans myIIR indice 1
    myAbsorp.acr=valeurACR; // la valeur filtrée est mise dans la structure

    //filtrage acIR:
    valeurACIR = myAbsorp.acir - param_iir[2] + alpha *param_iir[3]; //on filtre la valeur de ACir
    param_iir[2]=myAbsorp.acir;//la précédente valeur de acIR est mémorisée dans myIIR indice 2
    param_iir[3]=valeurACIR; //la précédente valeur filtrée de acIR est mémorisée dans myIIR indice 3
    myAbsorp.acir=valeurACIR; //la valeur filtrée est mise dans la structure

    return myAbsorp;
}

float* init_iir(){ //tableau de 4 elements pour stocker les valeurs n-1 de y et de x pour acR et acIR
    int i;
    float * sauvegarde=malloc(4* sizeof(float));
    for (i=0; i<=3; i++){
        if(sauvegarde != NULL) {
            sauvegarde[i]=0;
        }
    }
    return sauvegarde;
}


void fin_iir(float* tableau){//tableau qui a servi de mémoire
    free(tableau);//on libère la mémoire allouée
}