#include "../TankManager/TankManager.h"

OBUSP * allocation_dyn_tab_obus(){ return malloc(NBOBUSALLOWED * sizeof(OBUSP)); }

int * allocation_dyn_tab_repar_tank_ennemis(){ return malloc(3 * sizeof(int)); }

int nb_tank_weak(){
	struct TANK *temp = head; int nb_weak_tank = 0;
	while (temp != NULL){ // On boucle sur tous les tanks de la liste chaînée
		if (temp->blindage_origine == 0) nb_weak_tank++;
		temp = temp->suivant; // On passe au tank ennemi
	}
	return nb_weak_tank+repartitionTankEnnemis[0];
}

int nb_tank_medium(){
	struct TANK *temp = head; int nb_medium_tank = 0;
	while (temp != NULL){ // On boucle sur tous les tanks de la liste chaînée
		if (temp->blindage_origine == 1) nb_medium_tank++;
		temp = temp->suivant; // On passe au tank ennemi
	}
	return nb_medium_tank+repartitionTankEnnemis[1];
}

int nb_tank_strong(){
	struct TANK *temp = head; int nb_strong_tank = 0;
	while (temp != NULL){ // On boucle sur tous les tanks de la liste chaînée
		if (temp->blindage_origine == 2) nb_strong_tank++;
		temp = temp->suivant; // On passe au tank ennemi
	}
	return nb_strong_tank+repartitionTankEnnemis[2];
}

void afficher_nb_tanks_defaite(){
	printf("%s", GREEN);
	afficher_message_int(29, 75, nb_tank_weak());
	printf("%s", YELLOW);
	afficher_message_int(30, 75, nb_tank_medium());
	printf("%s", RED);
	afficher_message_int(31, 75, nb_tank_strong());
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
	
	if (pioupiouAlive == 1 && joueurMort == 0 && key != 'q' && mode != 3) { // Le joueur a gagné
		system("../Jouer_sons/./scriptSonsBoucleUnique.sh ../Jouer_sons/victory.mp3");
		printf("%s", YELLOW);
		afficher_fichier(PATHMENUVICTOIRE);
		printf("%s", YELLOW);
	}
	else if (pioupiouAlive == 0) {  // La bombe a explosé
		printf("%s", RED);
		afficher_fichier(PATHMENUEXPLOSION);
		afficher_nb_tanks_defaite();
	}
	else if (joueurMort == 1) { // Le joueur est mort
		printf("%s", RED);
		afficher_fichier(PATHMENUMORT);
		afficher_nb_tanks_defaite();
	}
	else afficher_fichier(PATHMENUQUITTER); // Le joueur a quitté
	printf("%s", NORMAL);
		
	while ((key = key_pressed()) != 'q'){}
	system("setterm -cursor on");
	system("stty echo");
	system("clear");
	system("killall play");
}

