#include "iir.h"

absorp iirTest(char* record1_fir.dat){
	absorp	myAbsorp;
	IIR(absorp.acr, ancienneValeur);

	return myAbsorp;

}

float IIR(float absorp.acr, float absorp.acir){
    int alpha= 0.992;
    int y =0;
    for (i=0; i<=51; i++){
        absorp.acr[n] = absorp.acr[n] - absorp.acr[n-1] + alpha *y;
        y=absorp.acr[n]
        absorp.acir[n] = absorp.acir[n] - absorp.acir[n-1] + alpha *absorp.acr[n-1];
    }