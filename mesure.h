#include "define.h"
typedef struct{
    int etat; //indice permettant de nous repérer par rapport aux périodes
    int cpt_ech; //compteur d'echantillons par période
    float min_acr; //variable permettant de récupérer la valeur la plus basse de acr de la période
    float max_acr; //variable permettant de récupérer la valeur la plus haute de acr la période
    float min_acir; //variable permettant de récupérer la valeur la plus basse de acir la période
    float max_acir; //variable permettant de récupérer la valeur la plus haute de acir la période
    float ratio; //ratio permettant d'avoir la saturation Sp02
    float *tab_bpm; //tableau gardant en mémoire les 2 dernières valeurs de bmp
    float *tab_sp02; //tableau gardant en mémoire les 2 dernières valeurs de sp02
} myMesures;

myMesures init_mesure();

oxy mesureTest(char* filename);

oxy MESURE(absorp myAbsorp, myMesures* myMes, oxy myOxy);

void fin_mesure(float* tableau1, float* tableau2);