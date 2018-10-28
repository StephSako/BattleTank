// Import de bibliothèques
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// Définitions de couleurs d'affichage
#define NORMAL  "\x1B[0m"
#define RED  "\x1B[31m"
#define REDCLIGNOTANT  "\x1B[5;31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"
#define BLACK  "\x1B[30m"

// Dimensions de la map
#define LONGUEURMAP 37
#define LARGEURMAP 145

// Dimensions des tanks joueurs et ennemis
#define LONGUEURTANK 3
#define LARGEURTANK 5

#define PETITASCII 15 // Pour les petits caractères ASCII OEM
#define GRANDASCII 20 // Pour les grands caractères ASCII OEM

#define NBOBUSALLOWED 50 // Nombre d'obus autorisé à apparaitre sur la map

#define NBTANKTOTALFACILE 20 // Nombre total de tanks ennemis
#define NBTANKWEAKFACILE 8 // Nombre total de tanks ennemis faibles
#define NBTANKMEDIUMFACILE 7 // Nombre total de tanks ennemis moyens
#define NBTANKSTRONGFACILE 5 // Nombre total de tanks ennemis forts

#define NBCOUPSABIMENT 3 // Nombre de coups pour les blindages faibles se détruisent, et les blindages moyens et forts rétrogradent

/***********************************************************Variables globales**************************************************************/

// On déclare les carrosseries de tank du joueur
char **carrosserieWTH; char **carrosserieWTG; char **carrosserieWTD; char **carrosserieWTB;
char **carrosserieMTH; char **carrosserieMTG; char **carrosserieMTD; char **carrosserieMTB;
char **carrosserieSTH; char **carrosserieSTG; char **carrosserieSTD; char **carrosserieSTB;

char *PATHMAP = "../Modèle/Fichiers_texte_map/map"; // Chemin de la map
char *PATHMENU = "../Modèle/Fichiers_texte_menu/main_menu"; // Chemin du menu principal

/**********************************************************Structure du tank du joueur******************************************************/

// LIste chaînée des structures des tanks
struct TANK{
	int pos_x;
	int pos_y;
	char direction;
	
	char **carrosserie;
	int blindage;
	int blindage_origine;
	int nb_impacts;
	
	char camp;
	int etat;

	struct TANK *suivant;
};

struct TANK *head;

// Tableau indiquant le nombre de tanks faibles, moyens et forts
int *repartitionTankEnnemis;

/*************************************************************************************************************************************/

// Structure des obus
typedef struct{
	int pos_x;
	int pos_y;
	char direction;
	char provenance; // P : joueur, W : tank ennemi faible, M : // moyen, S : // fort
} OBUS;

// Pointeur sur l'objet OBUS
typedef OBUS * OBUSP;

// Tableau de pointeurs d'obus permettant de les fair déplacer tous en même temps par accoups
OBUSP *TabPointeursObus;

/*************************************************************************************************************************************/

// Fonction qui permet d'attendre sans bloquer le programme
void delay(int NbSecondes){
	int seuil = 0;
	while(seuil <= NbSecondes){
		int n = rand()%(10);		
		if (n == 5) seuil++;
	}
}
