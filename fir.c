#include "fir.h"
#include "fichiers.h"
//#include "stdio.h"
//#include "stdlib.h"

absorp firTest(char* record1){
	absorp	myAbsorp;
	return myAbsorp;

}

float** init_fir(){
    float ** tableau_sauvegarde; //déclaration d'un double pointeur pour créer un tableau à deux dimensions
    tableau_sauvegarde = malloc (2*sizeof (float *));// 2 lignes, la première pour garder les valeurs acr et la deuxième pour les valeurs acir
    if(tableau_sauvegarde != NULL){//on vérifie que la mémoire a bien été alouée
        for (int i = 0; i < 2; i++){
            tableau_sauvegarde[i] = malloc (51*sizeof (float));//chaque ligne aura un tableau de 51valeurs pour garder en mémoire les entrées précédentes
            if (tableau_sauvegarde[i] != NULL){//on vérifie que la mémoire a bien été alouée
                for (int j = 0; j < 51; ++j) {
                    tableau_sauvegarde[i][j]=0;//initialisation de toutes les valeurs à zéro
                }
            }
        }
    }
    return tableau_sauvegarde;
}

absorp FIR(absorp myAbsorb, float ** buffer){ //buffer est un tableau deux dimensions
    for (int i = 0; i < 2; ++i) {// on se déplace en ligne; pour i=0, on s'occupe des valeurs x acr; pour i=1, on s'occupe des valeurs x acir
        for (int j = 50; j >0; --j) { //on se déplace en colonne
            buffer[i][j]=buffer[i][j-1];//décalage de tous les x vers la droite pour pouvooir ajouter ensuite au début la nouvelle valeur xn en entrée
        }
    }
    buffer[0][0]=myAbsorb.acr;//ajout de la nouvelle entrée xn d'acr à la première place, on a donc buffer[0]=[x(n), x(n-1), ...]
    buffer[1][0]=myAbsorb.acir;//ajout de la nouvelle entrée xn d'acir à la première place, on a donc buffer[1]=[x(n), x(n-1), ...]
    for (int k=0; k<=50; k++){
        myAbsorb.acr += FIR_TAPS[k] * buffer[0][k]; //on modifie la valeur de acr , correspond au yn du filtre
        myAbsorb.acir += FIR_TAPS[k] * buffer[1][k]; //on modifie la valeur de acir, correspond au yn du filtre
    }
    return myAbsorb;
}


float FIR_TAPS[51]={
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

/*
// Definitions des fonctions de queueArray qu'on utlisera comme buffer
// Operations de creation
struct QueueArray* createEmptyQueueArray(){
    struct QueueArray *newQueueA = malloc(1 * sizeof(struct QueueArray));
    if (newQueueA != NULL) {
        newQueueA->size=0;
    }
}
//Autres operations
void enqueueArray(struct QueueArray* q, int item, bool* valid){
    if(isQueuearrayEmpty(q)){
        q->front=0;
        q->rear=0;
        q->elems[0]=item;
        q->size=1;
        *valid=true;
    }
    else if(q->size==MAX_SIZE){
        *valid=false;
    } else if(q->rear==MAX_SIZE){
        q->size++;
        *valid=true;
        q->elems[0]=item;
        q->rear++;
    }
    else{
        q->size++;
        *valid=true;
        q->elems[q->rear]=item;
        q->rear++;
    }
}
int headArray(struct QueueArray* q, bool* valid){
    if(isQueuearrayEmpty(q)){
        *valid=false;
    }else{
        *valid=true;
        return q->elems[q->front];
    }
}
int dequeueArray(struct QueueArray* q, bool* valid){
    if(isQueuearrayEmpty(q) | queueArraySize(q)==MAX_SIZE){
        *valid=false;
    } else if(q->front==MAX_SIZE){
        *valid=true;
        q->size--;
        int elem=q->elems[q->front];
        q->front=0;
        return elem;
    }
    else{
        *valid=true;
        q->size--;
        int elem=q->elems[q->front];
        q->front++;
        return elem;
    }

}
int queueArraySize(struct QueueArray* q){
    return q->size;
}
bool isQueuearrayEmpty(struct QueueArray* q){
    if(q->size==0){
        return true;
    } else{
        return false;
    }
}
void printQueueArray(struct QueueArray* q){
    if(q->rear<q->front){
        for(int i=q->front; i<q->size; i++){
            printf("%i ", q->elems[i]);
        }
        for (int j = 0; j <=q->rear ; ++j) {
            printf("%i ", q->elems[j]);
        }
    } else{
        for (int k = 0; k <q->size ; ++k) {
            printf("%i ", q->elems);
        }
    }
}
void deleteQueueArray(struct QueueArray* q){
    free(q);
}

 */