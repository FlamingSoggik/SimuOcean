#ifndef ELEMENT_H
#define ELEMENT_H

#include "case.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Type {
	//0		 1		  2		 3	   4	   5		 6		  7		 8		 9		 10		 11		12
	VOID, PLANCTON, CORAIL, BAR, THON, POLLUTION, PYRANHA, REQUIN, ORQUE, BALEINE, PECHEUR, PONT, TERRE,
	TYPEMIN=0,
	TYPEMAX=TERRE
}Type;

typedef struct Element
{
        struct Case* caseParent;
        Type type;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);
} Element;

//Constructeurs
Element* New_Element(struct Case *c);

//Initialisateur
void Element_Init(struct Case *c, Element *This);

//Destructructeurs
void Element_New_Free(Element* This);

//Others
void Element_Clear(Element *This);

#ifdef __cplusplus
}
#endif

#endif // ELEMENT_H
