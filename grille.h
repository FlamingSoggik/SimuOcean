#include "case.h"
#include "listecase.h"

#ifndef GRILLE_H
#define GRILLE_H

typedef struct Grille
{
    struct Case **tab;
	void (*Free)(struct Grille *This);
	void (*Clear)(struct Grille *This);
	void (*Print)(struct Grille *This);
    struct ListeCase* (*getListVoisins)(struct Case*);
} Grille;


Grille Grille_Create();
void Grille_Init(Grille *This);
void Grille_Clear(struct Grille *This);
void Grille_Free(struct Grille *This);
void Grille_Print(struct Grille *This);
struct ListeCase* Grille_getListVoisins(struct Case *c);



#endif // GRILLE_H
