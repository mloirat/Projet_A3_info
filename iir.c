#include "iir.h"
#include "fichiers.h"

absorp iirTest(char* filename){
	absorp	myAbs;
    absorp	myAbs_new;
	int etat_fichier=0;
    FILE* fichier=initFichier(filename); //je défini mon fichier ayant toutes les valeurs
    float* parametre_irr=init_iir(); //tableau de 4 éléments qui garde en mémoire les valeurs n-1 de x et y pour acR et acIR
    myAbs_new=lireFichier(fichier, &etat_fichier);
    while(etat_fichier != EOF){ //lecture du fichier et application du filtre sur les données tant qu'on est pas arrivé à la fin du fichier
        myAbs=IIR(myAbs_new, parametre_irr);
        myAbs_new=lireFichier(fichier, &etat_fichier);
    }
    finFichier(fichier);
    fin_iir(parametre_irr); //on libère la mémoire allouée pour le tableau
	return myAbs;
}

float* init_iir(){ //création d'un tableau de 4 éléments pour stocker les valeurs n-1 de y et de x pour acR et acIR
    int i;
    float * tableau=malloc(4 * sizeof(float)); //on alloue un tableau de 4 éléments
    for (i=0; i<=3; i++){ //on remplit le tableau de 0 au début pour initialiser
        if(tableau != NULL) {
            tableau[i]=0; //on initialise à zéro les valeurs contenues
        }
    }
    return tableau;
}

absorp IIR(absorp myAbsorp, float* parametre_irr){
    float alpha= 0.992; //constante dans la formule du filtre IIR
    float valeurACR;
    float valeurACIR;

    //FILTRAGE de ACR:
    valeurACR = myAbsorp.acr - parametre_irr[0] + alpha * parametre_irr[1]; //on filtre la valeur de acr
    parametre_irr[0]=myAbsorp.acr; //la précédente valeur de acr est mémorisée dans parametre_irr à l'indice 0
    parametre_irr[1]=valeurACR; //la valeur filtrée de acr est mémorisée dans parametre_irr à l'indice 1
    myAbsorp.acr=valeurACR; //la valeur filtrée est mise dans la structure

    //FILTRAGE de ACIR:
    valeurACIR = myAbsorp.acir - parametre_irr[2] + alpha * parametre_irr[3]; //on filtre la valeur de acir
    parametre_irr[2]=myAbsorp.acir; //la précédente valeur de acir est mémorisée dans parametre_irr indice 2
    parametre_irr[3]=valeurACIR; //la  valeur filtrée de acir est mémorisée dans parametre_irr indice 3
    myAbsorp.acir=valeurACIR; //la valeur filtrée est mise dans la structure

    return myAbsorp;
}

void fin_iir(float* tableau){ //tableau qui a servi de mémoire pour les anciennes valeurs n-1
    free(tableau); //libération de la mémoire allouée
}