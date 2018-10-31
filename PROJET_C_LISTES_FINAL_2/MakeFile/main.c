#include "../InitGame/InitGame.h"

void affichage_mat_fake(int nbL, int nbC, char ** mat){
	for (int i = 0; i < nbL; i++){
		for (int j = 0; j < nbC; j++){
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}
}

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

		system("clear");
		afficher_message(15, 60, "Lancement du jeu .\n");
		system("sleep 0.4");
		afficher_message(15, 78, ".\n");
		system("sleep 0.4");
		afficher_message(15, 79, ".\n");
		system("sleep 0.4");
		afficher_message(20, 63, "C'est parti !\n");
		system("sleep 0.5");
		
		// On initialise les règles de la partie selon le mode choisie par le joueur
		initialiserLaPartieSelonLeMode(mode);

		// Chargement de la fake_map
		char **fake_map = creer_charger_map(LONGUEURMAP, LARGEURMAP, PATHMAPTERMINAL);
		
		// On initialise les carrosseries des tanks
		init_carrosseries();

		// On initialise une liste chaînée vide
		head = NULL;
		
		// On créé le tank du joueur
		struct TANK *joueur = creer_tank_joueur(fake_map, &head, 30, 30, 'A'); // On créé et initialise le TANKP du JOUEUR

		// On créé deux premiers tanks ennemis
		creer_tank_ennemis(fake_map, &head, 4, 2, 'C');
		creer_tank_ennemis(fake_map, &head, 30, 137, 'D');
	
		// On place le joueur sur le terminal et dans la fake map
		affichage_tank_terminal(joueur);
		
		int intervalleTankEnnemis = 0;
		int nbRand;  // Nombre aléatoire qui se réinitialise pour que les tanks ennemis se déplacent chaque seconde

		// Si le joueur ne quitte pas, qu'il reste des tanks à générer, que la bombe n'a pas explosé et que le joueur est encore vivant et qu'il y a encore des tanks en vie sur la map
		while ((key = key_pressed()) != 'q' && pioupiouAlive == 1 && joueurMort == 0 &&  nbTankStillAlive(head) > 0){
		
			afficher_message_int(1, 140, NbEnnemisTanksToCreate()); // On affiche le nombre de tanks restant
			afficher_message_int(2, 140, vieJoueur); // On affiche la vie du joueur
			if (NbEnnemisTanksToCreate() < 10) afficher_message(1, 141, " "); // Règler un bug d'affichage
			
			// On lance des vagues de tanks par deux tant qu'on peux en créer
			if (nb_tank_wave < 2 && NBTANKTOTAL >= 2){
				// On définit l'emplacement du prochain tank à générer
				if (nb_tank_wave%2 == 0) creer_tank_ennemis(fake_map, &head, 4, 2, 'C');
				if (nb_tank_wave%2 != 0) creer_tank_ennemis(fake_map, &head, 30, 137, 'D');
			}

			shot_cleaner(fake_map); // On efface tous les obus sur le terminal

			// Gestion des déplacements du joueur
			if (key == 'A' || key == 'B' || key == 'C' || key =='D'){
				joueur->direction = key; // Mise à jour de la position du joueur
				deplacer_tank_joueur_terminal(fake_map, &joueur); // On déplace le tank du joueur dans le terminal/fake map
			}

			// Gestion des tirs du joueur
			else if (key == 'x') shot_creator(joueur); // On créé un obus et on l'ajoute dans le tableau de pointeurs d'obus

			shot_manager(fake_map); // On réalise le déplacement de tous les obus par accoups
			
			srand(time(NULL));	
			nbRand = rand()%(4);
			if (intervalleTankEnnemis != nbRand){ // On bouge les tanks ennemis chaque seconde
				deplacer_tank_ennemis_terminal(fake_map, head, intervalleTankEnnemis); // On bouge et affiche tous les tanks ennemis
				intervalleTankEnnemis = nbRand;	
			}
			
			delay(26000); // Frequence d'affichage de toute la map (deplacement tank, tirs obus, ...)
		}
		
		/*system("clear");
		affichage_mat_fake(LONGUEURMAP, LARGEURMAP, fake_map);
		system("sleep 100");*/
	}
	
	quit_terminal(); // On nettoie le terminal et on remet ses bons paramètres
	return 0;
}
