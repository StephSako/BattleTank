#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

char ** allocation_dyn_mat(int nbL, int nbC){
	char ** mat = malloc(nbL * sizeof(char *));

	for (int i = 0; i < nbL; i++){
		*(mat + i) = malloc(nbC);
	}
	return mat;
}

void affichage_mat(int nbL, int nbC, char ** mat){
	for (int i = 0; i < nbL; i++){
		for (int j = 0; j < nbC; j++){
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}
}










/*void chargement_mat(int nbL, int nbC, char ** mat){
	for (int i = 0; i < nbL; i++){
		for (int j = 0; j < nbC; j++){
			*(*(mat + i) + j) = '$';
		}
	}
}

void lib_mat(int nbL, char ** mat){
	for (int i = 0; i < nbL; i++){
		free(*(mat + i));
		*(mat+i) = NULL;
	}
}*/
