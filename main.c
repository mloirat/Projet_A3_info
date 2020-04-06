#include <stdio.h>
#include "affichage.h"
#include "define.h"

int main() {
    printf("Hello, World!\n");
    oxy myOxygene ;
    myOxygene.spo2=91;
    myOxygene.pouls=130;
    affichage(myOxygene);
    return 0;
}