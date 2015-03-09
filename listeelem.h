#ifndef LISTEELEM_H
#define LISTEELEM_H

#include "element.h"
#include "Bool.h"
#include <stdint.h>

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
	uint16_t taille;
    struct MaillonListeElem *Top;
	void(*Free)(struct ListeElem*);
	int16_t(*Push)(struct ListeElem*, struct Element*);
	struct Element* (*Pop)(struct ListeElem*);
	void(*Clear)(struct ListeElem*);
	void(*Vider)(struct ListeElem*);
	uint16_t(*Taille)(struct ListeElem*);
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
	struct Element* (*getNieme)(struct ListeElem*, uint16_t);
}ListeElem;

uint16_t ListeElem_Taille(ListeElem* This);
void ListeElem_Clear(ListeElem *This);
void ListeElem_Vider(ListeElem *This);
void ListeElem_New_Free(ListeElem *This);
int16_t ListeElem_Push(ListeElem* This, struct Element *e);
struct Element* ListeElem_Pop(ListeElem* This);
ListeElem* New_ListeElem();
void ListeElem_Init(ListeElem* This);
///
/// \brief ListeElem_hasAPecheur Renvoie 0 si pas de pecheur dans la liste 1 sinon
/// \param This Pointeur sur la liste
/// \return
///
char ListeElem_hasAPecheur(ListeElem* This);
///
/// \brief ListeElem_hasAPont Renvoie 0 si pas de pont dans la liste 1 sinon
/// \param This Pointeur sur la liste
/// \return
///
char ListeElem_hasAPont(ListeElem* This);
///
/// \brief ListeElem_hasAnAnimal Renvoie 0 si pas d'animal dans la liste 1 sinon
/// \param This Pointeur sur la liste
/// \return
///
char ListeElem_hasAnAnimal(ListeElem* This);
///
/// \brief ListeElem_hasDirt Renvoie 0 si pas de terre dans la liste 1 sinon
/// \param This Pointeur sur la liste
/// \return
///
char ListeElem_hasDirt(ListeElem* This);

///
/// \brief ListeElem_getAnimal Renvoie un pointeur sur un animal de la liste
/// \param This
/// \return
///
struct Element* ListeElem_getAnimal(ListeElem* This);
///
/// \brief ListeElem_getPont Renvoie un pointeur sur le pont de la liste
/// \param This
/// \return
///
struct Element* ListeElem_getPont(ListeElem* This);
///
/// \brief ListeElem_getDirt Renvoie un pointeur sur la terre de la liste
/// \param This
/// \return
///
struct Element* ListeElem_getDirt(ListeElem* This);
///
/// \brief ListeElem_getPecheur Renvoie un pointeur sur le pecheur de la liste
/// \param This
/// \return
///
struct Element* ListeElem_getPecheur(ListeElem* This);
///
/// \brief ListeElem_deleteElement Enleve un element de la liste et le supprime par la même occasion
/// \return
///
Bool ListeElem_deleteElement(ListeElem*, struct Element*);
///
/// \brief ListeElem_remove Enleve un element de la liste sans le supprimer
/// \return
///
Bool ListeElem_remove(ListeElem*, struct Element*);
void ListeElem_Print(ListeElem*);
///
/// \brief ListeElem_getNieme Renvoie le Nieme element de la liste
/// \param This
/// \param number
/// \return
///
struct Element *ListeElem_getNieme(ListeElem *This, uint16_t number);

#endif // LISTEELEM_H
