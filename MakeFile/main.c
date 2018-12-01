#include "../GameManager/GameManager.h"

/* La fake_map est comme un calque permettant de gérer en background les collisions avec les tanks et les obus
alors que la true map est juste la représentation graphique de la map en temps réèl dans le terminal */

int main(){
	init_terminal(); // On initialise les paramètres du terminal

	// Chargement du menu
	afficher_fichier(PATHMENU);
	
	MenuSelectionMode(); // Le menu de selection du mode de jeu se lance

	if (mode != 3 && key != 'q'){ // Si le joueur a choisit un mode
		
		// On initialise les règles de la partie selon le mode choisie par le joueur
		initialiserLaPartieSelonLeMode(mode);
		
		// Si le joueur ne quitte pas, que la bombe n'a pas explosé et que le joueur est encore vivant et qu'il y a encore des tanks en vie
		while ((key = key_pressed()) != 'q' && pioupiouAlive == 1 && joueur->etat > 0 &&  NBTANKTOTAL > 0){
			
			// On lance des vagues de tanks par 4 tant qu'on peux en créer
			if (nb_tank_wave < wave && NBTANKTOTAL >= wave){
				// On définit l'emplacement du prochain tank à générer
				if (NBTANKTOTAL%2 == 0) creer_tank_ennemis(4, 1, 'C');
				if (NBTANKTOTAL%2 != 0) creer_tank_ennemis(30, 138, 'D');
			}
			
			// Gestion des déplacements du joueur
			if (key == 'A' || key == 'B' || key == 'C' || key =='D'){
				joueur->direction = key; // Mise à jour de la position du joueur
				deplacer_tank_joueur_terminal(joueur); // On déplace le tank du joueur dans le terminal/fake map
			}
			// Gestion des tirs du joueur
			else if (key == ' ') shot_creator(joueur); // On créé un obus et on l'ajoute dans le tableau de pointeurs d'obus
			
			deplacer_tank_ennemis_terminal(); // On bouge et affiche tous les tanks ennemis
			shot_manager(); // On réalise le déplacement de tous les obus par accoups
		}
	}
	
	quit_terminal(); // On nettoie le terminal et on remet ses bons paramètres
	return 0;
}
