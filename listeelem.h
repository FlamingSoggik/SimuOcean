#ifndef LISTE_H
#define LISTE_H

#include "element.h"

#define ERROR_MALLOC_ITEM -1
#define ERROR_LISTE_VIDE -2
#define ERROR_BAD_TYPE_ELEMENT -3
#define ERROR_ONE_PONT_MAX -4


typedef struct ItemListeElem{
		Element* e;
		struct ItemListeElem* next;
}ItemListeElem;

typedef struct ListeElem {
	int taille;
	struct ItemListeElem *Top;
	void(*Free)();
	int(*Push)(struct ListeElem*, struct Element*);
	void(*Pop)(struct ListeElem*);
	void(*Clear)(struct ListeElem*);
	int(*Taille)(struct ListeElem*);
	char (*HasAPont)(struct ListeElem*);
	char (*HasAPecheur)(struct ListeElem*);
	char (*HasAnAnimal)(struct ListeElem*);
}ListeElem;

int ListeElem_Taille(ListeElem* This);
void ListeElem_Clear(ListeElem *This);
void ListeElem_New_Free(ListeElem *This);
int ListeElem_Push(ListeElem* This, Element *e);
Element* ListeElem_Pop(ListeElem* This);
ListeElem* New_ListeElem();
void ListeElem_Init(ListeElem* This);
char ListeElem_hasAPecheur(ListeElem* This);
char ListeElem_hasAPont(ListeElem* This);
char ListeElem_hasAnAnimal(ListeElem* This);

#endif // LISTE_H
