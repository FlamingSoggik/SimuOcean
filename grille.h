#ifndef GRILLE_H
#define GRILLE_H

#include "case.h"
#include "listecase.h"
#include "element.h"

struct Element;

typedef struct Grille
{
    struct Case **tab;
	unsigned int Taille;
	unsigned int TailleMaxSousPont;
	unsigned int TourCourant;
	unsigned char listePredationInitialise;
	void (*Free)(struct Grille *This);
	void (*Clear)(struct Grille *This);
	void (*Print)(struct Grille *This);
	struct Case*** (*getMatriceVoisins)(struct Grille*, unsigned int, unsigned int, unsigned int);
	void (*moveFromTo)(struct Grille*, struct Element*, unsigned int, unsigned int);
	void (*reinitPecheur)(struct Grille*, struct Element*);
	void (*faireTour)(struct Grille*);
} Grille;


//Grille Grille_Create(int Taille);
Grille* New_Grille(int Taille);
void Grille_Init(Grille *This, unsigned int Taille);
void Grille_Clear(struct Grille *This);
void Grille_Free(struct Grille *This);
void Grille_Print(struct Grille *This);
struct Case*** Grille_getMatriceVoisins(struct Grille *This, unsigned int posX, unsigned int posY, unsigned int nbSauts);
void Grille_moveFromTo(struct Grille*, struct Element*, unsigned int, unsigned int);
void Grille_reinitPecheur(struct Grille *This, struct Element *elem);
void Grille_faireTour(Grille *This);

#endif // GRILLE_H
