void SupprimerTank(TANK *tankSelectionne, int position){
   struct TANK *tempTank = *tankSelectionne; 
  
    // Si le premier tank est supprimé
    if (position == 0){ 
        *tankSelectionne = tempTank->next;
        free(tempTank);
        return;
    } 
  
    // Nous devons trouver le tank précédent de celui que nous souhaitons supprimer pour ne pas casser la référence au suivant
    for (int i = 0; tempTank != NULL && i < (position-1); i++) tempTank = tempTank->next; 
  
    // Si la position est supèrieure au nombre de tanks
    if (tempTank == NULL || tempTank->next == NULL) return; 
  
    // Le tank tempTank->next est celui qui doit être supprimé (donc tankSelectionne) 
    TANK *next = tempTank->next->next; 
  
    // Délier le tank a supprimer de la liste 
    free(tempTank->next); // On libère la mémoire
    tempTank->next = next;
}
