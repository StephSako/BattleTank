#include "../Deplacer/deplacement_curseur.c"

void gotoxy(int x, int y);
void affichage_tank_terminal(struct TANK *tank);
void effacer_tank_terminal(struct TANK *tank);
void effacer_obus_terminal(int x, int y);
void deplacement_obus_terminal(OBUSP obus);
void deplacement_choix(int x, int y);
void afficher_string(int x, int y, char* message);
void afficher_message_int(int x, int y, int nb);
void afficher_message_vie(int x, int y, int vie);
void effacer_choix(int x, int y);
