#include "define.h"

//Fonctions:
absorp firTest(char* record1); //fonction qui appelle la fonction FIR avec le fichier contenant les données

absorp FIR(absorp myAbsorb, float ** buffer); //filtre FIR

float FIR_TAPS[51]; //tableau de coefficients h

float** init_fir(); //permet d'initialiser la structure qui gardera en mémoire les valeurs des entrées acr et acir du filtre FIR

void fin_fir(float** tableau); //permet de libérer la mémoire allouée
