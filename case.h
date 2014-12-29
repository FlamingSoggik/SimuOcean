#ifndef CASE_H
#define CASE_H

#include "listeelem.h"
#include "grille.h"

struct Grille;

typedef struct Case {
	struct Grille* g;
    unsigned int posX;
	unsigned int posY;
    struct ListeElem *liste;
	void(*Free)(struct Case*);
	void(*Clear)(struct Case*);
	void (*Print)(struct Case *This);
}Case;

struct Case Case_Create(struct Grille * g, unsigned int posX, unsigned int posY);
void Case_Free(Case *This);
void Case_Clear(Case *This);
void Case_Print(Case *This);

#endif // CASE_H
