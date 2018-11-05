#include "../Deplacer/key_pressed.h"

char ** allocation_dyn_mat(int nbL, int nbC){
	char ** mat = malloc(nbL * sizeof(char *));

	for (int i = 0; i < nbL; i++){
		*(mat + i) = malloc(nbC);
	}
	return mat;
}

void chargement_mat(int nbL, int nbC, char ** mat){
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
}

void affichage_mat(int nbL, int nbC, char ** mat){
	for (int i = 0; i < nbL; i++){
		for (int j = 0; j < nbC; j++){
			if (mat[i][j] == 'X'){
				printf("%s▯", NORMAL);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'P'){
				printf("%s▯", YELLOW);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'M'){
				printf("%s☲", BLACK);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'C'){
				printf("%s▯", WHITE);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'W'){
				printf("%s▇", CYAN);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'Y'){
				printf("%s☿", GREEN);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'B'){
				printf("%s☢", REDCLIGNOTANT);
				printf("%s", NORMAL);
			}
			else printf("%c", mat[i][j]);
		}
		printf("\n");
	}
}

void affichage_mat_simple(int nbL, int nbC, char ** mat){
	for (int i = 0; i < nbL; i++){
		for (int j = 0; j < nbC; j++){
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}
}
