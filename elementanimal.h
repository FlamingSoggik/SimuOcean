#ifndef ELEMENTANIMAL_H
#define ELEMENTANIMAL_H

#include "element.h"
#include "Bool.h"
#include "listetype.h"

#define ERR_TYPE_NOT_ANIMAL -1
#ifdef __cplusplus
extern "C" {
#endif

typedef struct ElementAnimal_Constantes{
		uint16_t dureeSurvie;
		uint16_t taille;
		uint16_t tailleDuBide;
		uint16_t sautMax;
		int16_t metabolisme;
		int16_t gestation;
		int16_t frequenceReproduction;
		struct ListeType* listePredation;
}ElementAnimal_Constantes;

///
/// \brief C_Vide Constante des elements vides
///
extern ElementAnimal_Constantes C_Vide;
///
/// \brief C_Plancton Constantes du Plancton
///
extern ElementAnimal_Constantes C_Plancton;
///
/// \brief C_Corail Constantes du Corail
///
extern ElementAnimal_Constantes C_Corail;
///
/// \brief C_Bar Constantes du bar
///
extern ElementAnimal_Constantes C_Bar;
///
/// \brief C_Thon Constantes du Thon
///
extern ElementAnimal_Constantes C_Thon;
///
/// \brief C_Pyranha Constantes du Pyranha
///
extern ElementAnimal_Constantes C_Pyranha;
///
/// \brief C_Requin Constantes du Requin
///
extern ElementAnimal_Constantes C_Requin;
///
/// \brief C_Orque Constantes de l'Orque
///
extern ElementAnimal_Constantes C_Orque;
///
/// \brief C_Baleine Constantes de la Baleine
///
extern ElementAnimal_Constantes C_Baleine;

typedef struct ElementAnimal
{
/*************************** Partie Héritée de Element ***************************/
		///
		/// \brief caseParent Pointeur vers la case dans laquelle on est
		///
        struct Case* caseParent;
		///
		/// \brief type Type de l'animal (bar, plancton ...)
		///
        Type type;
		///
		/// \brief Pointeur sur la fonction de liberation
		///
		void (*Free)(struct Element *This);
		///
		/// \brief Pointeur sur la fonction de nettoyage
		///
		void (*Clear)(struct Element *This);

/*********************************************************************************/


/************************* Partie propre à ElementAnimal *************************/
		///
		/// \brief dernierRepas Numero du tour du dernier repas de l'animal
		///
		uint16_t dernierRepas;

		///
		/// \brief Pointeur sur fonction getteur de dernierRepas
		///
		uint16_t (*GetDernierRepas)(struct ElementAnimal*);
		///
		/// \brief Pointeur sur fonction setteur de dernierRepas
		///
		void (*SetDernierRepas)(struct ElementAnimal* , uint16_t);

		///
		/// \brief sasiete Sasiete de l'animal
		///
		int16_t sasiete;
		int16_t (*GetSasiete)(struct ElementAnimal*);
		void (*SetSasiete)(struct ElementAnimal* , int16_t);

		///
		/// \brief derniereReproduction Numero du tour de la dernière reproduction de l'animal
		///
		uint16_t derniereReproduction;
		uint16_t (*GetDerniereReproduction)(struct ElementAnimal*);
		void (*SetDerniereReproduction)(struct ElementAnimal* , uint16_t);

		///
		/// \brief constantes Pointeur vers structure constante correspondant au type de l'ElementAnimal actuel
		///
		ElementAnimal_Constantes* constantes;


        void (*tour)(struct ElementAnimal*);
		Bool (*survie)(struct ElementAnimal *);
		Bool (*peutManger)(struct ElementAnimal*, Type t);
		void (*predation)(struct ElementAnimal*);
		void (*deplacement)(struct ElementAnimal*);
		void (*reproduction)(struct ElementAnimal*);

		///
		/// \brief hasAlreadyPlayed Indique si l'animal à déjà "joué" ce tour
		///
		char hasAlreadyPlayed;
		void (*aFaitSonTour)(struct ElementAnimal*);
		void (*finDuTour)(struct ElementAnimal*);
		Bool (*doitJouerCeTour)(struct ElementAnimal*);

/*********************************************************************************/

} ElementAnimal;

//Constructeurs
///
/// \brief New_ElementAnimal Créé un ElementAnimal de manière dynamique
/// \param c Case dans laquelle l'animal sera placé
/// \param t Type de l'animal
/// \return Pointeur sur l'ElementAnimal nouvellement créé
///
ElementAnimal* New_ElementAnimal(Case *c, Type t);
//ElementAnimal ElementAnimalCreate(Type t);

//ElementAnimal* New_ElementAnimal_v12(int16_t v12);

//Initialisateur
char ElementAnimal_Init(Case *c, ElementAnimal* This, Type t);

//Destructeurs

//Others
uint16_t ElementAnimal_getDernierRepas(struct ElementAnimal *This);
void ElementAnimal_setDernierRepas(struct ElementAnimal *This, uint16_t toset);
int16_t ElementAnimal_getSasiete(struct ElementAnimal *This);
void ElementAnimal_setSasiete(struct ElementAnimal *This, int16_t toset);
uint16_t ElementAnimal_getderniereReproduction(struct ElementAnimal *This);
void ElementAnimal_setderniereReproduction(struct ElementAnimal *This, uint16_t toset);

Bool ElementAnimal_survie(ElementAnimal *This);
void ElementAnimal_tour(ElementAnimal *This);
void ElementAnimal_predation(ElementAnimal *This);
void ElementAnimal_deplacement(ElementAnimal *This);
void ElementAnimal_reproduction(ElementAnimal *This);
Bool ElementAnimal_peutManger(ElementAnimal* This, Type t);
void ElementAnimal_aFaitSonTour(ElementAnimal* This);
void ElementAnimal_finDuTour(ElementAnimal *This);
Bool ElementAnimal_doitJouerCeTour(ElementAnimal *This);

///
/// \brief defineConstant definis les constantes des différents animaux
///
void defineConstant();

///
/// \brief remplirListePredation Remplis la liste de predation des différents animaux
/// \param This Pointeur vers la grille
///
void remplirListePredation(Grille *This);

///
/// \brief viderListePredationVide la liste de predation des animaux
/// \param This
///
void viderListePredation(Grille *This);

#ifdef __cplusplus
}
#endif

#endif // ELEMENTANIMAL_H
