#/bin/bash

ligneStrictVide=`cat ../Deplacer/deplacement_curseur.c ../Deplacer/deplacement_curseur.h ../Deplacer/deplacement_objet.c ../Deplacer/deplacement_objet.h ../Deplacer/key_pressed.c ../Deplacer/key_pressed.h ../Jouer_sons/scriptSons.sh ../Modèle/tanktype.h ../TankManager/TankManager.c ../TankManager/TankManager.h ../Tirer/tirer_obus.c ../Tirer/tirer_obus.h ../Traiter_fichiers_texte/treatment_mat.c ../Traiter_fichiers_texte/treatment_mat.h ../Traiter_fichiers_texte/flux_fichier.c ../Traiter_fichiers_texte/flux_fichier.h ../MakeFile/makefile ../MakeFile/main.c ../GameManager/GameManager.c ../GameManager/GameManager.h |grep -v [a-zA-Z] | grep -v } | wc -l`

lignesTotal=`cat ../Deplacer/deplacement_curseur.c ../Deplacer/deplacement_curseur.h ../Deplacer/deplacement_objet.c ../Deplacer/deplacement_objet.h ../Deplacer/key_pressed.c ../Deplacer/key_pressed.h ../Jouer_sons/scriptSons.sh ../Modèle/tanktype.h ../TankManager/TankManager.c ../TankManager/TankManager.h ../Tirer/tirer_obus.c ../Tirer/tirer_obus.h ../Traiter_fichiers_texte/treatment_mat.c ../Traiter_fichiers_texte/treatment_mat.h ../Traiter_fichiers_texte/flux_fichier.c ../Traiter_fichiers_texte/flux_fichier.h ../MakeFile/makefile ../MakeFile/main.c ../GameManager/GameManager.c ../GameManager/GameManager.h | wc -l`

caractStrictVide=`cat ../Deplacer/deplacement_curseur.c ../Deplacer/deplacement_curseur.h ../Deplacer/deplacement_objet.c ../Deplacer/deplacement_objet.h ../Deplacer/key_pressed.c ../Deplacer/key_pressed.h ../Jouer_sons/scriptSons.sh ../Modèle/tanktype.h ../TankManager/TankManager.c ../TankManager/TankManager.h ../Tirer/tirer_obus.c ../Tirer/tirer_obus.h ../Traiter_fichiers_texte/treatment_mat.c ../Traiter_fichiers_texte/treatment_mat.h ../Traiter_fichiers_texte/flux_fichier.c ../Traiter_fichiers_texte/flux_fichier.h ../MakeFile/makefile ../MakeFile/main.c ../GameManager/GameManager.c ../GameManager/GameManager.h |grep -v [a-zA-Z] | grep -v } | wc -m`

caractTotal=`cat ../Deplacer/deplacement_curseur.c ../Deplacer/deplacement_curseur.h ../Deplacer/deplacement_objet.c ../Deplacer/deplacement_objet.h ../Deplacer/key_pressed.c ../Deplacer/key_pressed.h ../Jouer_sons/scriptSons.sh ../Modèle/tanktype.h ../TankManager/TankManager.c ../TankManager/TankManager.h ../Tirer/tirer_obus.c ../Tirer/tirer_obus.h ../Traiter_fichiers_texte/treatment_mat.c ../Traiter_fichiers_texte/treatment_mat.h ../Traiter_fichiers_texte/flux_fichier.c ../Traiter_fichiers_texte/flux_fichier.h ../MakeFile/makefile ../MakeFile/main.c ../GameManager/GameManager.c ../GameManager/GameManager.h | wc -m`

ligneStrictNonVide=$(($lignesTotal-$ligneStrictVide))
caractStrictNonVide=$(($caractTotal-$caractStrictVide))

echo $lignesTotal lignes au total et $ligneStrictNonVide lignes non-vides.;
echo $caractTotal lettres au total et $caractStrictNonVide lettres de lignes non-vides;
