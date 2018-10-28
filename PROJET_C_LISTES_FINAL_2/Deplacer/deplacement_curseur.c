#include "../Traiter_fichiers_texte/treatment_mat.h"

void gotoxy(int x, int y){
	printf("\033[%d;%dH", (x+1), (y+1));
}

void affichage_tank_terminal(struct TANK *tank){
	if (tank->camp == 'E') printf("%s", RED);
	else if (tank->camp == 'P') printf("%s", GREEN);
	
	for (int i = 0; i < LONGUEURTANK; i++){
		gotoxy(tank->pos_x+i, tank->pos_y);
		for (int j = 0; j < PETITASCII; j++){			
			printf("%c", tank->carrosserie[i][j]);
		}
	}
	printf("%s", NORMAL);
}

void effacer_tank_terminal(struct TANK *tank){	
	for (int i = 0; i < LONGUEURTANK; i++){
		gotoxy(tank->pos_x + i, tank->pos_y);
		for (int j = 0; j < LARGEURTANK; j++){
			printf(" ");
		}
	}
}

void effacer_obus_terminal(OBUSP obus){	
	gotoxy(obus->pos_x, obus->pos_y);
	printf(" ");
}

void deplacement_obus_terminal(OBUSP obus, char direction){
	gotoxy(obus->pos_x, obus->pos_y);
	printf("%c", direction);
}

void deplacement_choix(int x, int y){
	gotoxy(x, y);
	printf("%s►", RED); // Afficher le selecteur en rouge
	printf("%s", NORMAL); // Remettre la couleur blanche d'écriture
}

void afficher_message(int x, int y, char* message){
	gotoxy(x, y);
	printf("%s", message);
}

void effacer_choix(int x, int y){
	gotoxy(x, y);
	printf(" ");
}

void init_terminal(){
	system("clear"); // On nettoie le terminal
	system("setterm -cursor off"); // On n'affiche pas le curseur clignotant dans le terminal
	system("stty -echo"); // Ne pas afficher les lettres/codes flèches tappées dans le terminal
	
	TabPointeursObus = allocation_dyn_tab(NBOBUSALLOWED); // Allocation dynamique du tableau de pointeurs d'obus
}

void quit_terminal(){
	system("clear");
	afficher_message(15, 60, "Vous quittez le jeu ...");
	fflush(stdout);
	system("sleep 1");
	system("setterm -cursor on");
	system("stty echo");
	system("clear");
}
