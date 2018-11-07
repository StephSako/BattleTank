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
	if (*head == NULL){
		return;
	}

	struct TANK* temp = *head; 

	// Si on veut supprimer le 1er tank de la liste
	if (position == 0){
		*head = temp->suivant;
		free(temp);
		return ;
	}
	
	// On cherche le tank précédant du tank à supprimer
	for (int i = 0; temp != NULL && i < position-1; i++)
		temp = temp->suivant; 

	// Si position est supèrieure au nombre de tanks dans la liste
	if (temp == NULL || temp->suivant == NULL){
		return;
	}
	
	// Le tank temp->suivant est le tank à supprimer 
    	// On stocke le pointeur du tank suivant au tank à supprimer 
	struct TANK *suivant = temp->suivant->suivant; 

	free(temp->suivant); // On libère la mémoire
	temp->suivant = suivant; // Deliement du tank supprimé
}

void AttaquerTank(char **mat, OBUSP obusP){
	
	int pos_xTankAttaque = 0, pos_yTankAttaque = 0; // Position du tank attaqué et à rechercher dans le tableau d'obus
	switch(obusP->direction){
		case('D') : if (mat[obusP->pos_x][obusP->pos_y-4] == '*') pos_xTankAttaque = obusP->pos_x;
				else if (mat[obusP->pos_x-1][obusP->pos_y-4] == '*') pos_xTankAttaque = obusP->pos_x-1;
				else if (mat[obusP->pos_x-2][obusP->pos_y-4] == '*') pos_xTankAttaque = obusP->pos_x-2;
				pos_yTankAttaque = obusP->pos_y-4; break;
				
		case('B') : if (mat[obusP->pos_x][obusP->pos_y] == '*') pos_yTankAttaque = obusP->pos_y;
				else if (mat[obusP->pos_x][obusP->pos_y-1] == '*') pos_yTankAttaque = obusP->pos_y-1;
				else if (mat[obusP->pos_x][obusP->pos_y-2] == '*') pos_yTankAttaque = obusP->pos_y-2;
				else if (mat[obusP->pos_x][obusP->pos_y-3] == '*') pos_yTankAttaque = obusP->pos_y-3;
				else if (mat[obusP->pos_x][obusP->pos_y-4] == '*') pos_yTankAttaque = obusP->pos_y-4;
				pos_xTankAttaque = obusP->pos_x; break;
		
		case('C') : if (mat[obusP->pos_x][obusP->pos_y] == '*') pos_xTankAttaque = obusP->pos_x;
				else if (mat[obusP->pos_x-1][obusP->pos_y] == '*') pos_xTankAttaque = obusP->pos_x-1;
				else if (mat[obusP->pos_x-2][obusP->pos_y] == '*') pos_xTankAttaque = obusP->pos_x-2;
				pos_yTankAttaque = obusP->pos_y; break;
		
		case('A') : if (mat[obusP->pos_x-2][obusP->pos_y] == '*') pos_yTankAttaque = obusP->pos_y;
				else if (mat[obusP->pos_x-2][obusP->pos_y-1] == '*') pos_yTankAttaque = obusP->pos_y-1;
				else if (mat[obusP->pos_x-2][obusP->pos_y-2] == '*') pos_yTankAttaque = obusP->pos_y-2;
				else if (mat[obusP->pos_x-2][obusP->pos_y-3] == '*') pos_yTankAttaque = obusP->pos_y-3;
				else if (mat[obusP->pos_x-2][obusP->pos_y-4] == '*') pos_yTankAttaque = obusP->pos_y-4;
				pos_xTankAttaque = obusP->pos_x-2; break;
		
		default : break;
	}
	
	int position = 0; // Rang auquel se trouve un tank qui devra être détruit et supprimé de la liste chaînée des tanks
	struct TANK *temp = head;
	
	while (temp != NULL){ // On boucle sur tous les tanks de la liste chaînée
		if (temp->pos_x == pos_xTankAttaque && temp->pos_y == pos_yTankAttaque && temp->camp != obusP->camp){ // On désactive le tir allier
			temp->nb_impacts++;
			
			if (temp->camp == 'P') vieJoueur--; // On enlève de la vie au joueur

			switch(temp->nb_impacts){
				case NBCOUPSABIMENT : // A partir de NBCOUPSABIMENT pour chaque blindage, la carrosserie s'abîme
					switch(temp->blindage){
						case 0 :
							system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosion.mp3");
							temp->carrosserie = carrosserieTankDetruit; // On change la carrosserie du tank
							NBTANKTOTAL--; // Un tank de moins à créé
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
							effacer_map_tank(mat, temp); // On efface le tank dans la fake_map
							SupprimerTank(&head, position);
							break;
							
						default : // Le tank n'est pas encore mort
							switch(temp->direction){
								case 'A': temp->carrosserie = carrosserieWTH; break;
								case 'B': temp->carrosserie = carrosserieWTB; break;
								case 'C': temp->carrosserie = carrosserieWTD; break;
								case 'D': temp->carrosserie = carrosserieWTG; break;
								default : break;
								
							} temp->blindage--; temp->nb_impacts = 0;
							effacer_tank_terminal(temp);
							affichage_tank_terminal(temp); break;
					}
									
				default : break;
			}
			break; // Nous avons impacté le bon tank en lui abîmant sa carrosserie et en le réaffichant
		}
		temp = temp->suivant; // On passe au tank ennemi suivant dans la liste chaînée des tanks ennemis
		position++;
	}
}

