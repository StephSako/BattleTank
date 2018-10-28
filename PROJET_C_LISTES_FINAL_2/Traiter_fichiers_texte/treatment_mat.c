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
			//printf("%c", mat[i][j]);
			
			if (mat[i][j] == 'X'){
				printf("%s%c", WHITE, mat[i][j]);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'P'){
				printf("%s%c", YELLOW, mat[i][j]);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'C'){
				printf("%s%c", WHITE, mat[i][j]);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'E'){
				printf("%s%c", CYAN, mat[i][j]);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'Y'){
				printf("%s%c", GREEN, mat[i][j]);
				printf("%s", NORMAL);
			}
			else if (mat[i][j] == 'B'){
				printf("%s%c", REDCLIGNOTANT, mat[i][j]);
				printf("%s", NORMAL);
			}
			/*else if (mat[i][j] == 'B'){
				//printf("💣");
				//printf("\033[%d;%dH", (i), (j));
				//system("printf 💣");
				//system("printf '\033[5;20HQ'");
				//printf("\033[%d;%dH", (i+1), (j+1));
				//printf("\uHHHH💣");
				printf("\u8223");
			}*/
			else printf("%c", mat[i][j]);
		}
		printf("\n");
	}
}

OBUSP * allocation_dyn_tab(){
	return malloc(NBOBUSALLOWED * sizeof(OBUSP));
}

int * allocation_dyn_tab_repar_tank_ennemis(){
	return malloc(3 * sizeof(int));
}
