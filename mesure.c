#include "mesure.h"

oxy mesureTest(char* filename){
	oxy myOxy;
	return myOxy;

}

myMesures init_mesure(){//initialisation de toutes les valeurs à zéro
    myMesures myMes_init;
    myMes_init.cpt_ech=0;
    myMes_init.etat=0;
    myMes_init.min_acr=0;
    myMes_init.max_acr=0;
    myMes_init.min_acir=0;
    myMes_init.max_acir=0;
    return myMes_init;
}

oxy MESURE(absorp myAbsorp, myMesures myMes){
    oxy myOxy;
    switch (myMes.etat) {
        case 0: //permet de fixer un premier repère pour calculer la periode
            if (myAbsorp.acr<0){//dépassement de zéro, front descendant
                myMes.etat=1;}
            break;
        case 1: //on se calibre sur la courbe,
            if (myAbsorp.acr>0){//dépassement du zéro, front descendant
                myMes.etat=2;
                myMes.cpt_ech=0;//on va pouvoir commencer à compter le nombre d'echantillon par periode
            }
            break;
        case 2://début d'une période, on commence à calculer le nombre d'échantillions sur une période
            myMes.cpt_ech++;
            if (myAbsorp.acr> myMes.max_acr) { //on récuprère la valeur maximale de acr de la période
                myMes.max_acr=myAbsorp.acr;
            }
            if (myAbsorp.acir> myMes.max_acir) { //on récuprère la valeur maximale de acir de la période
                myMes.max_acir=myAbsorp.acir;
            }
            if (myAbsorp.acr<0){//dépassement du zéro, front descendant
                myMes.etat=3;}
            break;
        case 3:
            myMes.cpt_ech++;
            if (myAbsorp.acr<myMes.min_acr) { //on récuprère la valeur minimale de acr de la période
                myMes.min_acr=myAbsorp.acr;
            }
            if (myAbsorp.acir<myMes.min_acir) { //on récuprère la valeur minimale de acir de la période
                myMes.min_acir=myAbsorp.acir;
            }
            if (myAbsorp.acr>0){//dépassement du zéro, front montant, on vient d'obtenir une période
                myOxy.pouls = 60/(myMes.cpt_ech * 0.002);//calcul du BPM

                myMes.ratio=( (myMes.max_acr - myMes.min_acr)/myAbsorp.dcr ) / ((myMes.max_acir - myMes.min_acir)/myAbsorp.dcir ); //calcul du ratio RsIR
                if(myMes.ratio>=0.4 && myMes.ratio<=1){
                    myOxy.spo2= -25*myMes.ratio +110; //calcul Sp02 à partir de la pente du graphe "correspondance entre RsIR et SpO2"
                }
                if(myMes.ratio>1 && myMes.ratio<=3.4){
                    myOxy.spo2= -25*myMes.ratio +110; //calcul Sp02 à partir de la pente du graphe "correspondance entre RsIR et SpO2"
                }

                myMes.etat=2; //on recommence une période
                myMes.cpt_ech=0; //on remet le compteur à zéro
                myMes.max_acr=0; //on remet les valeurs extrèmes à zéro
                myMes.min_acr=0;
                myMes.min_acir=0;
                myMes.max_acir=0;
            }
            break;
        default:
            break;
    }
}



