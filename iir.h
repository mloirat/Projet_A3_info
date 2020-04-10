#ifndef IIR_H
#define IIR_H
#include "define.h"

//Fonctions :
absorp iirTest(char* filename); //fonction qui appelle la fonction IIR avec le fichier de données

float* init_iir(); //initialisation du tableau de sauvegarde

absorp IIR(absorp myAbsorp, float* parametre_irr); //permet d'appliquer le filtre IIR à la structure myAbsorp

void fin_iir(float* tableau); //permet de libérer la mémoire du tableau de sauvegarde

#endif