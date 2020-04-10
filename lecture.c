#include "lecture.h"
#include "fichiers.h"

absorp lecture(FILE* file_pf, int* file_state){
    absorp myAbs;
    int etat_trame; //permet de savoir si la trame relevée est correcte, si il vaut 1 elle est correcte, sinon 0
    int myCharactere;
    float tableau[20] = {0};
    int i;
    int cpt_stop; //permet de compter le nombre de virgules et de LF dans la trame
    int cpt_chiffre ; //permet de compter le nombre de chiffre dans la trame
    etat_trame=0;
    while (etat_trame!=1) {//tant que la trame n'est pas correcte
        cpt_stop = 0;
        i = 0;
        myCharactere = 0;
        cpt_chiffre= 0;
        while (myCharactere != 10 && myCharactere != EOF) {//le 10 correspond à un LF
            myCharactere = fgetc(file_pf); //on récupère un nouveau caractère du fichier
            if (myCharactere == EOF) { //on a atteind la fin du fichier
                *file_state = EOF;
                etat_trame=1;
            }
            if (myCharactere == 44 || myCharactere == 10) {//le 44 correspond à une virgule et le 10 à un LF
                cpt_stop++;
            }
            if (myCharactere > 47 && myCharactere < 58) {
                myCharactere = myCharactere - 48;//on convertit un code ASCII decimal vers un  ASCII charactere
                cpt_chiffre++;
            }
            tableau[i] = myCharactere; //on enregistre les éléments de la trame
            i++;
        }
        if (cpt_stop == 4 && cpt_chiffre == 16) {//la trame est bonne, elle contient bien le bon nombre d'éléments, on affecte les valeurs
            etat_trame = 1; //on signale que la trame est bonne
            myAbs.acr=(tableau[0]*1000 + tableau[1]*100 + tableau[2]*10 + tableau[3]) -2048; //on récupère le nombre en entier de acr et on recentre autour du zéro
            myAbs.dcr=(tableau[5]*1000 + tableau[6]*100 + tableau[7]*10 + tableau[8] ) ; //on récupère le nombre en entierde dcr
            myAbs.acir=(tableau[10]*1000 + tableau[11]*100 + tableau[12]*10 + tableau[13] ) -2048; //on récupère le nombre en entier de acir et on recentre autour du zéro
            myAbs.dcir=(tableau[15]*1000 + tableau[16]*100 + tableau[17]*10 + tableau[18]); //on récupère le nombre en entier de dcir
        }else{
            myCharactere=fgetc(file_pf);
            if(myCharactere == EOF) {//on a atteind la fin de fichier
                *file_state = EOF;
            }
        }
    }
    myCharactere=fgetc(file_pf); //on récupère un nouveau caractère du fichier
    if(myCharactere == EOF){ //on a atteind la fin du fichier
        *file_state=EOF;
    }
    return myAbs;
}


