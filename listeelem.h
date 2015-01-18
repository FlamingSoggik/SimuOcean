#ifndef LISTEELEM_H
#define LISTEELEM_H

#include "element.h"
#include "Bool.h"

#define ERROR_MALLOC_ITEM -1
#define ERROR_LISTE_VIDE -2
#define ERROR_BAD_TYPE_ELEMENT -3
#define ERROR_ONE_PONT_MAX -4
#define ERROR_ONE_TERRE_MAX -5
#define ERROR_ELEMENT_PASSED_NULL -6


typedef struct MaillonListeElem{
        struct Element* e;
        struct MaillonListeElem* next;
}MaillonListeElem;

typedef struct ListeElem {
	unsigned int taille;
    struct MaillonListeElem *Top;
	void(*Free)(struct ListeElem*);
	int(*Push)(struct ListeElem*, struct Element*);
	struct Element* (*Pop)(struct ListeElem*);
	void(*Clear)(struct ListeElem*);
	void(*Vider)(struct ListeElem*);
	unsigned int(*Taille)(struct ListeElem*);
	char (*HasAPont)(struct ListeElem*);
	char (*HasDirt)(struct ListeElem*);
	char (*HasAPecheur)(struct ListeElem*);
	char (*HasAnAnimal)(struct ListeElem*);
	struct Element* (*getAnimal)(struct ListeElem*);
	struct Element* (*getPont)(struct ListeElem*);
	struct Element* (*getDirt)(struct ListeElem*);
	struct Element* (*getPecheur)(struct ListeElem*);
	Bool (*remove)(struct ListeElem*, struct Element*);
	Bool (*deleteElement)(struct ListeElem*, struct Element*);
	void (*Print)(struct ListeElem*);
	struct Element* (*getNieme)(struct ListeElem*, unsigned int);
}ListeElem;

unsigned int ListeElem_Taille(ListeElem* This);
void ListeElem_Clear(ListeElem *This);
void ListeElem_Vider(ListeElem *This);
void ListeElem_New_Free(ListeElem *This);
int ListeElem_Push(ListeElem* This, struct Element *e);
struct Element* ListeElem_Pop(ListeElem* This);
ListeElem* New_ListeElem();
void ListeElem_Init(ListeElem* This);
char ListeElem_hasAPecheur(ListeElem* This);
char ListeElem_hasAPont(ListeElem* This);
char ListeElem_hasAnAnimal(ListeElem* This);
char ListeElem_hasDirt(ListeElem* This);
struct Element* ListeElem_getAnimal(ListeElem* This);
struct Element* ListeElem_getPont(ListeElem* This);
struct Element* ListeElem_getDirt(ListeElem* This);
struct Element* ListeElem_getPecheur(ListeElem* This);
Bool ListeElem_deleteElement(ListeElem*, struct Element*);
Bool ListeElem_remove(ListeElem*, struct Element*);
void ListeElem_Print(ListeElem*);
struct Element *ListeElem_getNieme(ListeElem *This, unsigned int number);

#endif // LISTEELEM_H
