#include "../Traiter_fichiers_texte/flux_fichier.h"

struct TANK *creer_tank_joueur(char **fake_map, struct TANK** head, int pos_x, int pos_y, char direction){
	// Créer et initialise le tank du joueur
	struct TANK *tank = (struct TANK*) malloc(sizeof(struct TANK)); // On créé notre tank joueur
	
	// On initialise chaque attributs du tank joueur
	tank->pos_x = pos_x; tank->pos_y = pos_y; tank->direction = direction; tank->blindage_origine = 1; tank->etat = 2; tank->linearite = 0;
	tank->blindage =  tank->blindage_origine; tank->nb_impacts = 0; tank->camp = 'P'; tank->timingDeplacement = 0; tank->timingTir = 0;
	
	switch(tank->blindage_origine){
		case(0):
			switch(direction){ // Selon la direction du tank joueur
				case('A'): tank->carrosserie = carrosserieWTH; break;
				case('B'): tank->carrosserie = carrosserieWTB; break;
				case('C'): tank->carrosserie = carrosserieWTD; break;
				case('D'): tank->carrosserie = carrosserieWTG; break;
				default: break;
			} break;
		case(1): 
			switch(direction){ // Selon la direction du tank joueur
				case('A'): tank->carrosserie = carrosserieMTH; break;
				case('B'): tank->carrosserie = carrosserieMTB; break;
				case('C'): tank->carrosserie = carrosserieMTD; break;
				case('D'): tank->carrosserie = carrosserieMTG; break;
				default: break;
			} break;
		case(2):
			switch(direction){ // Selon la direction du tank joueur
				case('A'): tank->carrosserie = carrosserieSTH; break;
				case('B'): tank->carrosserie = carrosserieSTB; break;
				case('C'): tank->carrosserie = carrosserieSTD; break;
				case('D'): tank->carrosserie = carrosserieSTG; break;
				default: break;
			} break;
	}

	tank->suivant = (*head); 
    	(*head) = tank;
    	
    	remplir_map_tank(fake_map, tank); // On remplit la fake map à la création pout être 'touchable'
	return (*head);
}

void creer_tank_ennemis(char **fake_map, struct TANK **head, int pos_x, int pos_y, char direction){

	// Création du nouvel élément
	struct TANK *newEnnemyTank = (struct TANK*) malloc(sizeof(struct TANK)); // On créé notre tank ennemi

	int blindage_origine = rand()%(3);

	// On vérifie la disponibilité des blindages de tanks restants
	while(repartitionTankEnnemis[blindage_origine] <= 0) blindage_origine = rand()%(3);
	repartitionTankEnnemis[blindage_origine]--; // On décrémente puisqu'un tank va être créé de ce blindage

	// On initialise chaque attributs du tank ennemi
	newEnnemyTank->pos_x = pos_x; newEnnemyTank->pos_y = pos_y; newEnnemyTank->direction = direction; newEnnemyTank->linearite = 0;
	newEnnemyTank->blindage = blindage_origine; newEnnemyTank->blindage_origine = blindage_origine; newEnnemyTank->nb_impacts = 0;
	newEnnemyTank->camp = 'E'; newEnnemyTank->etat = 2; newEnnemyTank->timingDeplacement = 1; newEnnemyTank->timingTir = 1;
	
	// On selectionne la bonne carrosserie selon le blindage d'origine
	switch(blindage_origine){
		case(0): // Tank ennemi faible
			switch(direction){ // Selon la direction du tank ennemi
				case('A'): newEnnemyTank->carrosserie = carrosserieWTH; break;
				case('B'): newEnnemyTank->carrosserie = carrosserieWTB; break;
				case('C'): newEnnemyTank->carrosserie = carrosserieWTD; break;
				case('D'): newEnnemyTank->carrosserie = carrosserieWTG; break;
				default: break;
			} break;
			
		case(1): // Tank ennemi moyen
			switch(direction){
				case('A'): newEnnemyTank->carrosserie = carrosserieMTH; break;
				case('B'): newEnnemyTank->carrosserie = carrosserieMTB; break;
				case('C'): newEnnemyTank->carrosserie = carrosserieMTD; break;
				case('D'): newEnnemyTank->carrosserie = carrosserieMTG; break;
				default: break;
			} break;
			
		case(2): // Tank ennemi fort
			switch(direction){
				case('A'): newEnnemyTank->carrosserie = carrosserieSTH; break;
				case('B'): newEnnemyTank->carrosserie = carrosserieSTB; break;
				case('C'): newEnnemyTank->carrosserie = carrosserieSTD; break;
				case('D'): newEnnemyTank->carrosserie = carrosserieSTG; break;
				default: break;
			} break;

		default: break;
	}

	// Insertion du nouveau tank ennemi au début de la liste chainées
	newEnnemyTank->suivant = (*head);
    	(*head) = newEnnemyTank;
    	remplir_map_tank(fake_map, newEnnemyTank); // On remplit la fake map avec le tank
    	affichage_tank_terminal(newEnnemyTank); // On affiche le nouveau tank ennemis sur le terminal
    	
    	nb_tank_wave++; // Un tank de plus dans la vague de tanks ennemis
}

