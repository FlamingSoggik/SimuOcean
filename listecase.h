#ifndef LISTECASE_H
#define LISTECASE_H

#include "case.h"

#define ERROR_MALLOC_ITEM -1
#define ERROR_LISTE_VIDE -2
#define ERROR_BAD_TYPE_CASE -3
#define ERROR_ONE_PONT_MAX -4
#define ERROR_ONE_TERRE_MAX -5


typedef struct MaillonListeCase{
        struct Case* c;
        struct MaillonListeCase* next;
}MaillonListeCase;

typedef struct ListeCase {
	unsigned int taille;
    struct MaillonListeCase *Top;
    void(*Free)();
    int(*Push)(struct ListeCase*, struct Case*);
	struct Case*(*Pop)(struct ListeCase*);
    void(*Clear)(struct ListeCase*);
    int(*Taille)(struct ListeCase*);
	struct Case*(*getNieme)(struct ListeCase*, unsigned int);
}ListeCase;

int ListeCase_Taille(ListeCase* This);
void ListeCase_Clear(ListeCase *This);
void ListeCase_New_Free(ListeCase *This);
///
/// \brief ListeCase_Push Ajoute une case à la liste
/// \param This Pointeur sur la liste de case
/// \param c Pointeur sur la Case à ajouter à la liste
/// \return
///
int ListeCase_Push(ListeCase* This, struct Case *c);
///
/// \brief ListeCase_getNieme renvoie le N ieme element de la liste
/// \param This Pointeur sur la liste de case
/// \param number Numero de l'élément à retourner
/// \return
///
struct Case* ListeCase_getNieme(ListeCase* This, unsigned int number);
///
/// \brief ListeCase_Pop Renvoie le premier element de la liste
/// \param This Pointeur sur la liste
/// \return Pointeur sur la premiere case de la liste
///
struct Case* ListeCase_Pop(ListeCase* This);
ListeCase* New_ListeCase();
void ListeCase_Init(ListeCase* This);

#endif // LISTECASE_H