void initialiserLaPartieSelonLeMode(){

	system("clear");
	afficher_message(15, 60, "Lancement du jeu .\n");
	system("sleep 0.4");
	afficher_message(15, 78, ".\n");
	system("sleep 0.4");
	afficher_message(15, 79, ".\n");
	system("sleep 0.4");
	afficher_message(20, 63, "C'est parti !\n");
	system("sleep 0.5");
	
	// On initialise la répartition des différents types de tanks ennemis
	repartitionTankEnnemis = allocation_dyn_tab_repar_tank_ennemis();
	true_map = creer_charger_map(LONGUEURMAP, LARGEURMAP, PATHMAPTERMINAL); // On initialise la map à afficher
	affichage_mat(LONGUEURMAP, LARGEURMAP, true_map); // On l'affiche
	wave = 4;
	
	if (mode == 1){											// MODE TERMINAL FACILE
		NBTANKTOTAL = 15;
		vieJoueur = 6;
		NBCOUPSABIMENT = 2;
		// On initialise la répartition des différents types de tanks ennemis
		repartitionTankEnnemis[0] = NBTANKWEAKFACILE; // ... 6 tanks faibles
		repartitionTankEnnemis[1] = NBTANKMEDIUMFACILE; // ... 5 tanks moyens
		repartitionTankEnnemis[2] = NBTANKSTRONGFACILE; // ... 4 tanks forts
	}
	else if (mode == 2){										// MODE TERMINAL DIFFICILE		
		NBTANKTOTAL = 25;
		vieJoueur = 3;
		NBCOUPSABIMENT = 1;
		repartitionTankEnnemis[0] = NBTANKWEAKDIFFICILE; // ... 10 tanks faibles
		repartitionTankEnnemis[1] = NBTANKMEDIUMDIFFICILE; // ... 10 tanks moyens
		repartitionTankEnnemis[2] = NBTANKSTRONGDIFFICILE; // ... 10 tanks forts
	}
	
	// Chargement de la fake_map
	fake_map = creer_charger_map(LONGUEURMAP, LARGEURMAP, PATHMAPTERMINAL);
	
	// On initialise les carrosseries des tanks
	init_carrosseries();

	// On initialise une liste chaînée vide
	head = NULL;
	
	// On initialise le tank du joueur
	joueur = creer_tank_joueur(9, 74, 'B'); // On créé et initialise le TANKP du JOUEUR
	
	// On place le joueur sur le terminal et dans la fake map
	affichage_tank_terminal(joueur);

	// On créé quatre premiers tanks ennemis
	creer_tank_ennemis(4, 1, 'C');
	creer_tank_ennemis(30, 138, 'D');
	creer_tank_ennemis(8, 130, 'D');
	creer_tank_ennemis(33, 29, 'D');
	
	// On lance la musique du jeu en lançant la partie
	system("../Jouer_sons/./scriptSonsBoucle.sh ../Jouer_sons/terminator.mp3 ../Jouer_sons/find.mp3 ../Jouer_sons/angel_of_verdain.mp3");
}

void MenuSelectionMode(){

	// On initialise la selection dans le menu
	deplacement_choix(choix_x, choix_y);

	while((key = key_pressed()) != 'q'){
		if (key == 'A' || key == 'B'){ // Naviguer dans le menu = HAUT / BAS
			effacer_choix(choix_x, choix_y);
			
			// Choix des modes terminal		
			if (key == 'A' && choix_x != 10 && choix_y == 102) choix_x = choix_x - 5;
			else if (key == 'B' && choix_x != 15 && choix_y == 102) choix_x = choix_x + 5;			
			// Choix des modes facile/difficile
			else if (key == 'A' && choix_x == 12 && choix_y == 120) choix_x = choix_x - 2;
			else if (key == 'B' && choix_x == 10 && choix_y == 120) choix_x = choix_x + 2;
			
			deplacement_choix(choix_x, choix_y);
		}
		else if (key == '\n'){ // Valider un choix dans le menu = ENTREE
			system("clear");
			
			if (choix_x == 10 && choix_y == 102){
				choix_y = choix_y + 18;
				afficher_fichier(PATHMENUTERMINAL);
				deplacement_choix(choix_x, choix_y);
			}
				
			// Choix de la difficulté facile/difficile
			else if (choix_x == 10 && choix_y == 120){ // MODE TERMINAL FACILE
				mode = 1;
				break;
			}
			else if (choix_x == 12 && choix_y == 120){ // MODE TERMINAL DIFFICILE
				mode = 2;
				break;
			}
			else if (choix_x == 15){
				mode = 3;
				break; // MODE 'QUITTER'
				}
		}
		else if (key == '\t' && choix_y == 120){ // Retour au menu principal = TABULATION
			afficher_fichier(PATHMENU);
			choix_y = choix_y - 18;
			
			if (choix_x == 12) choix_x = choix_x - 2;
			deplacement_choix(choix_x, choix_y);
		}
	}
}
