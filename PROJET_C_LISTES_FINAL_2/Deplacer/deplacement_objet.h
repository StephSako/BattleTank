#include "deplacement_objet.c"

void deplacement_tank_bas(char **fake_map, struct TANK *joueur);
void deplacement_tank_droite(char **fake_map, struct TANK *joueur);
void deplacement_tank_haut(char **fake_map, struct TANK *joueur);
void deplacement_tank_gauche(char **fake_map, struct TANK *joueur);
void effacer_map_tank(char **fake_map, struct TANK *joueur);
void remplir_map_tank(char **fake_map, struct TANK *joueur);
