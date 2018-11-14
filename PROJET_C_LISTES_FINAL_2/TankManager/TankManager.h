#include "TankManager.c"

struct TANK *creer_tank_joueur(int pos_x, int pos_y, char direction);
void creer_tank_ennemis(int pos_x, int pos_y, char direction);
void deplacer_tank_ennemis_terminal();
void deplacer_tank_joueur_terminal(struct TANK *joueur);
