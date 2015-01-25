#ifndef ELEMENT_H
#define ELEMENT_H

#include "case.h"

/// Enumeration des différents types d'animaux
typedef enum Type {
	//0		 1		  2		 3	   4	   5		 6		  7		 8		 9		 10		 11		12
	VOID, PLANCTON, CORAIL, BAR, THON, POLLUTION, PYRANHA, REQUIN, ORQUE, BALEINE, PECHEUR, PONT, TERRE,
	TYPEMIN=0,
	TYPEMAX=TERRE
}Type;

/// Element est la structure de base dont les autres elements héritent (ElementPecheur, ElementPont et ElementTerre et ElementAnimal)
typedef struct Element
{
        struct Case* caseParent;
        Type type;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);
} Element;

//Constructeurs
///
/// \deprecated
/// \brief New_Element Créé un element de manière dynamique (avec malloc) son type est alors 0 (VOID) Cette fonction n'as pas à être appelée, la création d'élément se fait par les constructeurs des structures qui héritent de Element
/// \param c Pointeur sur la case parent
/// \return Pointeur sur l'élément nouvellement créé
///
Element* New_Element(struct Case *c);

//Initialisateur
///
/// \brief Element_Init Initialise l'élément (pointeurs sur fonction et type)
/// \param c Pointeur sur la case parent pour affectation au membre caseParent de la Classe Element
/// \param This Pointeur sur l'Element à initialiser
///
void Element_Init(struct Case *c, Element *This);

//Destructructeurs
///
/// \brief Element_New_Free Détruit les Elements dynamiques après les avoir nettoyer
/// \param This Pointeur sur l'élément à détruire
///
void Element_New_Free(Element* This);

//Others
///
/// \brief Element_Clear Nettoie l'Element, pour l'instant, cette fonction ne fait rien
/// \param This Pointeur sur l'Element à nettoyer
///
void Element_Clear(Element *This);

#endif // ELEMENT_H
