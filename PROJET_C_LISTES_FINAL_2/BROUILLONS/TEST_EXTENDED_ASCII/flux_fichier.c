#include "treatment_mat.c"

char **creer_charger_map(int nbL, int nbC, char *file_name){

	char **mat = allocation_dyn_mat(nbL, nbC);
	int car = 0, i = 0, j = 0;
	
	FILE* fichier = NULL;
	fichier = fopen(file_name, "r");
	
	long int taille = 0;

	if (fichier != NULL){
        	while (car != EOF && i < nbL && j < nbC){
		  		
			car = fgetc(fichier);
			if ((char)car != '\n'){			
				mat[i][j] = (char)car;	
				taille = taille + sizeof(car);		
				j++;
				
				if (j == (nbC)){ // On revient à la ligne
					j = 0;
					i++;
				}	
			}	
        	}
		printf("%ld", taille);
        	fclose(fichier);
    	}else printf("\nLe fichier n'existe pas : %s.\n", file_name);
    	
    	return mat;
}

void afficher_fichier(int nbL, int nbC, char *file_name){

	int car = 0;
	
	FILE* fichier = NULL;
	fichier = fopen(file_name, "r");

	if (fichier != NULL){
		printf("\n");
        	do{
			car = fgetc(fichier);
			printf("%c", (char)car);
			
        	}while (car != EOF);

        	fclose(fichier);
    	}else printf("\nLe fichier n'existe pas : %s.\n", file_name);
    	
}

// Lecture du fichier avec n'importe quel caractère
void creer_charger_map_new_version(char *file_name){

	FILE* fichier = NULL;
    int caractereActuel = 0;
 
    fichier = fopen(file_name, "r");
 
    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {
            caractereActuel = fgetc(fichier);
            /*if (caractereActuel == ' '){
            	printf(" "); printf(" "); printf(" ");
            }
            else */printf("%c", caractereActuel);
            
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
 
        fclose(fichier);
    }
}

int main(){

	/*int tailleAsciiCharPETIT = 15;
	int tailleAsciiCharGIGA = 20;
	
	char **mat = creer_charger_map(3, tailleAsciiCharPETIT, "test");
	printf("\n");
	affichage_mat(3, tailleAsciiCharPETIT, mat);
	
	printf("\n");
	
	char **mat3 = creer_charger_map(3, tailleAsciiCharGIGA, "test3");
	printf("\n");
	affichage_mat(3, tailleAsciiCharGIGA, mat3);
	
	
	printf("\n");*/
	
	creer_charger_map_new_version("test4");
	return 0;
}
