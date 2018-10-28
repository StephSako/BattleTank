#include <stdlib.h>
#include <stdio.h>

// Structure des obus
typedef struct{
	int pos_x;
	int pos_y;
	char direction;
} OBUS;
typedef OBUS * OBUSP;

OBUSP *tab;

int firstEmptyIndexObusTab(){
	int n = 0;
	while (n < (10-1) && tab[n] != NULL){
		n++;
	}
	return n;
}

int main(){

	tab = malloc(10 * sizeof(OBUSP));
	
	printf("%d\n", firstEmptyIndexObusTab());

	// Chargement
	for (int i = 0; i < 10; i++){
		OBUS *obus = malloc(sizeof(OBUS));
		
		obus->pos_y = i;
		obus->pos_x = i+i;
		obus->direction = 'e';
		
		tab[firstEmptyIndexObusTab()] = obus;		
	}
	
	printf("%d\n", firstEmptyIndexObusTab());

	for (int i = 0; i < 10; i++){
		printf("INDICE %d = %p pos_y : %d, pos_x : %d, dir : %c\n", i, tab[i], tab[i]->pos_y, tab[i]->pos_x, tab[i]->direction);
	}
	
	printf("\nON CHANGE LES VARIABLES\n");
	for (int i = 0; i < 10; i++){
		tab[i]->pos_y = tab[i]->pos_y + 25;
		tab[i]->pos_x = tab[i]->pos_x + 50;
	}
	
	printf("\nAFFICHAGE\n");
	for (int i = 0; i < 10; i++){
		printf("INDICE %d = %p pos_y : %d, pos_x : %d, dir : %c\n", i, tab[i], tab[i]->pos_y, tab[i]->pos_x, tab[i]->direction);
	}
	
	printf("\nON SUPPRIME UNE PARTIE = free\n");
	for (int i = 4; i <= 8; i++){
		free(tab[i]);
		tab[i] = NULL;
	}
	
	printf("\nAFFICHAGE AVANT AJOUT\n");
	for (int i = 0; i < 10; i++){
		if (tab[i] == NULL)
			printf("INDICE %d = NULL\n", i);
		else
			printf("INDICE %d = %p pos_y : %d, pos_x : %d, dir : %c\n", i, tab[i], tab[i]->pos_y, tab[i]->pos_x, tab[i]->direction);
	}
	
	OBUS *obus = malloc(sizeof(OBUS));
		
	obus->pos_y = 999;
	obus->pos_x = 999;
	obus->direction = 's';
	
	tab[firstEmptyIndexObusTab()] = obus;	
	
	printf("\nDERNIER AFFICHAGE\n");
	for (int i = 0; i < 10; i++){
		if (tab[i] == NULL)
			printf("INDICE %d = NULL\n", i);
		else
			printf("INDICE %d = %p pos_y : %d, pos_x : %d, dir : %c\n", i, tab[i], tab[i]->pos_y, tab[i]->pos_x, tab[i]->direction);
	}
	
	printf("\nAFFICHAGE TEST\n");
	for (int i = 0; i < 10; i++){
		if (tab[i] != NULL)
			printf("INDICE %d = %d\n", i, tab[i]->pos_y);
	}
	
	OBUS *obus2 = tab[9];
	
	printf("\nAFFICHAGE RECHERCHE\n");
	int i = 0;
	while( i < 10){
		if (tab[i] == obus2){
			printf("INDICE %d\n", i);
			break;
		}
		i++;
	}
	
	printf("\n1ER INDICE VDIE : %d\n\n", firstEmptyIndexObusTab());
	
	int gf=0;
	while(gf<5){
		
		if (gf == 3) break;
		printf("%d\n", gf);
		gf++;
	}

	return 0;
}
