#include "fir.h"

absorp firTest(char* record1.dat){
	absorp	myAbsorp;
	return myAbsorp;

}

#il faut creer un tableau de acR et un tableau de acIR

float FIR(ACR[], ACIR[], h[]){
    int n=50; #mettre length de x plutot
    int y=0
    for (int k=0; k<=n; k++){
        yancien=y;
        y += h[k] * x[n-k];
    }
    return y;
}
