#ifndef GRILLE_H
#define GRILLE_H

#include "case.h"
#include "listecase.h"
#include "element.h"
//#include "elementpecheur.h"

#define NOMBRE_PECHEUR_MAX 6

struct Element;
struct ElementPecheur;

typedef struct Grille
{
    struct Case **tab;
	unsigned int Taille;
	unsigned int TailleMaxSousPont;
	unsigned int TourCourant;
	unsigned char listePredationInitialise;
	unsigned char nbPecheur;
	struct ElementPecheur** tabPecheur;
	void (*Free)(struct Grille *This);
	void (*Clear)(struct Grille *This);
	void (*Print)(struct Grille *This);
	struct Case*** (*getMatriceVoisins)(struct Grille*, unsigned int, unsigned int, unsigned int);
	void (*moveFromTo)(struct Grille*, struct Element*, unsigned int, unsigned int);
	void (*reinitPecheur)(struct Grille*, struct Element*);
	void (*faireTour)(struct Grille*, char isSDL);
	void (*detruirePont)(struct Grille*, struct Case*);
} Grille;


//Grille Grille_Create(int Taille);
Grille* New_Grille(int Taille, unsigned char nbPecheurs);
void Grille_Init(Grille *This, unsigned int Taille, unsigned char nbPecheurs);
void Grille_Clear(struct Grille *This);
void Grille_Free(struct Grille *This);
void Grille_Print(struct Grille *This);
struct Case*** Grille_getMatriceVoisins(struct Grille *This, unsigned int posX, unsigned int posY, unsigned int nbSauts);
void Grille_moveFromTo(struct Grille*, struct Element*, unsigned int, unsigned int);
void Grille_reinitPecheur(struct Grille *This, struct Element *elem);
void Grille_faireTour(Grille *This, char isSdl);
void Grille_detruirePont(Grille *This, struct Case* c);

#endif // GRILLE_H
