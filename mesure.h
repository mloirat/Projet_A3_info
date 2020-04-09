#ifndef MESURE_H
#define MESURE_H
#include "define.h"


typedef struct{
    int etat; //indice permettant de nous repérer par rapport aux périodes
    int cpt_ech; //compteur d'echantillons par période
    float min_acr; //variable permettant de récupérer la valeur la plus basse de acr de la période
    float max_acr; //variable permettant de récupérer la valeur la plus haute de acr la période
    float min_acir; //variable permettant de récupérer la valeur la plus basse de acir la période
    float max_acir; //variable permettant de récupérer la valeur la plus haute de acir la période
    float ratio; //ratio permettant d'avoir la saturation Sp02
    int *tab_bpm; //tableau gardant en mémoire les 2 dernières valeurs de bmp
} myMesures;

oxy mesureTest(char* filename);

myMesures init_mesure();

int calcul_du_BMP(myMesures* myMes);

int calcul_de_SPO2(absorp myAbs, myMesures* myMes);

oxy MESURE(absorp myAbsorp, myMesures* myMes, oxy myOxy);

void fin_mesure(int* tableau1);

#endif