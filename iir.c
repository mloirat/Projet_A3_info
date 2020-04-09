#include "iir.h"
#include "fichiers.h"

absorp iirTest(char* filename){
	absorp	myAbsorp;
    absorp	myAbsorp_new;
	int etat=0;
    FILE* fichier=initFichier(filename); //je défini mon fichier ayant toutes les valeurs
    float* param_iir=init_iir(); //tableau de 4 éléments qui garde en mémoire les valeurs n-1 de x et y pour acR et acIR
    myAbsorp_new=lireFichier(fichier, &etat);
    while(etat!= EOF){ //on lis le fichier et filtre les données tant qu'on est pas arrivé à la fin du fichier
        myAbsorp=IIR(myAbsorp_new, param_iir);
        myAbsorp_new=lireFichier(fichier, &etat);
    }
    finFichier(fichier);
    fin_iir(param_iir); //on libère la mémoire allouée pour le tableau
	return myAbsorp;
}

float* init_iir(){ //tableau de 4 elements pour stocker les valeurs n-1 de y et de x pour acR et acIR
    int i;
    float * sauvegarde=malloc(4* sizeof(float)); //on alloue un tableau de 4 éléments
    for (i=0; i<=3; i++){ //on rempli le tableau de 0 au début pour initialiser
        if(sauvegarde != NULL) {
            sauvegarde[i]=0;
        }
    }
    return sauvegarde;
}

absorp IIR(absorp myAbsorp, float* param_iir){
    float alpha= 0.992; //constante deans la formule du filtre IIR
    float valeurACR;
    float valeurACIR;

    //FILTRAGE acR:
    valeurACR = myAbsorp.acr - param_iir[0]  + alpha *param_iir[1]; //on filtre la valeur de ACr
    param_iir[0]=myAbsorp.acr; //la précédente valeur de acR est mémorisée dans param_iir indice 0
    param_iir[1]=valeurACR; //la précédente valeur filtrée de acR est mémorisée dans param_iir indice 1
    myAbsorp.acr=valeurACR; //la valeur filtrée est mise dans la structure

    //FILTRAGE acIR:
    valeurACIR = myAbsorp.acir - param_iir[2] + alpha *param_iir[3]; //on filtre la valeur de ACir
    param_iir[2]=myAbsorp.acir; //la précédente valeur de acIR est mémorisée dans param_iir indice 2
    param_iir[3]=valeurACIR; //la précédente valeur filtrée de acIR est mémorisée dans param_iir indice 3
    myAbsorp.acir=valeurACIR; //la valeur filtrée est mise dans la structure

    return myAbsorp;
}


void fin_iir(float* tableau){ //tableau qui a servi de mémoire pour les anciennes valeurs n-1
    free(tableau); //on libère la mémoire allouée
}