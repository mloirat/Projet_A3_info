#include <stdio.h>
#include <stdlib.h>
#include "define.h"

#ifndef FICHIERS_H
#define FICHIERS_H

FILE* initFichier(char* nomFichier );
absorp lireFichier(FILE* pf, int* etat);
void finFichier(FILE* pf);

#endif

