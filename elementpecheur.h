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

/*************************** Partie Héritée de Element ***************************/
		struct Case* caseParent;
		Type type;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);


/*********************************************************************************/

/************************* Partie propre à ElementPecheur ************************/
		///
		/// \brief sac Alias besace : masse de poisson disponible pour la consruction du pont
		///
		unsigned int sac;
		unsigned int longueurCanne;
		unsigned int tailleFilet;
		unsigned int distanceDeplacement;
		struct ListeType* listeDePeche;
		unsigned int PositionInitialeX;
		unsigned int PositionInitialeY;
		char estSelectionne;
		void (*pecheParCanne)(struct ElementPecheur*, char*);
		void (*pecheParFilet)(struct ElementPecheur*, char*);
		Bool (*deplacement)(struct ElementPecheur*, char);
		Bool (*construirePont)(struct ElementPecheur*, char);
		void (*mourir)(struct ElementPecheur*); // --> fait
		void (*lancerpoisson)(struct ElementPecheur*);
		void (*reinitSac)(struct ElementPecheur*);
		Bool (*peutPecher)(struct ElementPecheur*, Type);


/*********************************************************************************/
} ElementPecheur;

//Constructeurs
///
/// \brief New_ElementPecheur Créé un ElementPecheur de manière dynamique
/// \param c Case dans laquelle se trouve le pecheur
/// \return Pointeur vers l'ElementPEcheur nouvellement créé
///
ElementPecheur* New_ElementPecheur(Case *c);


//Initialisateur

///
/// \brief ElementPecheur_Init Initialise l'ElementPecheur avec les pointeur sur fonction et ls attributs
/// \param c Case dans laquelle se trouve l'ElementPecheur
/// \param This Pointeur sur l'ElementPecheur
/// \return Code d'erreur
///
char ElementPecheur_Init(Case *c, ElementPecheur* This);

//Destructeurs

//Others
void ElementPecheur_pecheParCanne(ElementPecheur* This, char *buffer);
void ElementPecheur_pecheParFilet(ElementPecheur* This, char *buffer);
Bool ElementPecheur_deplacement(ElementPecheur* This, char direction);
Bool ElementPecheur_construirePont(ElementPecheur* This, char direction);

///
/// \brief ElementPecheur_mourir Fait réapparaitre l'ElementPecheur à sa position initiale
/// \param This Pointeur sur l'ElementPecheur à faire respawn
///
void ElementPecheur_mourir(ElementPecheur* This);
void ElementPecheur_lancerpoisson(ElementPecheur* This); // Non implementé, implémentation prévue pour le mode multijoueur
Bool ElementPecheur_peutPecher(ElementPecheur* This, Type t);
void ElementPecheur_reinitSac(ElementPecheur* This);

#ifdef __cplusplus
}
#endif

#endif // ELEMENTPECHEUR_H
