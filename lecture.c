#include "lecture.h"
#include "fichiers.h"

absorp lecture(FILE* file_pf, int* file_state){
    absorp myAbs;
    int myCharactere;
    float tableau[20]={0};
    int i;
    int cpt_stop;
    cpt_stop=0;
    i=0;
    myCharactere=0;
    int cpt_chiffre=0;
    while(myCharactere != 10 && myCharactere != EOF){//10 correspond à un LF
        myCharactere=fgetc(file_pf);
        if(myCharactere == EOF){
            *file_state=EOF;
        }
        if(myCharactere == 44 || myCharactere == 10 ){//on a une virgule ou un LF
            cpt_stop++;
        }
        if(myCharactere > 47 && myCharactere < 58){
            myCharactere= myCharactere - 48;
            cpt_chiffre++;
        }
        tableau[i]=myCharactere;
        i++; //printf("mon caractere %d\n ",myCharactere);
    }
    if(cpt_stop==4 && cpt_chiffre == 16 ){//la trame est bonne on affecte les valeurs
        //printf("trame est bonne \n");
        myAbs.acr=(tableau[0]*1000 + tableau[1]*100 + tableau[2]*10 + tableau[3]) -2048;
        //printf(" acr = %f \n", myAbs.acr);
        myAbs.dcr=(tableau[5]*1000 + tableau[6]*100 + tableau[7]*10 + tableau[8] ) ;
        //printf(" dcr = %f \n", myAbs.dcr);
        myAbs.acir=(tableau[10]*1000 + tableau[11]*100 + tableau[12]*10 + tableau[13] ) -2048;
        //printf(" acir = %f \n", myAbs.acir);
        myAbs.dcir=(tableau[15]*1000 + tableau[16]*100 + tableau[17]*10 + tableau[18]);
        //printf(" dcir = %f \n", myAbs.dcir);
    }
    myCharactere=fgetc(file_pf);
    if(myCharactere == EOF){
        *file_state=EOF;
    }// return EOF flag
    //printf("acr= %f \n acir= %f \n dcr= %f \n dcir= %f \n", myAbs.acr, myAbs.acir, myAbs.dcr, myAbs.dcir);
    return myAbs;
}