void animation_bullet(char **mat, OBUSP obusP){ // Avec la nouvelle position
	// L'obus avance dans le vide
	if (mat[obusP->pos_x][obusP->pos_y] == ' '){
		deplacement_obus_terminal(obusP);							// On affiche l'obus dans le terminal
		fflush(stdout);										// On vide le buffer de sortie (on force l'affichage)
		mat[obusP->pos_x][obusP->pos_y] = '+';						// On ajoute l'obus dans la fake map
	}
	// Collision avec une brique
	else if (mat[obusP->pos_x][obusP->pos_y] == 'C' || mat[obusP->pos_x][obusP->pos_y] == 'P'){
		
		int son = 0; // Oon joue le bruitage ou pas ? (1 bruitage pour 3 briques pour ne pas déranger le joueur avec trop de bruitages)
		if (obusP->direction == 'A' || obusP->direction == 'B'){
			for (int i = obusP->pos_y-1; i <= obusP->pos_y+1; i++){
				if (mat[obusP->pos_x][i] == 'P' && obusP->provenance == 2){		// Tir tank superarmé sur une brique dur
					mat[obusP->pos_x][i] = ' ';
					effacer_obus_terminal(obusP->pos_x, i);
				}
				else if (mat[obusP->pos_x][i] == 'C'){					// Tir sur une brique normale
					mat[obusP->pos_x][i] = ' ';
					effacer_obus_terminal(obusP->pos_x, i);
				}
				if (son == 0){
					system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosion.mp3"); // On joue un bruitage avec d'un script (executé en fond)
					son = 1;
				}
			}
		} else if (obusP->direction == 'C' || obusP->direction == 'D'){
			
			for (int i = obusP->pos_x-1; i <= obusP->pos_x+1; i++){
				if (mat[i][obusP->pos_y] == 'P' && obusP->provenance == 2){
					mat[i][obusP->pos_y] = ' ';
					effacer_obus_terminal(i, obusP->pos_y);
				}
				else if (mat[i][obusP->pos_y] == 'C'){
					mat[i][obusP->pos_y] = ' ';
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
	else if (mat[obusP->pos_x][obusP->pos_y] == 'B' && obusP->camp == 'E'){
		pioupiouAlive = 0;
		effacer_obus_terminal(obusP->pos_x, obusP->pos_y);
		mat[obusP->pos_x][obusP->pos_y] = ' ';
		DeleteObusPTab(obusP);
		system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosionFin.mp3");
	}
	// Collision avec un tank ou une brique non destructible (eau, roseau, limite de la map)
	else{
		if (mat[obusP->pos_x][obusP->pos_y] == '*' || mat[obusP->pos_x][obusP->pos_y] == 'T')
			AttaquerTank(mat, obusP); // On cherche le tank et on l'attaque s'il y en a eu un de touché	
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
			case 'A':
				obus->pos_x = tank->pos_x-1; obus->pos_y = tank->pos_y+2; break;
			case 'D':
				obus->pos_x = tank->pos_x+1; obus->pos_y = tank->pos_y-1; break;
			case 'B':
				obus->pos_x = tank->pos_x+3; obus->pos_y = tank->pos_y+2; break;
			case 'C':
				obus->pos_x = tank->pos_x+1; obus->pos_y = tank->pos_y+5; break;
			default : break;
		}
		TabPointeursObus[firstEmptyIndexObusTab()] = obus; // On ajoute le pointeur d'obus dans le tableau
	}
}

void shot_cleaner(char **fake_map){
	// On parcourt le tableau des obus pour tous les effacer du terminal et de la fake map
	for (int i = 0; i < NBOBUSALLOWED; i++){ // On parcours le tableau de pointeurs d'obus relativement
		if (TabPointeursObus[i] != NULL){
			//if (TabPointeursObus[i]->timingDeplacementObus%800 == 0){
			
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
				/*TabPointeursObus[i]->timingDeplacementObus = 1;
			}
			(TabPointeursObus[i]->timingDeplacementObus)++;*/
		}
	}
}

void shot_manager(char **fake_map){
	// On parcourt le tableau des obus pour tous les faire deplacer d'un accoup en même temps : c'est naturel
	for (int i = 0; i < NBOBUSALLOWED; i++){ // On parcours le tableau de pointeurs d'obus relativement
		if (TabPointeursObus[i] != NULL){
			//if (TabPointeursObus[i]->timingDeplacementObus%800 == 0){
				//deplacement_obus_terminal(TabPointeursObus[i]);
				animation_bullet(fake_map, TabPointeursObus[i]); // Animation par accoup de l'obus
				/*TabPointeursObus[i]->timingDeplacementObus = 1;
			}
			(TabPointeursObus[i]->timingDeplacementObus)++;*/
		}		
	}
}
