#include "../InitGame/InitGame.h"

/* La fake_map est comme un calque permettant de gérer en background les collisions avec les tanks et les obus
alors que la true map est juste la représentation graphique de la map en temps réèl dans le terminal */

int main(){
	init_terminal(); // On initialise les paramètres du terminal

	// Chargement du menu
	afficher_fichier(PATHMENU);
	
	// On initialise la selection dans le menu
	deplacement_choix(choix_x, choix_y);
	
	char key;
	while((key = key_pressed()) != 'q'){
		if (key == 'A' || key == 'B'){ // Naviguer dans le menu = HAUT / BAS
			effacer_choix(choix_x, choix_y);
			
			// Choix des modes terminal/graphique		
			if (key == 'A' && choix_x != 10 && choix_y == 103) choix_x = choix_x - 5;
			else if (key == 'B' && choix_x != 20 && choix_y == 103) choix_x = choix_x + 5;			
			// Choix des modes facile/difficile
			else if (key == 'A' && choix_x == 12 && choix_y == 121) choix_x = choix_x - 2;
			else if (key == 'B' && choix_x == 10 && choix_y == 121) choix_x = choix_x + 2;
			else if (key == 'A' && choix_x == 17 && choix_y == 121) choix_x = choix_x - 2;
			else if (key == 'B' && choix_x == 15 && choix_y == 121) choix_x = choix_x + 2;
			
			deplacement_choix(choix_x, choix_y);
		}
		else if (key == '\n'){ // Valider un choix dans le menu = ENTREE
			system("clear");
			
			if (choix_x == 10 && choix_y == 103){
				choix_y = choix_y + 18;
				afficher_fichier(PATHMENUTERMINAL);
				deplacement_choix(choix_x, choix_y);
			}			
			else if (choix_x == 15 && choix_y == 103){
				choix_y = choix_y + 18;
				afficher_fichier(PATHMENUGRAPHIQUE);
				deplacement_choix(choix_x, choix_y);
			}
				
			// Choix de la difficulté facile/difficile
			else if (choix_x == 10 && choix_y == 121){ // MODE TERMINAL FACILE
				mode = 11;
				break;
			}
			else if (choix_x == 12 && choix_y == 121){ // MODE TERMINAL DIFFICILE
				mode = 12;
				break;
			}
			else if (choix_x == 15 && choix_y == 121){ // MODE GRAPHIQUE FACILE
				mode = 21;
				break;
			}
			else if (choix_x == 17 && choix_y == 121){ // MODE GRAPHIQUE DIFFICILE
				mode = 22;
				break;
			}
			else if (choix_x == 20) break; // MODE 'QUITTER'
		}
		else if (key == '\t' && choix_y == 121){ // Retour au menu principal = TABULATION
			afficher_fichier(PATHMENU);
			choix_y = choix_y - 18;
			
			if (choix_x == 17 || choix_x == 12) choix_x = choix_x - 2;
			deplacement_choix(choix_x, choix_y);
		}
	}

	if (mode != 0){ // Si le joueur a choisit un mode

		system("clear");
		afficher_message(15, 65, "Lancement du jeu .\n");
		system("sleep 0.4");
		afficher_message(15, 83, ".\n");
		system("sleep 0.4");
		afficher_message(15, 84, ".\n");
		system("sleep 0.4");
		afficher_message(20, 71, "C'est parti !\n");
		system("sleep 0.5");
		
		// On initialise les règles de la partie selon le mode choisie par le joueur
		initialiserLaPartieSelonLeMode(mode);
		
		// Chargement de la true_map
		affichage_mat(LONGUEURMAP, LARGEURMAP, true_map);

		// Chargement de la fake_map
		char **fake_map = creer_charger_map(LONGUEURMAP, LARGEURMAP, PATHMAPTERMINAL);
		
		// On initialise les carrosseries des tanks
		init_carrosseries();

		// On initialise une liste chaînée vide
		head = NULL;
		
		// On créé le tank du joueur
		struct TANK *joueur = creer_tank_joueur(fake_map, &head, 30, 30, 'A'); // On créé et initialise le TANKP du JOUEUR

		// On créé deux premiers tanks ennemis
		creer_tank_ennemis(fake_map, &head, 4, 2, 'B');
		creer_tank_ennemis(fake_map, &head, 30, 137, 'B');
	
		// On place le joueur sur le terminal et dans la fake map
		affichage_tank_terminal(joueur);
		
		int intervalleTankEnnemis = 0;
		int nbRand;  // Nombre aléatoire qui se réinitialise pour que les tanks ennemis se déplacent chaque seconde

		char entr;
		
		// Si le joueur ne quitte pas, qu'il reste des tanks à générer, que la bombe n'a pas explosé et que le joueur est encore vivant et qu'il y a encore des tanks en vie sur la map
		while ((entr = key_pressed()) != 'q' && pioupiouAlive == 1 && joueur->etat > 0 && nbTankStillAlive(head) > 1){
		
			if (nb_tank_wave < 2 && NbEnnemisTanksToCreate() > 0){ // On lance des vagues de tanks par deux tant qu'on peux en créer
				// On définit l'emplacement du prochain tank à générer
				if (nb_tank_wave%2 == 0) creer_tank_ennemis(fake_map, &head, 4, 2, 'B');
				if (nb_tank_wave%2 != 0) creer_tank_ennemis(fake_map, &head, 30, 137, 'B');
			}
		
			shot_cleaner(fake_map); // On efface tous les obus sur le terminal

			// Gestion des déplacements du joueur
			if (entr == 'A' || entr == 'B' || entr == 'C' || entr =='D'){
				joueur->direction = entr; // Mise à jour de la position du joueur
				deplacer_tank_joueur_terminal(fake_map, &joueur); // On déplace le tank du joueur dans le terminal/fake map
			}

			// Gestion des tirs du joueur
			else if (entr == 'x') shot_creator(joueur); // On créé un obus et on l'ajoute dans le tableau de pointeurs d'obus

			shot_manager(fake_map); // On réalise le déplacement de tous les obus par accoups
			
			srand(time(NULL));	
			nbRand = rand()%(100);
			if (intervalleTankEnnemis != nbRand){ // On bouge les tanks ennemis chaque seconde
				deplacer_tank_ennemis_terminal(fake_map, head); // On bouge et affiche tous les tanks ennemis
				intervalleTankEnnemis = nbRand;	
			}
			
			delay(87000); // Frequence d'affichage de toute la map (deplacement tank, tirs obus, ...)
		}
	}
	
	quit_terminal(); // On nettoie le terminal et on remet ses bons paramètres	
	return 0;
}
