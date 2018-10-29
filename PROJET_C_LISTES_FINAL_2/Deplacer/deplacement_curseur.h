#include "../Deplacer/deplacement_curseur.c"

void gotoxy(int x, int y);
void affichage_tank_terminal(struct TANK *tank);
void effacer_tank_terminal(struct TANK *tank);
void effacer_obus_terminal(OBUSP obus);
void deplacement_obus_terminal(OBUSP obus, char car);
void deplacement_choix(int x, int y);
void afficher_message(int x, int y, char* message);
void effacer_choix(int x, int y);
void init_terminal();
void fin_win();
void fin_game_over();
void quit_terminal();
