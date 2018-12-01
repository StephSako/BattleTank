#include "../Deplacer/deplacement_objet.h"

// Retourne l'indice de la première case vide rencontree
int firstEmptyIndexObusTab(){
	int n = 0;
	while (n < NBOBUSALLOWED && TabPointeursObus[n] != NULL) n++;
	return n;
}

// Supprime le pointeur de l'obus voulu et comble l'espace ainsi vide
void DeleteObusPTab(OBUSP obusPDeleted){
	int ind = 0;
	while (ind < NBOBUSALLOWED){
		if (TabPointeursObus[ind] == obusPDeleted){
			free(TabPointeursObus[ind]); // On desalloue l'obusP dans le tableau
			TabPointeursObus[ind] = NULL; // On libère l'espace dans le tableau de pointeurs
			break;
		}
		ind++;
	}
}

// Supprime le tank détruit de la liste chaînée
void SupprimerTank(struct TANK **head, int position){
	// La liste est vide
	if (*head == NULL) return;
	
	struct TANK* temp = *head; 
	// Si on veut supprimer le 1er tank de la liste
	if (position == 0){
		*head = temp->suivant;
		free(temp);
		return ;
	}
	
	// On cherche le tank précédant du tank à supprimer
	for (int i = 0; temp != NULL && i < position-1; i++) temp = temp->suivant; 

	// Si position est supèrieure au nombre de tanks dans la liste
	if (temp == NULL || temp->suivant == NULL) return;
	
	// Le tank temp->suivant est le tank à supprimer et on stocke le pointeur du tank suivant au tank à supprimer 
	struct TANK *suivant = temp->suivant->suivant; 

	free(temp->suivant); // On libère la mémoire
	temp->suivant = suivant; // Deliement du tank supprimé
}

void AttaquerTank(OBUSP obusP){	
	int pos_xTankAttaque = 0, pos_yTankAttaque = 0; // Position du tank attaqué et à rechercher dans le tableau d'obus
	switch(obusP->direction){
		case('D') : for (int i = 0; i < 3; i++) if (fake_map[obusP->pos_x-i][obusP->pos_y-4] == '*') pos_xTankAttaque = obusP->pos_x-i;
				pos_yTankAttaque = obusP->pos_y-4; break;
				
		case('B') : for (int i = 0; i < 5; i++) if (fake_map[obusP->pos_x][obusP->pos_y-i] == '*') pos_yTankAttaque = obusP->pos_y-i;
				pos_xTankAttaque = obusP->pos_x; break;
		
		case('C') : for (int i = 0; i < 3; i++) if (fake_map[obusP->pos_x-i][obusP->pos_y] == '*') pos_xTankAttaque = obusP->pos_x-i;
				pos_yTankAttaque = obusP->pos_y; break;
		
		case('A') : for(int i = 0; i < 5; i++) if (fake_map[obusP->pos_x-2][obusP->pos_y-i] == '*') pos_yTankAttaque = obusP->pos_y-i;
				pos_xTankAttaque = obusP->pos_x-2; break;
		
		default : break;
	}
	
	int position = 0; // Rang auquel se trouve un tank qui devra être détruit et supprimé de la liste chaînée des tanks
	struct TANK *temp = head;
	
	while (temp != NULL){ // On boucle sur tous les tanks de la liste chaînée
		if (temp->pos_x == pos_xTankAttaque && temp->pos_y == pos_yTankAttaque && temp->camp != obusP->camp){ // On désactive le tir allier
			
			temp->nb_impacts++;			
			if (temp->camp == 'P'){
				vieJoueur--; // On enlève de la vie au joueur
				afficher_message_vie(2, 140, vieJoueur); // On affiche la vie du joueur
			}

			if(temp->nb_impacts == NBCOUPSABIMENT){ // A partir de NBCOUPSABIMENT pour chaque blindage, la carrosserie s'abîme
				switch(temp->blindage){
					case 0 :
						system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosion.mp3");
						temp->carrosserie = carrosserieTankDetruit; // On change la carrosserie du tank
						NBTANKTOTAL--; // Un tank de moins à créé
						afficher_message_int(1, 140, NBTANKTOTAL); // On affiche le nombre de tanks restant
						if (NBTANKTOTAL < 10) afficher_string(1, 141, " "); // Régler un bug d'affichage
						nb_tank_wave--; // Un tank de moins dans la vague : il faut en créér un autre
						temp->etat = 0; // Le tank est mort
						if (temp->camp == 'P') joueurMort = 1;
						
						// On affiche les poussières des tanks en train de mourrir
						int randSuppr = 0;
						while (randSuppr <= 12000){
							affichage_tank_terminal(temp);
							randSuppr++; // Gagner du temps pour afficher les poussières (~ delay())
						}
						
						effacer_tank_terminal(temp); // On efface le tank dans le terminal
						effacer_map_tank(temp); // On efface le tank dans la fake_map
						SupprimerTank(&head, position);
						break;
						
					default : // Le tank n'est pas encore mort
						temp->blindage--; temp->nb_impacts = 0;
						effacer_tank_terminal(temp);
						affichage_tank_terminal(temp); break;
					}
			}
			break; // Nous avons impacté le bon tank en lui abîmant sa carrosserie et en le réaffichant
		}
		temp = temp->suivant; // On passe au tank ennemi suivant dans la liste chaînée des tanks ennemis
		position++;
	}
}

