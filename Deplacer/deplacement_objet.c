#include "../Deplacer/deplacement_curseur.h"

void effacer_map_tank(struct TANK *joueur){
	for (int i = joueur->pos_x; i < joueur->pos_x+LONGUEURTANK; i++){
		for (int j = joueur->pos_y; j < joueur->pos_y+LARGEURTANK; j++){
			fake_map[i][j] = ' ';
		}
	}
}

void remplir_map_tank(struct TANK *joueur){
	for (int i = joueur->pos_x; i < joueur->pos_x+LONGUEURTANK; i++){
		for (int j = joueur->pos_y; j < joueur->pos_y+LARGEURTANK; j++){
			fake_map[i][j] = 'T';
		}
	}
	fake_map[joueur->pos_x][joueur->pos_y] = '*';
}

void deplacement_tank_bas(struct TANK *joueur){
	affichage_tank_terminal(joueur); // On peut orienter le tank même s'il est contre un mur

	if (joueur->pos_x < (LONGUEURMAP-3) && fake_map[joueur->pos_x+3][joueur->pos_y] == ' ' &&
	fake_map[joueur->pos_x+3][joueur->pos_y+1] == ' ' &&
	fake_map[joueur->pos_x+3][joueur->pos_y+2] == ' ' &&
	fake_map[joueur->pos_x+3][joueur->pos_y+3] == ' ' &&
	fake_map[joueur->pos_x+3][joueur->pos_y+4] == ' '){
		effacer_tank_terminal(joueur); // On efface le joueur dans le terminal	
		effacer_map_tank(joueur); // On efface le joueur dans la fake map
		
		joueur->pos_x++; // On met à jour la position du joueur
		
        	remplir_map_tank(joueur); // On déplace et remplit le tank du joueur dans la fake map        	
		affichage_tank_terminal(joueur); // On déplace le tank sur le terminal	
        }
}
     
void deplacement_tank_droite(struct TANK *joueur){
	affichage_tank_terminal(joueur);

	if (joueur->pos_y < (LARGEURMAP-1) && fake_map[joueur->pos_x][joueur->pos_y+5] == ' ' &&
	fake_map[joueur->pos_x+1][joueur->pos_y+5] == ' ' &&
	fake_map[joueur->pos_x+2][joueur->pos_y+5] == ' ' && 
	(joueur->pos_x != 30 || joueur->pos_y != 131)){ // Eviter de rentrer dans la rampe de lancement des tanks ennemis pour eviter les spawnkill
		effacer_tank_terminal(joueur);		
		effacer_map_tank(joueur);
		
		joueur->pos_y++;
		
        	remplir_map_tank(joueur);        	
		affichage_tank_terminal(joueur);
        }
}

void deplacement_tank_haut(struct TANK *joueur){
	affichage_tank_terminal(joueur);

	if (joueur->pos_x > 0 && fake_map[joueur->pos_x-1][joueur->pos_y] == ' ' &&
	fake_map[joueur->pos_x-1][joueur->pos_y+1] == ' ' &&
	fake_map[joueur->pos_x-1][joueur->pos_y+2] == ' ' &&
	fake_map[joueur->pos_x-1][joueur->pos_y+3] == ' ' &&
	fake_map[joueur->pos_x-1][joueur->pos_y+4] == ' '){
		effacer_tank_terminal(joueur);		
		effacer_map_tank(joueur);
		
		joueur->pos_x--;
		
        	remplir_map_tank(joueur);        	
		affichage_tank_terminal(joueur);
        }
}

void deplacement_tank_gauche(struct TANK *joueur){
	affichage_tank_terminal(joueur);

        if (joueur->pos_y > 0 && fake_map[joueur->pos_x][joueur->pos_y-1] == ' ' &&
        fake_map[joueur->pos_x+1][joueur->pos_y-1] == ' ' &&
        fake_map[joueur->pos_x+2][joueur->pos_y-1] == ' ' && 
	(joueur->pos_x != 4 || joueur->pos_y != 8)){
		effacer_tank_terminal(joueur);		
		effacer_map_tank(joueur);
		
		joueur->pos_y--;
		
        	remplir_map_tank(joueur);        	
		affichage_tank_terminal(joueur);
        }
}
