#include "mesure.h"
#include "fichiers.h"

oxy mesureTest(char* filename){
	oxy myOxy;
	absorp myAbsorp;
	myOxy.pouls=0;
	myOxy.spo2=0;
    int etat_fichier=0;
    myMesures mesure = init_mesure(); //initialisation de la structure pour garder en mémoire les valeurs d'un appel de fonction à l'autre
    FILE* fichier=initFichier(filename); //défini mon fichier ayant toutes les valeurs
    myAbsorp=lireFichier(fichier, &etat_fichier);
    while(etat_fichier!= EOF){ //lecture du fichier et calculs de Sp02 et du pouls grâce aux données tant qu'on est pas arrivé à la fin du fichier
        myOxy = MESURE(myAbsorp, &mesure, myOxy);
        myAbsorp=lireFichier(fichier, &etat_fichier);}
    finFichier(fichier); //fermeture du fichier
    fin_mesure(mesure.tab_bpm); //on supprime le tableau dynamique créé
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
    myMes.tab_bpm=malloc (2*sizeof (int *));//permet de stocker les deux dernières valeurs de bmp
    if(myMes.tab_bpm!=NULL){
        myMes.tab_bpm[0]=0;
        myMes.tab_bpm[1]=0; }
    return myMes;
}

int calcul_du_BMP(myMesures* myMes){
    int pouls_actuel;
    int pouls_moyen;
    pouls_actuel= 60 / (myMes->cpt_ech * 0.002);    //calcul du pouls actuel
    if(myMes->tab_bpm[0]!=0 && myMes->tab_bpm[1]!=0){   //il y a des valeurs précédentes de pouls afin de faire une moyenne
        pouls_moyen= (myMes->tab_bpm[0] + myMes->tab_bpm[1] + pouls_actuel)/3;  //on fait la moyenne du pouls avec les deux dernières valeurs
        myMes->tab_bpm[1] = myMes->tab_bpm[0];  //on translate les valeurs de pouls sauvegardées pour ajouter la nouvelle valeur du pouls
        myMes->tab_bpm[0] = pouls_actuel;   //ajout de la nouvelle valeur pouls
    } else{
        if(myMes->tab_bpm[0]==0 && myMes->tab_bpm[1]==0){   //il n'y a aucune valeur de sauvegardée de précédent bmp
            myMes->tab_bpm[0]=pouls_actuel;     //on sauvegarde la valeurs de bmp actuel pour le prochain calcul pour pouvoir faire un moyenne
            pouls_moyen=pouls_actuel;
        } else{     //il n'y a qu'une valeur de BPM sauvegardée, on fait un moyenne avec celle-ci
            pouls_moyen= (myMes->tab_bpm[0] + pouls_actuel)/2;  //on calcul notre pouls moyen
            myMes->tab_bpm[1] = myMes->tab_bpm[0];  //on translate les valeurs de pouls sauvegardées pour ajouter la nouvelle valeur du pouls
            myMes->tab_bpm[0] = pouls_actuel;   //ajout de la nouvelle valeur de pouls
        }
    }
    return pouls_moyen;
}

int calcul_de_SPO2(absorp myAbs, myMesures* myMes){
    int spo2;
    myMes->ratio = ((myMes->max_acr - myMes->min_acr)/myAbs.dcr ) / ((myMes->max_acir - myMes->min_acir)/myAbs.dcir ); //calcul du ratio RsIR
    if(myMes->ratio>=0.4 && myMes->ratio<=1){
        spo2= -25*myMes->ratio +110; //calcul Sp02 à partir de la pente du graphe "correspondance entre RsIR et SpO2"
    }
    if(myMes->ratio>1 && myMes->ratio<=3.4){
        spo2= (-100/3)*myMes->ratio +(350/3); //calcul Sp02 à partir de la pente du graphe "correspondance entre RsIR et SpO2"
    }
    return spo2;
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
            }
            break;
        case 2://début d'une période, on commence à calculer le nombre d'échantillons sur une période
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
                myOxy.pouls= calcul_du_BMP(myMes);
                myOxy.spo2= calcul_de_SPO2(myAbsorp,myMes);
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

void fin_mesure(int* tableau1){
    free(tableau1);
}