void animation_bullet(OBUSP obusP){ // Avec la nouvelle position
	if ((obusP->pos_y == 135 && (obusP->pos_x == 30 || obusP->pos_x == 31 || obusP->pos_x == 32)) ||
	(obusP->pos_y == 9 && (obusP->pos_x == 4 || obusP->pos_x == 5 || obusP->pos_x == 6))){ // Eviter le spawnkill
		fake_map[obusP->pos_x][obusP->pos_y] = ' ';
		effacer_obus_terminal(obusP->pos_x, obusP->pos_y);
		DeleteObusPTab(obusP);
	}
	// L'obus avance dans le vide
	else if (fake_map[obusP->pos_x][obusP->pos_y] == ' '){
		deplacement_obus_terminal(obusP);							// On affiche l'obus dans le terminal
		fake_map[obusP->pos_x][obusP->pos_y] = '+';					// On ajoute l'obus dans la fake map
	}
	// Collision avec une brique
	else if (fake_map[obusP->pos_x][obusP->pos_y] == 'C' || fake_map[obusP->pos_x][obusP->pos_y] == 'P'){
		
		int son = 0; // On joue le bruitage (1 bruitage pour 3 briques pour ne pas déranger le joueur avec trop de bruitages)
		if (obusP->direction == 'A' || obusP->direction == 'B'){
			for (int i = obusP->pos_y-2; i <= obusP->pos_y+2; i++){
				if (fake_map[obusP->pos_x][i] == 'P' && obusP->provenance == 2){		// Tir tank superarmé sur une brique dur
					fake_map[obusP->pos_x][i] = ' ';
					effacer_obus_terminal(obusP->pos_x, i);
				}
				else if (fake_map[obusP->pos_x][i] == 'C'){					// Tir sur une brique normale
					fake_map[obusP->pos_x][i] = ' ';
					effacer_obus_terminal(obusP->pos_x, i);
				}
				if (son == 0){
					// On joue un bruitage avec d'un script (executé en fond)
					system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosion.mp3");
					son = 1;
				}
			}
		} else if (obusP->direction == 'C' || obusP->direction == 'D'){
			
			for (int i = obusP->pos_x-1; i <= obusP->pos_x+1; i++){
				if (fake_map[i][obusP->pos_y] == 'P' && obusP->provenance == 2){
					fake_map[i][obusP->pos_y] = ' ';
					effacer_obus_terminal(i, obusP->pos_y);
				}
				else if (fake_map[i][obusP->pos_y] == 'C'){
					fake_map[i][obusP->pos_y] = ' ';
					effacer_obus_terminal(i, obusP->pos_y);
				}
				if (son == 0){
					system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosion.mp3");
					son = 1;
				}
			}
		}	
		DeleteObusPTab(obusP); // On supprime l'obus dans le tableau de pointeurs d'obus pour ne plus le traiter
	}
	// Un tank ENNEMI a tiré sur la bombe à protéger
	else if (fake_map[obusP->pos_x][obusP->pos_y] == 'B' && obusP->camp == 'E'){
		pioupiouAlive = 0;
		effacer_obus_terminal(obusP->pos_x, obusP->pos_y);
		fake_map[obusP->pos_x][obusP->pos_y] = ' ';
		DeleteObusPTab(obusP);
		system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosionFin.mp3");
	}
	// Collision avec un tank ou une brique non destructible (eau, roseau, limite de la map)
	else{
		if (fake_map[obusP->pos_x][obusP->pos_y] == '*' || fake_map[obusP->pos_x][obusP->pos_y] == 'T')
			AttaquerTank(obusP); // On cherche le tank et on l'attaque s'il y en a eu un de touché	
		DeleteObusPTab(obusP); // On supprime l'obus qui a percuté un obstacle
	}
}

