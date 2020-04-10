#include "fir.h"
#include "fichiers.h"

absorp firTest(char* filename){
    absorp	myAbs;
    absorp	myAbs_new;
    FILE* fichier=initFichier(filename);    //je défini mon fichier ayant toutes les valeurs
    int etat_fichier=0;
    float** buffer= init_fir();     //tableau 2 dimensions qui va garder en mémoire les 51 entrées x(n) de acr du filtre FIR sur la première ligne et celles de acir sur la deuxième ligne
    myAbs_new=lireFichier(fichier, &etat_fichier);
    while(etat_fichier != EOF){     //on lit le fichier et filtre les données tant qu'on est pas arrivé à la fin du fichier
        myAbs=FIR(myAbs_new, buffer);     //on applique à la structure le filtre FIR
        myAbs_new=lireFichier(fichier, &etat_fichier); //on prend de nouvelles valeurs
    }
    finFichier(fichier);
    fin_fir(buffer); //on libère la mémoire allouée pour le tableau
    return myAbs;
}

float** init_fir(){
    float ** buffer; //déclaration d'un double pointeur pour créer un tableau à  deux dimensions
    int i;
    int j;
    buffer = malloc (2 * sizeof (float *)); // 2 lignes, la première pour garder les valeurs acr et la deuxième pour les valeurs acir
    if(buffer != NULL){ //on vérifie que la mémoire a bien été alouée
        for (i = 0; i < 2; i++){
            buffer[i] = malloc (51 * sizeof (float)); //chaque ligne gardera en mémoire 51 valeurs correspondant aux entrées précédentes
            if (buffer[i] != NULL){ //on vérifie que la mémoire a bien été alouée
                for (j = 0; j < 51; ++j) {
                    buffer[i][j]=0; //initialisation de toutes les valeurs à zéro
                }
            }
        }
    }
    return buffer;
}

absorp FIR(absorp myAbsorb, float ** buffer){ //on applique un filtre
    int i;
    int j;
    for (i = 0; i < 2; ++i) { // on se déplace en ligne; pour i=0, on s'occupe des valeurs x acr; pour i=1, on s'occupe des valeurs x acir
        for (j = 50; j >0; --j) { //on se déplace en colonne
            buffer[i][j]=buffer[i][j-1]; //décalage de tous les x vers la droite pour pouvoir ajouter ensuite au début la nouvelle valeur xn en entrée
        }
    }
    buffer[0][0]=myAbsorb.acr; //ajout de la nouvelle entrée xn d'acr à la première place, on a donc buffer[0]=[x(n), x(n-1), ...]
    buffer[1][0]=myAbsorb.acir; //ajout de la nouvelle entrée xn d'acir à la première place, on a donc buffer[1]=[x(n), x(n-1), ...]
    int k;
    myAbsorb.acr=0;
    myAbsorb.acir=0;
    for (k=0; k<=50; k++){
        myAbsorb.acr += FIR_TAPS[k] * buffer[0][k]; //on modifie la valeur de acr , correspond au yn du filtre
        myAbsorb.acir += FIR_TAPS[k] * buffer[1][k]; //on modifie la valeur de acir, correspond au yn du filtre
    }
    return myAbsorb;
}


float FIR_TAPS[51]={ //tableau des coefficients h
        1.4774946e-019,
        1.6465231e-004,
        3.8503956e-004,
        7.0848037e-004,
        1.1840522e-003,
        1.8598621e-003,
        2.7802151e-003,
        3.9828263e-003,
        5.4962252e-003,
        7.3374938e-003,
        9.5104679e-003,
        1.2004510e-002,
        1.4793934e-002,
        1.7838135e-002,
        2.1082435e-002,
        2.4459630e-002,
        2.7892178e-002,
        3.1294938e-002,
        3.4578348e-002,
        3.7651889e-002,
        4.0427695e-002,
        4.2824111e-002,
        4.4769071e-002,
        4.6203098e-002,
        4.7081811e-002,
        4.7377805e-002,
        4.7081811e-002,
        4.6203098e-002,
        4.4769071e-002,
        4.2824111e-002,
        4.0427695e-002,
        3.7651889e-002,
        3.4578348e-002,
        3.1294938e-002,
        2.7892178e-002,
        2.4459630e-002,
        2.1082435e-002,
        1.7838135e-002,
        1.4793934e-002,
        1.2004510e-002,
        9.5104679e-003,
        7.3374938e-003,
        5.4962252e-003,
        3.9828263e-003,
        2.7802151e-003,
        1.8598621e-003,
        1.1840522e-003,
        7.0848037e-004,
        3.8503956e-004,
        1.6465231e-004,
        1.4774946e-019
};


void fin_fir(float** tableau) {// pour effacer le buffer à  2 dimensions qui a servi de mémoire
    free(tableau[0]);//on supprime la première ligne du tableau,on libère la mémoire allouée
    free(tableau[1]);//on supprime la deuxième ligne du tableau,on libère la mémoire allouée
    free(tableau);//on libère la mémoire allouée
}