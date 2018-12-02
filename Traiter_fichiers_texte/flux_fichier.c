#include "../Tirer/tirer_obus.h"

char **creer_charger_map(int nbL, int nbC, char *file_name){

	char **mat = allocation_dyn_mat(nbL, nbC);
	int car = 0, i = 0, j = 0;
	FILE* fichier = fopen(file_name, "r");

	if (fichier != NULL){
        	while (car != EOF && i < nbL && j < nbC){
		  		
			car = fgetc(fichier);
			if ((char)car != '\n'){			
				mat[i][j] = (char)car;			
				j++;
				
				if (j == (nbC)){ // On revient à la ligne
					j = 0;
					i++;
				}	
			}	
        	}

        	fclose(fichier);
    	}else printf("\nLe fichier n'existe pas : %s.\n", file_name);
    	
    	return mat;
}

void afficher_fichier(char *file_name){

	int car = 0, i = 0, j = 0;
	
	FILE* fichier = NULL;
	fichier = fopen(file_name, "r");

	if (fichier != NULL){
		//printf("\n");
        	do{
			car = fgetc(fichier);
			if ((char)car != '\n' && (char)car != EOF){						
				if (j == (LARGEURMAP)){ // On revient à la ligne
					j = 0;
					i++;
				}
				gotoxy(i, j);
				printf("%c", (char)car);
				j++;
			}
			
        	}while (car != EOF);

        	fclose(fichier);
    	}else printf("\nLe fichier n'existe pas : %s.\n", file_name);
}

void init_carrosseries(){
	// On initialise les carrosseries des tanks
	carrosserieWTH = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/weak_tank/weak_tank_haut");
	carrosserieWTG = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/weak_tank/weak_tank_gauche");
	carrosserieWTD = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/weak_tank/weak_tank_droite");
	carrosserieWTB = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/weak_tank/weak_tank_bas");

	carrosserieMTH = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/medium_tank/medium_tank_haut");
	carrosserieMTG = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/medium_tank/medium_tank_gauche");
	carrosserieMTD = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/medium_tank/medium_tank_droite");
	carrosserieMTB = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/medium_tank/medium_tank_bas");

	carrosserieSTH = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/strong_tank/strong_tank_haut");
	carrosserieSTG = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/strong_tank/strong_tank_gauche");
	carrosserieSTD = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/strong_tank/strong_tank_droite");
	carrosserieSTB = creer_charger_map(LONGUEURTANK, PETITASCII, "../Modèle/Fichiers_texte_tank/strong_tank/strong_tank_bas");
	
	carrosserieTankDetruit = creer_charger_map(LONGUEURTANK, 15, "../Modèle/Fichiers_texte_tank/TankDetruit");
}
