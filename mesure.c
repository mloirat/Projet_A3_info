#include "mesure.h"
#include "fichiers.h"

oxy mesureTest(char* filename){
	oxy myOxy;
	absorp myAbsorp;
    int etat_fichier=0;
    myMesures mesure = init_mesure();
    FILE* fichier=initFichier(filename); //défini mon fichier ayant toutes les valeurs
    myAbsorp=lireFichier(fichier, &etat_fichier);
    while(etat_fichier!= EOF){ //lecture du fichier et calcul la saturation Sp02 et le pouls grâce aux données tant qu'on est pas arrivé à la fin du fichier
        myOxy = MESURE(myAbsorp, &mesure, myOxy);
        myAbsorp=lireFichier(fichier, &etat_fichier);
    }
    finFichier(fichier);
    fin_mesure(mesure.tab_bpm,mesure.tab_sp02);
	return myOxy;
}

myMesures init_mesure(){//créer une structure MyMesures, initialisation de toutes les valeurs à zéro
    myMesures myMes;
    myMes.cpt_ech=0;
    myMes.etat=0;
    myMes.min_acr=0;
    myMes.max_acr=0;
    myMes.min_acir=0;
    myMes.max_acir=0;
    myMes.tab_bpm=malloc (2*sizeof (float *));//permet de stocker les deux dernières valeurs de bmp
    if(myMes.tab_bpm!=NULL){
        myMes.tab_bpm[0]=0;
        myMes.tab_bpm[1]=0; }
    myMes.tab_sp02=malloc (2*sizeof (float *));//permet de stocker les deux dernières valeurs de bmp
    if(myMes.tab_sp02!=NULL){
        myMes.tab_sp02[0]=0;
        myMes.tab_sp02[1]=0; }
    return myMes;
}

oxy MESURE(absorp myAbsorp, myMesures* myMes, oxy myOxy){
    switch (myMes->etat) {
        case 0: //permet de fixer un premier repère pour calculer la periode
            if (myAbsorp.acr<0){//dépassement de zéro, front descendant
                myMes->etat=1;
            }
            break;
        case 1: //on se calibre sur la courbe,
            if (myAbsorp.acr>0){//dépassement du zéro, front montant
                myMes->etat=2;
                myMes->cpt_ech=0;//on va pouvoir commencer à compter le nombre d'echantillon par periode
            }
            break;
        case 2://début d'une période, on commence à calculer le nombre d'échantillions sur une période
            myMes->cpt_ech++;
            if (myAbsorp.acr> myMes->max_acr) { //on récupère la valeur maximale de acr de la période
                myMes->max_acr=myAbsorp.acr;
            }
            if (myAbsorp.acir> myMes->max_acir) { //on récupère la valeur maximale de acir de la période
                myMes->max_acir=myAbsorp.acir;
            }
            if (myAbsorp.acr<0){//dépassement du zéro, front descendant
                myMes->etat=3;}
            break;
        case 3:
            myMes->cpt_ech++;
            if (myAbsorp.acr<myMes->min_acr) { //on récupère la valeur minimale de acr de la période
                myMes->min_acr=myAbsorp.acr;
            }
            if (myAbsorp.acir<myMes->min_acir) { //on récupère la valeur minimale de acir de la période
                myMes->min_acir=myAbsorp.acir;
            }
            if (myAbsorp.acr>0){//dépassement du zéro, front montant, on vient d'obtenir une période
                int pouls_actuel = 60/(myMes->cpt_ech * 0.002);//calcul du pouls actuel
                if(myMes->tab_bpm[0]!=0 && myMes->tab_bpm[1]!=0){//il y a des valeurs précédentes de pouls afin de faire une moyenne
                    myOxy.pouls=(myMes->tab_bpm[0]+myMes->tab_bpm[1]+pouls_actuel)/3; //on fait la moyenne du pouls avec les deux dernières valeurs
                    myMes->tab_bpm[1]=myMes->tab_bpm[0];//on translate les valeurs de pouls sauvegardées pour ajouter la nouvelle valeur du pouls
                    myMes->tab_bpm[0]=pouls_actuel; //ajout de la nouvelle valeur pouls
                } else{
                    myOxy.pouls=pouls_actuel;//il n'y a pas deux valeurs précédentes de pouls, on ne fait pas de moyenne
                }
                myMes->ratio=((myMes->max_acr - myMes->min_acr)/myAbsorp.dcr ) / ((myMes->max_acir - myMes->min_acir)/myAbsorp.dcir ); //calcul du ratio RsIR
                int sp02_actuel;
                if(myMes->ratio>=0.4 && myMes->ratio<=1){
                    sp02_actuel= -25*myMes->ratio +110; //calcul Sp02 à partir de la pente du graphe "correspondance entre RsIR et SpO2"
                }
                if(myMes->ratio>1 && myMes->ratio<=3.4){
                    sp02_actuel=myOxy.spo2= (-100/3)*myMes->ratio +(350/3); //calcul Sp02 à partir de la pente du graphe "correspondance entre RsIR et SpO2"
                }
                if(myMes->tab_sp02[0]!=0 && myMes->tab_sp02[1]!=0){//il y a des valeurs précédentes de sp02 afin de faire une moyenne
                    myOxy.spo2=(myMes->tab_sp02[0]+myMes->tab_sp02[1]+pouls_actuel)/3; //on fait la moyenne de sp02 avec les deux dernières valeurs
                    myMes->tab_sp02[1]=myMes->tab_sp02[0];//on translate les valeurs de sp02 sauvegardées pour ajouter la nouvelle valeur du sp02
                    myMes->tab_sp02[0]=sp02_actuel; //ajout de la nouvelle valeur sp02
                } else{
                    myOxy.spo2=sp02_actuel;//il n'y a pas deux valeurs précédentes de sp02, on ne fait pas de moyenne
                }
                myMes->etat=2; //on recommence une période
                myMes->cpt_ech=0; //on remet le compteur à zéro
                myMes->max_acr=0; //on remet les valeurs extrèmes à zéro
                myMes->min_acr=0;
                myMes->max_acir=0;
                myMes->min_acir=0;
            }
            break;
        default:
            break;
    }
    return myOxy;
}

void fin_mesure(float* tableau1, float* tableau2){
    free(tableau1);
    free(tableau2);
}