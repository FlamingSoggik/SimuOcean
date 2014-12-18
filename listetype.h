#ifndef LISTE_H
#define LISTE_H

#include "element.h"

#define ERROR_MALLOC_ITEM -1
#define ERROR_LISTE_VIDE -2

typedef struct MaillonListeType{
		Type t;
        struct MaillonListeType* next;
}MaillonListeType;

typedef struct ListeType {
	int taille;
    struct MaillonListeType *Top;
	void(*Free)();
	int(*Push)(struct ListeType*, Type t);
	void(*Pop)(struct ListeType*);
	void(*Clear)(struct ListeType*);
	int(*Taille)(struct ListeType*);
}ListeType;

int ListeType_Taille(ListeType* This);
void ListeType_Clear(ListeType *This);
void ListeType_New_Free(ListeType *This);
int ListeType_Push(ListeType* This, Type t);
Type ListeType_Pop(ListeType* This);
ListeType* New_ListeType();
void ListeType_Init(ListeType* This);

#endif // LISTE_H
