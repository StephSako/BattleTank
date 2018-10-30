#include "../TankEnnemis/TankEnnemis.h"

OBUSP * allocation_dyn_tab_obus(){
	return malloc(NBOBUSALLOWED * sizeof(OBUSP));
}

int * allocation_dyn_tab_repar_tank_ennemis(){
	return malloc(3 * sizeof(int));
}

void init_terminal(){
	system("clear"); // On nettoie le terminal
	system("setterm -cursor off"); // On n'affiche pas le curseur clignotant dans le terminal
	system("stty -echo"); // Ne pas afficher les lettres/codes flèches tappées dans le terminal
	
	NBOBUSALLOWED = 50; // On initialise le nombre d'obus autorisés à apparaitre à l'écran
	TabPointeursObus = allocation_dyn_tab_obus(); // Allocation dynamique du tableau de pointeurs d'obus
}

void quit_terminal(){
	system("clear");
	
	if (pioupiouAlive == 1 && joueurMort == 0 && key != 'q' && mode != 3) // Le joueur a gagné
		afficher_message(15, 60, "Vous avez gagné !!");
	else if (pioupiouAlive == 0 || joueurMort == 1) // Le joueur a perdu
		afficher_message(15, 60, "Vous avez perdu ...");
	else { // Sinon le joueur a quitté
		afficher_message(15, 60, "Vous quittez le jeu ...");
	}
	fflush(stdout);
	system("sleep 0.8");
	system("setterm -cursor on");
	system("stty echo");
	system("clear");
}

void initialiserLaPartieSelonLeMode(){
	
	// On initialise la répartition des différents types de tanks ennemis
	repartitionTankEnnemis = allocation_dyn_tab_repar_tank_ennemis();
	
	if (mode == 11){											// MODE TERMINAL FACILE
		true_map = creer_charger_map(LONGUEURMAP, LARGEURMAP, PATHMAPTERMINAL); // On initialise la map à afficher
		affichage_mat(LONGUEURMAP, LARGEURMAP, true_map); // On l'affiche
		
		NBTANKTOTAL = 20;
		// On initialise la répartition des différents types de tanks ennemis
		repartitionTankEnnemis[0] = NBTANKWEAKFACILE; // ... 8 tanks faibles
		repartitionTankEnnemis[1] = NBTANKMEDIUMFACILE; // ... 7 tanks moyens
		repartitionTankEnnemis[2] = NBTANKSTRONGFACILE; // ... 5 tanks forts
	}
	else if (mode == 12){										// MODE TERMINAL DIFFICILE
		true_map = creer_charger_map(LONGUEURMAP, LARGEURMAP, PATHMAPTERMINAL);
		affichage_mat(LONGUEURMAP, LARGEURMAP, true_map);
		
		NBTANKTOTAL = 30;
		repartitionTankEnnemis[0] = NBTANKWEAKDIFFICILE; // ... 10 tanks faibles
		repartitionTankEnnemis[1] = NBTANKMEDIUMDIFFICILE; // ... 10 tanks moyens
		repartitionTankEnnemis[2] = NBTANKSTRONGDIFFICILE; // ... 10 tanks forts
		
	}
	else if (mode == 21){										// MODE GRAPHIQUE FACILE
		afficher_fichier(PATHMAPGRAPHIQUE); // On affiche directement le fichier avec les caractères spéciaux
		
		NBTANKTOTAL = 20;
		repartitionTankEnnemis[0] = NBTANKWEAKFACILE;
		repartitionTankEnnemis[1] = NBTANKMEDIUMFACILE;
		repartitionTankEnnemis[2] = NBTANKSTRONGFACILE;
	}
	else if (mode == 22){										// MODE GRAPHIQUE DIFFICILE
		afficher_fichier(PATHMAPGRAPHIQUE);
		
		NBTANKTOTAL = 30;
		repartitionTankEnnemis[0] = NBTANKWEAKDIFFICILE;
		repartitionTankEnnemis[1] = NBTANKMEDIUMDIFFICILE;
		repartitionTankEnnemis[2] = NBTANKSTRONGDIFFICILE;
	}
}

void MenuSelectionMode(){
	while((key = key_pressed()) != 'q'){
		if (key == 'A' || key == 'B'){ // Naviguer dans le menu = HAUT / BAS
			effacer_choix(choix_x, choix_y);
			
			// Choix des modes terminal/graphique		
			if (key == 'A' && choix_x != 10 && choix_y == 102) choix_x = choix_x - 5;
			else if (key == 'B' && choix_x != 20 && choix_y == 102) choix_x = choix_x + 5;			
			// Choix des modes facile/difficile
			else if (key == 'A' && choix_x == 12 && choix_y == 120) choix_x = choix_x - 2;
			else if (key == 'B' && choix_x == 10 && choix_y == 120) choix_x = choix_x + 2;
			else if (key == 'A' && choix_x == 17 && choix_y == 120) choix_x = choix_x - 2;
			else if (key == 'B' && choix_x == 15 && choix_y == 120) choix_x = choix_x + 2;
			
			deplacement_choix(choix_x, choix_y);
		}
		else if (key == '\n'){ // Valider un choix dans le menu = ENTREE
			system("clear");
			
			if (choix_x == 10 && choix_y == 102){
				choix_y = choix_y + 18;
				afficher_fichier(PATHMENUTERMINAL);
				deplacement_choix(choix_x, choix_y);
			}			
			else if (choix_x == 15 && choix_y == 102){
				choix_y = choix_y + 18;
				afficher_fichier(PATHMENUGRAPHIQUE);
				deplacement_choix(choix_x, choix_y);
			}
				
			// Choix de la difficulté facile/difficile
			else if (choix_x == 10 && choix_y == 120){ // MODE TERMINAL FACILE
				mode = 11;
				break;
			}
			else if (choix_x == 12 && choix_y == 120){ // MODE TERMINAL DIFFICILE
				mode = 12;
				break;
			}
			else if (choix_x == 15 && choix_y == 120){ // MODE GRAPHIQUE FACILE
				mode = 21;
				break;
			}
			else if (choix_x == 17 && choix_y == 120){ // MODE GRAPHIQUE DIFFICILE
				mode = 22;
				break;
			}
			else if (choix_x == 20){
				mode = 3;
				break; // MODE 'QUITTER'
				}
		}
		else if (key == '\t' && choix_y == 120){ // Retour au menu principal = TABULATION
			afficher_fichier(PATHMENU);
			choix_y = choix_y - 18;
			
			if (choix_x == 17 || choix_x == 12) choix_x = choix_x - 2;
			deplacement_choix(choix_x, choix_y);
		}
	}
}
