#include "case.h"
#include "listecase.h"

#ifndef GRILLE_H
#define GRILLE_H

typedef struct Grille
{
    struct Case **tab;
	unsigned int Taille;
	void (*Free)(struct Grille *This);
	void (*Clear)(struct Grille *This);
	void (*Print)(struct Grille *This);
	struct Case*** (*getMatriceVoisins)(struct Grille*, unsigned int, unsigned int, unsigned int);
} Grille;


Grille Grille_Create(int Taille);
void Grille_Init(Grille *This, int Taille);
void Grille_Clear(struct Grille *This);
void Grille_Free(struct Grille *This);
void Grille_Print(struct Grille *This);
struct Case*** Grille_getMatriceVoisins(struct Grille *This, unsigned int, unsigned int, unsigned int);

#endif // GRILLE_H
