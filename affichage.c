#include "affichage.h"
#include <stdio.h>
#include <unistd.h>

void affichage(oxy myOxy){
    if( access( ".verrouData", F_OK ) != -1 ){ // Fichier verrou existe
        printf("Attention l'application java lit le Data.txt");//on supprime le fichier verrou pour que l'application java puisse lire le fichier Data.txt

    }else{// Fichier verrou n'existe pas
        FILE* verrou = fopen(".verrouData", "r");//ce fichier va permettre de bloquer la lecture de l'application java sur le fichier Data.txt
        //"r" = ouverture en lecture seule

        FILE* fichier_data = fopen("Data.txt", "w+"); //le fichier data.txt où l'on va écrire les nouvelles valeurs de SpO2 et BMP
        //"w+"= ouverture en écriture et lecture, en effaçant au préalable les anciennes valeurs
        if (fichier_data != NULL){  //on peut lire le fichier Data.txt
            fprintf(fichier_data, "%i\n%i", myOxy.spo2,myOxy.pouls); //on écrit les nouvelles valeurs de Sp02 et BMP dans le fichier Data.txt
            fclose(fichier_data); //on referme le fichier data.txt
        }
        remove(".verrouData");
    }
}

