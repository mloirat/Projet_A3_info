#include "define.h"
//#include "stdbool.h"
// Definition de la structure
#define MAX_SIZE 30
typedef struct{
    int tableau_acr[51]; //tableau pour garder en mémoire les valeurs de acr
    int tableau_acir[51]; //tableau pour garder en mémoire les valeurs de acr
} buffer;

absorp firTest(char* record1);

absorp FIR(absorp myAbsorb, buffer tableau);

float FIR_TAPS[51];



buffer init_fir(void);//permet d'initialiser la structure qui gardera en mémoire les valeurs des entrées acr et acir du filtre FIR


/*
//definition de queueArray , qu'on utilisera pour faire le buffer
struct QueueArray{
    int size;
    int front;
    int rear;
    int elems[MAX_SIZE];
};

// Operations de creation
struct QueueArray* createEmptyQueueArray();
//Autres operations
void enqueueArray(struct QueueArray* q, int item, bool* valid); //permet de rajouter un élément de la structure
int headArray(struct QueueArray* q, bool* valid); //recupère le premier élément de la structure
int dequeueArray(struct QueueArray* q, bool* valid); //recupère le premier élément de la structure
int queueArraySize(struct QueueArray* q);
bool isQueuearrayEmpty(struct QueueArray* q);
void printQueueArray(struct QueueArray* q);
void deleteQueueArray(struct QueueArray* q);

*/