void deleteTANK(TANK *tankSelectionne){

	TANK *headTank = ListeTanks->premier; // Tête de la liste chaînée

	// Si le tank à supprimer est la tête de liste (donc le joueur)
	if(head == tankSelectionne && head->suivant != NULL){  // S'il reste bien plus qu'un tank dans la liste
		
		/* Copy the data of suivant node to head */
		head->data = head->suivant->data; 

		// On stocke l'addresse du tank suivant 
		tankSelectionne = head->suivant; 

		// On supprime le lien du tank suivant
		head->suivant = head->suivant->suivant; 
	}
	else {
		// On doit trouver le tank précédent
		TANK *prev = head;
		while(prev->suivant != NULL && prev->suivant != n) 
		prev = prev->suivant; 

		// Supprimer le tank de la liste chaînée
		prev->suivant = prev->suivant->suivant;
	}
	
	// On libère la mémoire
	free(tankSelectionne);
}
