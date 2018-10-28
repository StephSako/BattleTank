#include "TankEnnemis.c"

struct TANK *creer_tank_joueur(struct TANK **head, int pos_x, int pos_y, char direction, int blindage_origine, int nb_impacts, char camp, int etat);
void creer_tank_ennemis(struct TANK **head, int pos_x, int pos_y, char direction, int nb_impacts, int etat);
void deplacer_tank_ennemis_terminal(char **fake_map, struct TANK *tankSelectionne);
void deplacer_tank_joueur_terminal(char **fake_map, struct TANK **joueurP);
int NbEnnemisTanksToCreate();
