#ifndef ELEMENTTERRE_H
#define ELEMENTTERRE_H

#include "element.h"
#include "Bool.h"
#include "listetype.h"

#define ERR_TYPE_NOT_ANIMAL -1

typedef struct ElementTerre
{
		struct Case* caseParent;
		Type type;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);
} ElementTerre;

//Constructeurs
ElementTerre* New_ElementTerre(Case *c);


//Initialisateur
char ElementTerre_Init(Case *c, ElementTerre* This);

//Destructeurs

//Others

#endif // ELEMENTTERRE_H
