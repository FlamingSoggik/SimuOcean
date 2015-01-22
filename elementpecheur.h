#ifndef ELEMENTPECHEUR_H
#define ELEMENTPECHEUR_H

#include "element.h"
#include "Bool.h"
#include "listetype.h"

#define ERR_TYPE_NOT_ANIMAL -1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ElementPecheur
{
		struct Case* caseParent;
		Type type;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);

		unsigned int sac;
		unsigned int longueurCanne;
		unsigned int tailleFilet;
		unsigned int distanceDeplacement;
		struct ListeType* listeDePeche;
		unsigned int PositionInitialeX;
		unsigned int PositionInitialeY;
		void (*pecheParCanne)(struct ElementPecheur*); //--> fait
		void (*pecheParFilet)(struct ElementPecheur*); //--> fait
		Bool (*deplacement)(struct ElementPecheur*, char); //--> fait
		void (*construirePont)(struct ElementPecheur*, char); // --> fait
		void (*mourir)(struct ElementPecheur*); // --> fait
		void (*lancerpoisson)(struct ElementPecheur*);
		Bool (*peutPecher)(struct ElementPecheur*, Type);  //--> fait
} ElementPecheur;

//Constructeurs
ElementPecheur* New_ElementPecheur(Case *c);


//Initialisateur
char ElementPecheur_Init(Case *c, ElementPecheur* This);

//Destructeurs

//Others
void ElementPecheur_pecheParCanne(ElementPecheur* This);
void ElementPecheur_pecheParFilet(ElementPecheur* This);
Bool ElementPecheur_deplacement(ElementPecheur* This, char direction);
void ElementPecheur_construirePont(ElementPecheur* This, char direction);
void ElementPecheur_mourir(ElementPecheur* This);
void ElementPecheur_lancerpoisson(ElementPecheur* This);
Bool ElementPecheur_peutPecher(ElementPecheur* This, Type t);

#ifdef __cplusplus
}
#endif

#endif // ELEMENTPECHEUR_H
