#include "define.h"


//Fonctions :

absorp iirTest(char* filename); //fonction qui appelle la fonction IIR avec le fichier de données

absorp IIR(absorp myAbsorp, float* param_iir); //filtre IIR

float* init_iir(); //initialisation du tableau

void fin_iir(float* tableau); //permet de libérer la mémoire du tableau