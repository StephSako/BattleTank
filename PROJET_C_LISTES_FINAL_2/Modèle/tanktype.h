/***********************************************************Imports des bibliothèques**********************************************************/
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

/***********************************************************Définitions des couleurs d'affichage************************************************/
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

/***********************************************************Variables globales******************************************************************/

// Dimensions de la map
#define LONGUEURMAP 37
#define LARGEURMAP 145

// Dimensions des tanks joueurs et ennemis
#define LONGUEURTANK 3
#define LARGEURTANK 5

#define PETITASCII 15 // Pour les petits caractères ASCII OEM
#define GRANDASCII 20 // Pour les grands caractères ASCII OEM

int NBOBUSALLOWED; // Nombre d'obus autorisé à apparaitre sur la map selon le mode choisi

// 20 tanks ennemis en mode facile ou 30 tanks ennemis en mode difficile
int NBTANKTOTAL;
#define NBTANKWEAKFACILE 7 // Nombre total de tanks ennemis faibles
#define NBTANKMEDIUMFACILE 7 // Nombre total de tanks ennemis moyens
#define NBTANKSTRONGFACILE 6 // Nombre total de tanks ennemis forts

#define NBTANKWEAKDIFFICILE 10
#define NBTANKMEDIUMDIFFICILE 10
#define NBTANKSTRONGDIFFICILE 10

#define NBCOUPSABIMENT 3 // Nombre de coups pour les blindages faibles se détruisent, et les blindages moyens et forts rétrogradent

// Position du selecteur de choix dans le menu
int choix_x = 10;
int choix_y = 102;

// Mode de jeu
int mode = 0; 	/* MODE TERMINAL FACILE => 11
			MODE TERMINAL DIFFICILE => 12
			MODE TERMINAL FACILE => 21
			MODE TERMINAL DIFFICILE => 22
			MODE QUITTER => 3*/
char key;

/***********************************************************Variables globales des carrosseries*************************************************/

// On déclare les carrosseries de tank du joueur
char **carrosserieWTH; char **carrosserieWTG; char **carrosserieWTD; char **carrosserieWTB;
char **carrosserieMTH; char **carrosserieMTG; char **carrosserieMTD; char **carrosserieMTB;
char **carrosserieSTH; char **carrosserieSTG; char **carrosserieSTD; char **carrosserieSTB;

char *PATHMAPTERMINAL = "../Modèle/Fichiers_texte_map/map"; // Chemin de la map
char *PATHMAPGRAPHIQUE = "../Modèle/Fichiers_texte_map/map_graphique"; // Chemin de la map
char **true_map; // Tableau contenant la map soit terminal ou graphique à afficher

char *PATHMENU = "../Modèle/Fichiers_texte_menu/main_menu"; // Chemin du menu principal
char *PATHMENUTERMINAL = "../Modèle/Fichiers_texte_menu/main_menu_mode_terminal"; // Chemin du menu terminal
char *PATHMENUGRAPHIQUE = "../Modèle/Fichiers_texte_menu/main_menu_mode_graphique"; // Chemin du menu graphique

/**********************************************************Structure du tank du joueur**********************************************************/

// Liste chaînée des structures des tanks
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

struct TANK *head; // Création de la liste

int joueurMort = 0;

int vieJoueur = 9;

// Tableau indiquant le nombre de tanks faibles, moyens et forts
int *repartitionTankEnnemis;

// Nombre de tank total en mode facile à générer au cours de la partie par vague de 2
int nb_tank_wave = 0;

/***********************************************************************************************************************************************/

// Structure des obus
typedef struct{
	int pos_x;
	int pos_y;
	char direction;
	int provenance; // 0 : tank ennemi faible, 1 : tank ennemi moyen, 2 : tank ennemi fort
	char camp;
} OBUS;

// Pointeur sur l'objet OBUS
typedef OBUS * OBUSP;

// Tableau de pointeurs d'obus permettant de les fair déplacer tous en même temps par accoups
OBUSP *TabPointeursObus;

/***********************************************************************************************************************************************/
// Fonction qui permet de mettre un délai sans bloquer le programme
void delay(int NbSecondes){
	int seuil = 0;
	while(seuil <= NbSecondes){
		int n = rand()%(10);		
		if (n == 5) seuil++;
	}
}

/***********************************************************Variable du pioupiou****************************************************************/

int pioupiouAlive = 1;
