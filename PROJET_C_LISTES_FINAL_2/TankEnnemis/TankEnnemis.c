#include "../Traiter_fichiers_texte/flux_fichier.h"

struct TANK *creer_tank_joueur(char **fake_map, struct TANK** head, int pos_x, int pos_y, char direction){
	// Créer et initialise le tank du joueur
	struct TANK *tank = (struct TANK*) malloc(sizeof(struct TANK)); // On créé notre tank joueur
	
	// On initialise chaque attributs du tank joueur
	tank->pos_x = pos_x; tank->pos_y = pos_y; tank->direction = direction; tank->blindage_origine = 2; tank->etat = 2;
	tank->blindage = tank->blindage_origine; tank->nb_impacts = 0; tank->camp = 'P';
	
	switch(direction){ // Selon la direction du tank joueur
		case('A'): tank->carrosserie = carrosserieSTH; break;
		case('B'): tank->carrosserie = carrosserieSTB; break;
		case('C'): tank->carrosserie = carrosserieSTD; break;
		case('D'): tank->carrosserie = carrosserieSTG; break;
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
	newEnnemyTank->pos_x = pos_x; newEnnemyTank->pos_y = pos_y; newEnnemyTank->direction = direction;
	newEnnemyTank->blindage = blindage_origine; newEnnemyTank->blindage_origine = blindage_origine; newEnnemyTank->nb_impacts = 0;
	newEnnemyTank->camp = 'E'; newEnnemyTank->etat = 2;
	
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

	// Insertion du nouveau tank ennemi au début de la liste chainées des tanks ennemis
	newEnnemyTank->suivant = (*head);
    	(*head) = newEnnemyTank;
    	remplir_map_tank(fake_map, newEnnemyTank);
    	
    	nb_tank_wave++; // Un tank de plus dans la vague de tanks ennemis
}

void deplacer_tank_ennemis_terminal(char **fake_map, struct TANK *tankSelectionne){

	while (tankSelectionne != NULL){ // On boucle sur tous les tanks de la liste chaînée
		if (tankSelectionne->camp == 'E'){ // On ne boucle que sur les tanks ennemis
			int directionAleatoire = rand()%(4);
			
			switch(directionAleatoire){ // Selon la direction du tank ennemis
				case(0): // Vers le haut
					switch(tankSelectionne->blindage){ // Selon la direction du tank ennemi
						case(0): tankSelectionne->carrosserie = carrosserieWTH; break;
						case(1): tankSelectionne->carrosserie = carrosserieMTH; break;
						case(2): tankSelectionne->carrosserie = carrosserieSTH; break;
						default: break;
					} tankSelectionne->direction = 'A';
					deplacement_tank_haut(fake_map, tankSelectionne); break; // On effectue le déplacement
					
				case(1): // Vers le bas
					switch(tankSelectionne->blindage){
						case(0): tankSelectionne->carrosserie = carrosserieWTB; break;
						case(1): tankSelectionne->carrosserie = carrosserieMTB; break;
						case(2): tankSelectionne->carrosserie = carrosserieSTB; break;
						default: break;
					} tankSelectionne->direction = 'B';
					deplacement_tank_bas(fake_map, tankSelectionne); break;
					
				case(2): // Vers la droite
					switch(tankSelectionne->blindage){
						case(0): tankSelectionne->carrosserie = carrosserieWTD; break;
						case(1): tankSelectionne->carrosserie = carrosserieMTD; break;
						case(2): tankSelectionne->carrosserie = carrosserieSTD; break;
						default: break;
					} tankSelectionne->direction = 'C';
					deplacement_tank_droite(fake_map, tankSelectionne); break;
					
				case(3): // Vers la gauche
					switch(tankSelectionne->blindage){
						case(0): tankSelectionne->carrosserie = carrosserieWTG; break;
						case(1): tankSelectionne->carrosserie = carrosserieMTG; break;
						case(2): tankSelectionne->carrosserie = carrosserieSTG; break;
						default: break;
					} tankSelectionne->direction = 'D';
					deplacement_tank_gauche(fake_map, tankSelectionne); break;

				default : break;
			}
			
			int tirAleatoire = rand()%(2);
			if (tirAleatoire == 0) shot_creator(tankSelectionne); // On fait tirer les tanks ennemis aléatoirement
		}
		tankSelectionne = tankSelectionne->suivant; // On passe au tank ennemi
	}	
}

void deplacer_tank_joueur_terminal(char **fake_map, struct TANK **joueurP){

	switch((*joueurP)->direction){ // Selon la direction du tank du joueur
		case('A'): // Vers le haut
			switch((*joueurP)->blindage){ // Selon la direction du tank ennemi
				case(0): (*joueurP)->carrosserie = carrosserieWTH; break;
				case(1): (*joueurP)->carrosserie = carrosserieMTH; break;
				case(2): (*joueurP)->carrosserie = carrosserieSTH; break;
				default: break;
			} deplacement_tank_haut(fake_map, (*joueurP)); break; // On effectue le déplacement
			
		case('B'): // Vers le bas
			switch((*joueurP)->blindage){
				case(0): (*joueurP)->carrosserie = carrosserieWTB; break;
				case(1): (*joueurP)->carrosserie = carrosserieMTB; break;
				case(2): (*joueurP)->carrosserie = carrosserieSTB; break;
			} deplacement_tank_bas(fake_map, (*joueurP)); break;
			
		case('C'): // Vers la droite
			switch((*joueurP)->blindage){
				case(0): (*joueurP)->carrosserie = carrosserieWTD; break;
				case(1): (*joueurP)->carrosserie = carrosserieMTD; break;
				case(2): (*joueurP)->carrosserie = carrosserieSTD; break;
			} deplacement_tank_droite(fake_map, (*joueurP)); break;
			
		case('D'): // Vers la gauche
			switch((*joueurP)->blindage){
				case(0): (*joueurP)->carrosserie = carrosserieWTG; break;
				case(1): (*joueurP)->carrosserie = carrosserieMTG; break;
				case(2): (*joueurP)->carrosserie = carrosserieSTG; break;
			} deplacement_tank_gauche(fake_map, (*joueurP)); break;

		default : break;
	}
}

int NbEnnemisTanksToCreate(){
	int nbTankToCreate = 0;
	for (int i = 0; i < 3; i++) nbTankToCreate = nbTankToCreate + repartitionTankEnnemis[i];	
	return nbTankToCreate;
}

int nbTankStillAlive(struct TANK *tank){
	int nbTankStillAlive = 0;
	while (tank != NULL){ 
		nbTankStillAlive++;
		tank = tank->suivant; 
	}
	return nbTankStillAlive;
}
