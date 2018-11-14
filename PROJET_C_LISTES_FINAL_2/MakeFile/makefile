lancement: AlesieaBattle EXECUTION clean

key_pressed.o : ../Deplacer/key_pressed.h ../Modèle/tanktype.h
	gcc -c -Werror -Wall ../Deplacer/key_pressed.c
	
treatment_mat.o : ../Traiter_fichiers_texte/treatment_mat.h key_pressed.o
	gcc -c -Werror -Wall ../Traiter_fichiers_texte/treatment_mat.c

deplacement_curseur.o : ../Deplacer/deplacement_curseur.h treatment_mat.o
	gcc -c -Werror -Wall ../Deplacer/deplacement_curseur.c
	
deplacement_objet.o : ../Deplacer/deplacement_objet.h deplacement_curseur.o
	gcc -c -Werror -Wall ../Deplacer/deplacement_objet.c

tirer_obus.o : ../Tirer/tirer_obus.h deplacement_objet.o
	gcc -c -Werror -Wall ../Tirer/tirer_obus.c

flux_fichier.o : ../Traiter_fichiers_texte/flux_fichier.h tirer_obus.o
	gcc -c -Werror -Wall ../Traiter_fichiers_texte/flux_fichier.c
	
TankManager.o : ../TankManager/TankManager.h flux_fichier.o
	gcc -c -Werror -Wall ../TankManager/TankManager.c

GameManager.o : ../GameManager/GameManager.h TankManager.o
	gcc -c -Werror -Wall ../GameManager/GameManager.c

main.o : main.c GameManager.o
	gcc -c -Werror -Wall main.c
	
AlesieaBattle : main.o
	gcc -Werror -Wall main.o -o AlesieaBattle
	
EXECUTION :
	./AlesieaBattle
	
clean : AlesieaBattle
	rm -rf *.o
