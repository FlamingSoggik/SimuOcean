#include "case.h"

#ifndef LISTECASE_H
#define LISTECASE_H

#define ERROR_MALLOC_ITEM -1
#define ERROR_LISTE_VIDE -2
#define ERROR_BAD_TYPE_CASE -3
#define ERROR_ONE_PONT_MAX -4


typedef struct MaillonListeCase{
        struct Case* c;
        struct MaillonListeCase* next;
}MaillonListeCase;

typedef struct ListeCase {
    int taille;
    struct MaillonListeCase *Top;
    void(*Free)();
    int(*Push)(struct ListeCase*, struct Case*);
    void(*Pop)(struct ListeCase*);
    void(*Clear)(struct ListeCase*);
    int(*Taille)(struct ListeCase*);
}ListeCase;

int ListeCase_Taille(ListeCase* This);
void ListeCase_Clear(ListeCase *This);
void ListeCase_New_Free(ListeCase *This);
int ListeCase_Push(ListeCase* This, struct Case *c);
struct Case* ListeCase_Pop(ListeCase* This);
ListeCase* New_ListeCase();
void ListeCase_Init(ListeCase* This);

#endif // LISTECASE_H
