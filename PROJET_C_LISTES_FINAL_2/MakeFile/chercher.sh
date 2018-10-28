#/bin/bash

ligneStrictVide=`cat ../Deplacer/deplacement_curseur.c ../Deplacer/deplacement_curseur.h ../Deplacer/deplacement_objet.c ../Deplacer/deplacement_objet.h ../Deplacer/key_pressed.c ../Deplacer/key_pressed.h ../Jouer_sons/scriptSons.sh ../Modèle/tanktype.h ../TankEnnemis/TankEnnemis.c ../TankEnnemis/TankEnnemis.h ../Tirer/tirer_obus.c ../Tirer/tirer_obus.h ../Traiter_fichiers_texte/treatment_mat.c ../Traiter_fichiers_texte/treatment_mat.h ../Traiter_fichiers_texte/flux_fichier.c ../Traiter_fichiers_texte/flux_fichier.h ../MakeFile/makefile ../MakeFile/main.c |grep -v [a-zA-Z] | grep -v } | wc -l`

lignesTotal=`cat ../Deplacer/deplacement_curseur.c ../Deplacer/deplacement_curseur.h ../Deplacer/deplacement_objet.c ../Deplacer/deplacement_objet.h ../Deplacer/key_pressed.c ../Deplacer/key_pressed.h ../Jouer_sons/scriptSons.sh ../Modèle/tanktype.h ../TankEnnemis/TankEnnemis.c ../TankEnnemis/TankEnnemis.h ../Tirer/tirer_obus.c ../Tirer/tirer_obus.h ../Traiter_fichiers_texte/treatment_mat.c ../Traiter_fichiers_texte/treatment_mat.h ../Traiter_fichiers_texte/flux_fichier.c ../Traiter_fichiers_texte/flux_fichier.h ../MakeFile/makefile ../MakeFile/main.c | wc -l`

ligneStrictNonVide=$(($lignesTotal-$ligneStrictVide))

echo $lignesTotal lignes au total et $ligneStrictNonVide lignes non-vides.;
