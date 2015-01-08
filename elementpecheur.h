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
		void (*pecheParCanne)(struct ElementPecheur*);
		void (*pecheParFilet)(struct ElementPecheur*);
		void (*deplacement)(struct ElementPecheur*);
		void (*construirePont)(struct ElementPecheur*);
		void (*mourir)(struct ElementPecheur*);
		void (*lancerpoisson)(struct ElementPecheur*);

} ElementPecheur;

//Constructeurs
ElementPecheur* New_ElementPecheur(Case *c);


//Initialisateur
char ElementPecheur_Init(Case *c, ElementPecheur* This);

//Destructeurs

//Others


#ifdef __cplusplus
}
#endif

#endif // ELEMENTPECHEUR_H
