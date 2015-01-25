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
	///
	/// \brief tab Tableau de Cases
	///
    struct Case **tab;
	///
	/// \brief Taille du tableau de Case
	///
	unsigned int Taille;
	///
	/// \brief TailleMaxSousPont Taille maximal des animaux sous un pont
	///
	unsigned int TailleMaxSousPont;
	///
	/// \brief TourCourant Numero du tour actuel
	///
	unsigned int TourCourant;
	///
	/// \brief listePredationInitialise Permet de dire si les liste de predations sont initialisées ou non
	///
	unsigned char listePredationInitialise;
	///
	/// \brief nbPecheur Nombre de pecheurs sur le plateau de jeu
	///
	unsigned char nbPecheur;
	///
	/// \brief tabPecheur Tableau contenant les pecheurs à faire jouer
	///
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
///
/// \brief New_Grille Créé la grille et l'initialise
/// \param Taille Taille de la grille
/// \param nbPecheurs Nombre de pecheurs sur la grille
/// \return Pointeur sur la grille nouvellement créé
///
Grille* New_Grille(int Taille, unsigned char nbPecheurs);

///
/// \brief Grille_Init Initialise la grille
/// \param This Pointeur sur la grille à initialiser
/// \param Taille Taille de la grille à initialiser
/// \param nbPecheurs Nombre de pecheurs sur la grille
///
void Grille_Init(Grille *This, unsigned int Taille, unsigned char nbPecheurs);
///
/// \brief Grille_Clear Nettoie la grille (free ous les éléments internes
/// \param This
///
void Grille_Clear(struct Grille *This);
void Grille_Free(struct Grille *This);
///
/// \brief Grille_Print Affiche la grille (utile en mode terminal
/// \param This Pointeur sur la Grille
///
void Grille_Print(struct Grille *This);
///
/// \brief Grille_getMatriceVoisins Renvoie la matrice des voisins
/// \param This Pointeur sur la grille
/// \param posX Position X à partir de laquelle on demande les voisins
/// \param posY Position Y à partir de laquelle on demande les voisins
/// \param nbSauts nombre de voisins de chaque coté de la ligne annoncée par posx, posy
/// \return
///
struct Case*** Grille_getMatriceVoisins(struct Grille *This, unsigned int posX, unsigned int posY, unsigned int nbSauts);
///
/// \brief Grille_moveFromTo Deplace un element de la grille d'une case à une autre
///
void Grille_moveFromTo(struct Grille*, struct Element*, unsigned int, unsigned int);
///
/// \brief Grille_reinitPecheur Fait respawn le pecheur
/// \param This Pointeur sur la grille
/// \param elem ElementPecheur à réinitialiser
///
void Grille_reinitPecheur(struct Grille *This, struct Element *elem);
///
/// \brief Grille_faireTour Fait faire un tour à l'Environnement
/// \param This Pointeur sur la Grille
/// \param isSdl Différencie un appel depuis la sdl d'un appel sans interface graphique de lancée
///
void Grille_faireTour(Grille *This, char isSdl);
///
/// \brief Grille_detruirePont Detruire un pont à une case donnée
/// \param This Pointeur sur la grille
/// \param Pointeur sur la case où l'on veut supprimer le pont
///
void Grille_detruirePont(Grille *This, struct Case* c);

#endif // GRILLE_H
