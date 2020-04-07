#include "define.h"
//#include "stdbool.h"
// Definition de la structure
typedef struct{
    int tableau_acr[51]; //tableau pour garder en mémoire les valeurs de acr
    int tableau_acir[51]; //tableau pour garder en mémoire les valeurs de acr
} buffer;

absorp firTest(char* record1);

absorp FIR(absorp myAbsorb, float ** buffer);

float FIR_TAPS[51];

float** init_fir();//permet d'initialiser la structure qui gardera en mémoire les valeurs des entrées acr et acir du filtre FIR

void fin_fir(float** tableau);
