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
		if (temp->pos_x == pos_xTankAttaque && temp->pos_y == pos_yTankAttaque){
			temp->nb_impacts++;

			switch(temp->nb_impacts){
				case NBCOUPSABIMENT : // A partir de NBCOUPSABIMENT pour chaque blindage, la carrosserie s'abîme
					switch(temp->blindage){
						case 0 :
							effacer_tank_terminal(temp); // On efface le tank dans le terminal
							effacer_map_tank(mat, temp); // On efface le tank dans la fake_map
							
							temp->etat = 0;
							SupprimerTank(&head, position);
							system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosion.mp3");
							
							break;
						case 1 : 
							switch(temp->direction){
								case 'A': temp->carrosserie = carrosserieWTH; break;
								case 'B': temp->carrosserie = carrosserieWTB; break;
								case 'C': temp->carrosserie = carrosserieWTD; break;
								case 'D': temp->carrosserie = carrosserieWTG; break;
								default : break;
								
							} temp->blindage--; temp->nb_impacts = 0;
							effacer_tank_terminal(temp);
							affichage_tank_terminal(temp); break;
							
						case 2 :
							switch(head->direction){ // A partir de 3 coups, la carrosserie s'abîme
								case 'A': temp->carrosserie = carrosserieMTH; break;
								case 'B': temp->carrosserie = carrosserieMTB; break;
								case 'C': temp->carrosserie = carrosserieMTD; break;
								case 'D': temp->carrosserie = carrosserieMTG; break;
								default : break;
								
							} temp->blindage--; temp->nb_impacts = 0;
							effacer_tank_terminal(temp);
							affichage_tank_terminal(temp); break;
							
						default : break;
					}
									
				default : break;
				
			}
			break; // Nous avons impacté le bon tank en lui abîmant sa carrosserie et en le réaffichant
		}
		temp = temp->suivant; // On passe au tank ennemi suivant dans la liste chaînée des tanks ennemis
		position++;
	}
}

void animation_bullet(char **mat, OBUSP obusP, char car){
	if (obusP->pos_y <= LARGEURMAP && obusP->pos_y >= 0 && obusP->pos_x < LONGUEURMAP-1 && obusP->pos_x > 0 && 
		mat[obusP->pos_x][obusP->pos_y] == ' '){						// Tant que l'obus ne percute pas d'obstacle
		
		deplacement_obus_terminal(obusP, car);						// On affiche l'obus dans le terminal
		fflush(stdout);										// On vide le buffer de sortie (on force l'affichage)
		mat[obusP->pos_x][obusP->pos_y] = car;						// On ajoute l'obus dans la fake map
	}
	else if (mat[obusP->pos_x][obusP->pos_y] == 'C'){
		effacer_obus_terminal(obusP);								// On efface l'obus dans le terminal
		mat[obusP->pos_x][obusP->pos_y] = ' ';						// On efface l'obus dans la fake map
		DeleteObusPTab(obusP);									// On supprime l'obus dans le tableau de pointeurs d'obus 															pour ne plus le traiter
		system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosion.mp3"); 	// On joue un bruitage à l'aide d'un script (execute en 															background)
	}
	else if (mat[obusP->pos_x][obusP->pos_y] == 'B' && obusP->camp == 'E'){		// Un tank ENNEMI a tiré sur la bombe à protéger
		pioupiouAlive = 0;
		effacer_obus_terminal(obusP);
		mat[obusP->pos_x][obusP->pos_y] = ' ';
		DeleteObusPTab(obusP);
		system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosionFin.mp3");
	}
	// Briques non destructibles
	else if 	(mat[obusP->pos_x][obusP->pos_y] == 'X' ||
			mat[obusP->pos_x][obusP->pos_y] == 'P' ||
			mat[obusP->pos_x][obusP->pos_y] == 'E' ||
			mat[obusP->pos_x][obusP->pos_y] == 'Y')
			
			// Un tank ENNEMI SUPERARME tire sur un bloc dur
			if (mat[obusP->pos_x][obusP->pos_y] == 'P' && obusP->provenance == 2 && obusP->camp == 'E'){
				effacer_obus_terminal(obusP);
				mat[obusP->pos_x][obusP->pos_y] = ' ';
				DeleteObusPTab(obusP);
				system("../Jouer_sons/./scriptSons.sh ../Jouer_sons/explosion.mp3");
			}
			else DeleteObusPTab(obusP); // On supprime l'obus du tableau de pointeurs 
			
	else{ // Gestion des collisions avec les tanks ennemis
		AttaquerTank(mat, obusP); // On cherche le tank et on l'attaque s'il y en a eu un de touché
		DeleteObusPTab(obusP); // On supprime l'obus qui a percuté un obstacle
	}
}

