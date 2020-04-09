#ifndef IIR_H
#define IIR_H
#include "define.h"

//Fonctions :
absorp iirTest(char* filename); //fonction qui appelle la fonction IIR avec le fichier de données

float* init_iir(); //initialisation du tableau

absorp IIR(absorp myAbsorp, float* param_iir); //filtre IIR

void fin_iir(float* tableau); //permet de libérer la mémoire du tableau

#endif