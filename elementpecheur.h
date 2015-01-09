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
		struct ListeType* listeDePeche;
		void (*pecheParCanne)(struct ElementPecheur*);
		void (*pecheParFilet)(struct ElementPecheur*);
		void (*deplacement)(struct ElementPecheur*);
		void (*construirePont)(struct ElementPecheur*);
		void (*mourir)(struct ElementPecheur*);
		void (*lancerpoisson)(struct ElementPecheur*);
		Bool (*peutPecher)(struct ElementPecheur*, Type);
} ElementPecheur;

//Constructeurs
ElementPecheur* New_ElementPecheur(Case *c);


//Initialisateur
char ElementPecheur_Init(Case *c, ElementPecheur* This);

//Destructeurs

//Others
void ElementPecheur_pecheParCanne(ElementPecheur* This);
void ElementPecheur_pecheParFilet(ElementPecheur* This);
void ElementPecheur_deplacement(ElementPecheur* This);
void ElementPecheur_construirePont(ElementPecheur* This);
void ElementPecheur_mourir(ElementPecheur* This);
void ElementPecheur_lancerpoisson(ElementPecheur* This);
Bool ElementPecheur_peutPecher(ElementPecheur* This, Type t);

#ifdef __cplusplus
}
#endif

#endif // ELEMENTPECHEUR_H