void shot_creator(struct TANK *joueurP){
	if (firstEmptyIndexObusTab() < NBOBUSALLOWED){ // Si on n'atteint pas le nombre d'obus tires maximum à l'ecran
					
		OBUSP obus = malloc(sizeof(OBUS)); // On declare un NOUVEAU pointeur de l'obus cree	
		obus->provenance = joueurP->blindage;
		obus->camp = joueurP->camp;	
		// On deplace l'obus dans le terminal / la fake map
		switch(joueurP->direction){ // On initialise les attributs de l'obus tire en fonction des attributs du tank
			case 'A':
				obus->pos_x = joueurP->pos_x-1; obus->pos_y = joueurP->pos_y+2; obus->direction = joueurP->direction; break;
			case 'D':
				obus->pos_x = joueurP->pos_x+1; obus->pos_y = joueurP->pos_y-1; obus->direction = joueurP->direction; break;
			case 'B':
				obus->pos_x = joueurP->pos_x+3; obus->pos_y = joueurP->pos_y+2; obus->direction = joueurP->direction; break;
			case 'C':
				obus->pos_x = joueurP->pos_x+1; obus->pos_y = joueurP->pos_y+5; obus->direction = joueurP->direction; break;
			default : break;
		}
		TabPointeursObus[firstEmptyIndexObusTab()] = obus; // On ajoute le pointeur d'obus dans le tableau
	}
}

void shot_manager(char **fake_map){
	// On parcourt le tableau des obus pour tous les faire deplacer d'un accoup en même temps : c'est naturel
	for (int i = 0; i < NBOBUSALLOWED; i++){ // On parcours le tableau de pointeurs d'obus relativement
		if (TabPointeursObus[i] != NULL){
			switch(TabPointeursObus[i]->direction){
				case 'A': animation_bullet(fake_map, TabPointeursObus[i], '^'); break; // Animation par accoup de l'obus
				case 'D': animation_bullet(fake_map, TabPointeursObus[i], '<'); break;	
				case 'B': animation_bullet(fake_map, TabPointeursObus[i], 'v'); break;	
				case 'C': animation_bullet(fake_map, TabPointeursObus[i], '>'); break;
				default : break;
			}
		}
	}
}

void shot_cleaner(char **fake_map){
	// On parcourt le tableau des obus pour tous les effacer du terminal et de la fake map
	for (int i = 0; i < NBOBUSALLOWED; i++){ // On parcours le tableau de pointeurs d'obus relativement
		if (TabPointeursObus[i] != NULL){
		
			effacer_obus_terminal(TabPointeursObus[i]); // On efface tous les obus encore en "vie"
			fake_map[TabPointeursObus[i]->pos_x][TabPointeursObus[i]->pos_y] = ' ';
			
			switch(TabPointeursObus[i]->direction){
				case 'A': TabPointeursObus[i]->pos_x--; break; // On incremente les positions des obus = le fameux 'accoup'
				case 'D': TabPointeursObus[i]->pos_y--; break;	
				case 'B': TabPointeursObus[i]->pos_x++; break;	
				case 'C': TabPointeursObus[i]->pos_y++; break;
				default : break;
			}
		}
	}
}
