#ifndef LISTETYPE_H
#define LISTETYPE_H

#include "element.h"
#include "Bool.h"

#define ERROR_MALLOC_ITEM -1
#define ERROR_LISTE_VIDE -2

typedef struct MaillonListeType{
		Type t;
        struct MaillonListeType* next;
}MaillonListeType;

///
/// \struct ListeType Liste de type d'animaux, sert pour les prédations
///
typedef struct ListeType {
	int taille;
    struct MaillonListeType *Top;
	void(*Free)();
	int(*Push)(struct ListeType*, Type t);
	Type(*Pop)(struct ListeType*);
	void(*Clear)(struct ListeType*);
	int(*Taille)(struct ListeType*);
	Bool (*Contain)(struct ListeType*, Type t);
}ListeType;

int ListeType_Taille(ListeType* This);
void ListeType_Clear(ListeType *This);
void ListeType_New_Free(ListeType *This);
int ListeType_Push(ListeType* This, Type t);
Type ListeType_Pop(ListeType* This);
ListeType* New_ListeType();
void ListeType_Init(ListeType* This);
Bool ListeType_Contain(ListeType*This, Type t);

#endif // LISTETYPE_H
