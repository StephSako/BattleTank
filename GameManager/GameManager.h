#include "GameManager.c"

OBUSP * allocation_dyn_tab_obus();
int * allocation_dyn_tab_repar_tank_ennemis();
void afficher_nb_tanks_defaite();
void init_terminal();
void quit_terminal();
void initialiserLaPartieSelonLeMode();
void MenuSelectionMode();
int nb_tank_weak();
int nb_tank_medium();
int nb_tank_strong();
void liberer_matrice_all();
