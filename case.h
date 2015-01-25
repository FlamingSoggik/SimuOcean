#ifndef CASE_H
#define CASE_H

#include "listeelem.h"
#include "grille.h"

struct Grille;


typedef struct Case {
	struct Grille* g;
    unsigned int posX;
	unsigned int posY;
    struct ListeElem *liste;
	void(*Free)(struct Case*);
	void(*Clear)(struct Case*);
	void (*Print)(struct Case *This);
}Case;

///
/// \brief Case_Create Créé une Case de manière statique et la retourne
/// \param g Pointeur vers la grille parente
/// \param posX Position x dans la grille parente
/// \param posY Position y dans la grille parente
/// \return Case Initialisée
///
struct Case Case_Create(struct Grille * g, unsigned int posX, unsigned int posY);

///
/// \brief Case_Free Libère la case pointée par This en la nettoyant. Pas de free réellement appelé puisque la création de case se fait uniquement de manière statique
/// \param This Pointeur sur la case à libérer
///
void Case_Free(Case *This);

///
/// \brief Case_Clear Nettoie une Case (libère tous les éléments de sa ListeElem)
/// \param This Pointeur sur la Case à nettoyer
///
void Case_Clear(Case *This);

///
/// \brief Case_Print [DEBUG]Affiche la liste d'élément contenue par la Case pointée par This
/// \param This Pointeur sur la Case à afficher
///
void Case_Print(Case *This);

#endif // CASE_H