void deplacer_tank_ennemis_terminal(char **fake_map){

	struct TANK *temp = head;
	while (temp != NULL){ // On boucle sur tous les tanks de la liste chaînée	
		if (temp->camp == 'E'){ // On ne boucle que sur les tanks ennemis

			// On met un delai de changer de direction des tanks
			if (temp->timingDeplacement%5000 == 0){
				int direction = -1;
				
				if (temp->pos_x == 30 && temp->pos_y > 130){ // On fait sortir entierement les tanks de leur SAS (bas droite)
					direction = 3;
				}
				else if (temp->pos_x == 4 && temp->pos_y < 6){ // On fait sortir entierement les tanks de leur SAS (haut gauche)
					direction = 2;
				}
				else if (temp->linearite < 5){
				// On fais bouger le tank sur 5 cases de suite pour créer une mouvement plus naturel et éviter le sur-place
					switch(temp->direction){ // Selon la direction du tank ennemi
						case('A'): direction = 0; break;
						case('B'): direction = 1; break;
						case('C'): direction = 2; break;
						case('D'): direction = 3; break;
						default: break;
					}
					temp->linearite++;
				} else{
					temp->linearite = 0;
					int directionAleatoire = rand()%(4); // Le mouvement des tanks est aléatoire au bout de 5 mouvements consécutifs
					direction = directionAleatoire;
				}
				
				switch(direction){
					case(0): // Vers le haut
						switch(temp->blindage){ // Selon la direction du tank ennemi
							case(0): temp->carrosserie = carrosserieWTH; break;
							case(1): temp->carrosserie = carrosserieMTH; break;
							case(2): temp->carrosserie = carrosserieSTH; break;
							default: break;
						} temp->direction = 'A';
						deplacement_tank_haut(fake_map, temp); break; // On effectue le déplacement
						
					case(1): // Vers le bas
						switch(temp->blindage){
							case(0): temp->carrosserie = carrosserieWTB; break;
							case(1): temp->carrosserie = carrosserieMTB; break;
							case(2): temp->carrosserie = carrosserieSTB; break;
							default: break;
						} temp->direction = 'B';
						deplacement_tank_bas(fake_map, temp); break;
						
					case(2): // Vers la droite
						switch(temp->blindage){
							case(0): temp->carrosserie = carrosserieWTD; break;
							case(1): temp->carrosserie = carrosserieMTD; break;
							case(2): temp->carrosserie = carrosserieSTD; break;
							default: break;
						} temp->direction = 'C';
						deplacement_tank_droite(fake_map, temp); break;
						
					case(3): // Vers la gauche
						switch(temp->blindage){
							case(0): temp->carrosserie = carrosserieWTG; break;
							case(1): temp->carrosserie = carrosserieMTG; break;
							case(2): temp->carrosserie = carrosserieSTG; break;
							default: break;
						} temp->direction = 'D';
						deplacement_tank_gauche(fake_map, temp); break;

					default : break;
				}
				temp->timingDeplacement = 0;
			}
			
			if (temp->timingTir%25000 == 0){
				shot_creator(temp); // On fait tirer les tanks ennemis aléatoirement
				temp->timingTir = 0;
			}
			
			temp->timingTir++;
			temp->timingDeplacement++;
		}
		temp = temp->suivant; // On passe au tank ennemi
	}	
}

void deplacer_tank_joueur_terminal(char **fake_map, struct TANK *joueur){

	switch(joueur->direction){ // Selon la direction du tank du joueur
		case('A'): // Vers le haut
			switch(joueur->blindage){ // Selon la direction du tank ennemi
				case(0): joueur->carrosserie = carrosserieWTH; break;
				case(1): joueur->carrosserie = carrosserieMTH; break;
				case(2): joueur->carrosserie = carrosserieSTH; break;
				default: break;
			} deplacement_tank_haut(fake_map, joueur); break; // On effectue le déplacement
			
		case('B'): // Vers le bas
			switch(joueur->blindage){
				case(0): joueur->carrosserie = carrosserieWTB; break;
				case(1): joueur->carrosserie = carrosserieMTB; break;
				case(2): joueur->carrosserie = carrosserieSTB; break;
			} deplacement_tank_bas(fake_map, joueur); break;
			
		case('C'): // Vers la droite
			switch(joueur->blindage){
				case(0): joueur->carrosserie = carrosserieWTD; break;
				case(1): joueur->carrosserie = carrosserieMTD; break;
				case(2): joueur->carrosserie = carrosserieSTD; break;
			} deplacement_tank_droite(fake_map, joueur); break;
			
		case('D'): // Vers la gauche
			switch(joueur->blindage){
				case(0): joueur->carrosserie = carrosserieWTG; break;
				case(1): joueur->carrosserie = carrosserieMTG; break;
				case(2): joueur->carrosserie = carrosserieSTG; break;
			} deplacement_tank_gauche(fake_map, joueur); break;

		default : break;
	}
}
