#include "tirer_obus.c"

int firstEmptyIndexObusTab();
void DeleteObusPTab(OBUSP obusPDeleted);
void SupprimerTank(struct TANK **head, int position);
void AttaquerTank(char **mat, OBUSP obusP);
void animation_bullet(char **mat, OBUSP obusP);
void shot_creator(struct TANK *tank);
void shot_manager(char **fake_map);
