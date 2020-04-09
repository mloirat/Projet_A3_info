#include "lecture.h"
#include "fichiers.h"
#include "string.h"
absorp lecture(FILE* file_pf, int* file_state){
    absorp myAbsorp;
    int myCharactere;
    int cpt_variable;
    int coeff;
    int nombre;
    cpt_variable=0;
    coeff=1000;
    nombre=0;
    do{
        myCharactere=fgetc(file_pf);        //printf("%i, %c\n",myCharactere,myCharactere);
        if(myCharactere>47 && myCharactere<58){ //le caractere correspond à un decimal qui faut en ascii un chiffre compris entre 0 et 9
            printf("coef %d   ",coeff);
            myCharactere=myCharactere-48;
            nombre+=myCharactere*coeff;
            coeff=coeff/10;
        }
        if(myCharactere==44){   //le caractere correspond à une virgule, on passe à une autre variable
            switch (cpt_variable){
                case 0: //nous sommes à la première variable soit acr
                    myAbsorp.acr=nombre;
                    printf("acr vaut %d\n",myAbsorp.acr);
                    cpt_variable=1;
                    break;
                case 1: //nous sommes à la deuxième variable soit acir
                    myAbsorp.acir=nombre;
                    printf("acir vaut %d\n",myAbsorp.acir);
                    cpt_variable=2;
                    break;
                case 2://nous sommes à la troisième variable soit dcr
                    myAbsorp.dcr=nombre;
                    printf("dcr vaut %d\n",myAbsorp.dcr);
                    cpt_variable=3;
                    break;
                case 3://nous sommes à la quatrième variable soit dcir
                    myAbsorp.dcir=nombre;
                    printf("dcir vaut %d\n",myAbsorp.dcir);
                    cpt_variable=0;
                default:
                    break;
            }
            coeff=1000;
            nombre=0;
        }
    }while(myCharactere!=EOF);
   // *file_state=EOF;
    return myAbsorp; // return EOF flag
}


