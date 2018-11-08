#include "../InitGame/InitGame.h"

/* La fake_map est comme un calque permettant de gérer en background les collisions avec les tanks et les obus
alors que la true map est juste la représentation graphique de la map en temps réèl dans le terminal */

int main(){
	init_terminal(); // On initialise les paramètres du terminal

	// Chargement du menu
	afficher_fichier(PATHMENU);
	
	// On initialise la selection dans le menu
	deplacement_choix(choix_x, choix_y);
	
	MenuSelectionMode(); // Le menu de selection du mode de jeu se lance

	if (mode != 3 && key != 'q'){ // Si le joueur a choisit un mode
		
		// On initialise les règles de la partie selon le mode choisie par le joueur
		initialiserLaPartieSelonLeMode(mode);

		// Chargement de la fake_map
		char **fake_map = creer_charger_map(LONGUEURMAP, LARGEURMAP, PATHMAPTERMINAL);
		
		// On initialise les carrosseries des tanks
		init_carrosseries();

		// On initialise une liste chaînée vide
		head = NULL;
		
		// On initialise le tank du joueur
		joueur = creer_tank_joueur(fake_map, &head, 8, 80, 'D'); // On créé et initialise le TANKP du JOUEUR
		
		// On place le joueur sur le terminal et dans la fake map
		affichage_tank_terminal(joueur);

		// On créé quatre premiers tanks ennemis
		creer_tank_ennemis(fake_map, &head, 4, 2, 'C');
		creer_tank_ennemis(fake_map, &head, 30, 137, 'D');
		creer_tank_ennemis(fake_map, &head, 8, 130, 'D');
		creer_tank_ennemis(fake_map, &head, 33, 29, 'D');

		// Si le joueur ne quitte pas, que la bombe n'a pas explosé et que le joueur est encore vivant et qu'il y a encore des tanks en vie
		while ((key = key_pressed()) != 'q' && pioupiouAlive == 1 && joueur->etat > 0 &&  NBTANKTOTAL > 0){
		
			afficher_message_int(1, 140, NBTANKTOTAL); // On affiche le nombre de tanks restant
			afficher_message_int(2, 140, vieJoueur); // On affiche la vie du joueur
			if (NBTANKTOTAL < 10) afficher_message(1, 141, " "); // Régler un bug d'affichage
			
			// On lance des vagues de tanks par 4 tant qu'on peux en créer									// ATTENTION
			if (nb_tank_wave < 3 && NBTANKTOTAL >= 2){
				// On définit l'emplacement du prochain tank à générer
				if (nb_tank_wave%2 == 0) creer_tank_ennemis(fake_map, &head, 4, 2, 'C');
				if (nb_tank_wave%2 != 0) creer_tank_ennemis(fake_map, &head, 30, 137, 'D');
			}
			
			// Gestion des déplacements du joueur
			if (key == 'A' || key == 'B' || key == 'C' || key =='D'){
				joueur->direction = key; // Mise à jour de la position du joueur
				deplacer_tank_joueur_terminal(fake_map, joueur); // On déplace le tank du joueur dans le terminal/fake map
			}
			// Gestion des tirs du joueur
			else if (key == ' ') shot_creator(joueur); // On créé un obus et on l'ajoute dans le tableau de pointeurs d'obus
			
			deplacer_tank_ennemis_terminal(fake_map); // On bouge et affiche tous les tanks ennemis
			shot_manager(fake_map); // On réalise le déplacement de tous les obus par accoups
		}
	}
	
	quit_terminal(); // On nettoie le terminal et on remet ses bons paramètres
	return 0;
}
