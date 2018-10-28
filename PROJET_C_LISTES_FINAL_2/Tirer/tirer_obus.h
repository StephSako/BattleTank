#include "tirer_obus.c"

int firstEmptyIndexObusTab();
void DeleteObusPTab(OBUSP obusPDeleted);
void SupprimerTank(struct TANK **head, int position);
void AttaquerTank(char **mat, OBUSP obusP);
void animation_bullet(char **mat, OBUSP obusP, char car);
void shot_creator(struct TANK *joueurP);
void shot_manager(char **fake_map);
void shot_cleaner(char **fake_map);