void shot_creator(struct TANK *tank){
	if (firstEmptyIndexObusTab() < NBOBUSALLOWED){ // Si on n'atteint pas le nombre d'obus tires maximum à l'ecran
					
		OBUSP obus = malloc(sizeof(OBUS)); // On créé un nouveau pointeur de l'obus cree	
		obus->provenance = tank->blindage;
		obus->camp = tank->camp;
		obus->direction = tank->direction;
		obus->timingDeplacementObus = 1;
		
		// On deplace l'obus dans le terminal + fake map
		switch(tank->direction){ // On initialise les attributs de l'obus tire en fonction des attributs du tank
			case 'A': obus->pos_x = tank->pos_x-1; obus->pos_y = tank->pos_y+2; break;
			case 'D': obus->pos_x = tank->pos_x+1; obus->pos_y = tank->pos_y-1; break;
			case 'B': obus->pos_x = tank->pos_x+3; obus->pos_y = tank->pos_y+2; break;
			case 'C': obus->pos_x = tank->pos_x+1; obus->pos_y = tank->pos_y+5; break;
			default : break;
		}
		TabPointeursObus[firstEmptyIndexObusTab()] = obus; // On ajoute le pointeur d'obus dans le tableau
	}
}

void shot_manager(){
	for (int i = 0; i < NBOBUSALLOWED; i++){ // On parcours le tableau de pointeurs d'obus relativement
		if (TabPointeursObus[i] != NULL){
			if (TabPointeursObus[i]->timingDeplacementObus%251 == 0 && TabPointeursObus[i]->timingDeplacementObus != 0){
				animation_bullet(TabPointeursObus[i]); // Animation par accoup de l'obus
			}
		}
	}
	
	for (int i = 0; i < NBOBUSALLOWED; i++){ // On parcours le tableau de pointeurs d'obus relativement
		if (TabPointeursObus[i] != NULL){
			if (TabPointeursObus[i]->timingDeplacementObus%500 == 0){		
				// On efface et vide tous les obus de leurs anciennes positions
				effacer_obus_terminal(TabPointeursObus[i]->pos_x, TabPointeursObus[i]->pos_y);
				fake_map[TabPointeursObus[i]->pos_x][TabPointeursObus[i]->pos_y] = ' ';
				
				// On met à jour la position
				switch(TabPointeursObus[i]->direction){
					case 'A': TabPointeursObus[i]->pos_x--; break; // On incremente les positions des obus = le fameux 'accoup'
					case 'D': TabPointeursObus[i]->pos_y--; break;	
					case 'B': TabPointeursObus[i]->pos_x++; break;	
					case 'C': TabPointeursObus[i]->pos_y++; break;
					default : break;
				}
				
				// Permet d'éviter des clignotements de l'obus (car il y a un delai pour l'affichage comme pour l'effacement)
				if (fake_map[TabPointeursObus[i]->pos_x][TabPointeursObus[i]->pos_y] == ' '){
					deplacement_obus_terminal(TabPointeursObus[i]); // Réaffiche l'obus en attendant son traitement
				} TabPointeursObus[i]->timingDeplacementObus = 0;
			} TabPointeursObus[i]->timingDeplacementObus++;
		}
	}
}
