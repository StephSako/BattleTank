#include "tirer_obus.c"

int firstEmptyIndexObusTab();
void DeleteObusPTab(OBUSP obusPDeleted);
void SupprimerTank(struct TANK **head, int position);
void AttaquerTank(OBUSP obusP);
void animation_bullet(OBUSP obusP);
void shot_creator(struct TANK *tank);
void shot_manager();
