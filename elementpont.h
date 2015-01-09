#ifndef ELEMENTPECHEUR_H
#define ELEMENTPECHEUR_H

#include "element.h"
#include "Bool.h"
#include "listetype.h"

#define ERR_TYPE_NOT_ANIMAL -1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ElementPont
{
		struct Case* caseParent;
		Type type;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);
} ElementPont;

//Constructeurs
ElementPont* New_ElementPecheur(Case *c);


//Initialisateur
char ElementPecheur_Init(Case *c, ElementPont* This);

//Destructeurs

//Others


#ifdef __cplusplus
}
#endif

#endif // ELEMENTPONT_H
