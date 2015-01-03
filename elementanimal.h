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
		unsigned int dureeSurvie;
		unsigned int taille;
		unsigned int tailleDuBide;
		unsigned int sautMax;
		int metabolisme;
		int gestation;
		int frequenceReproduction;
		struct ListeType* listePredation;
}ElementAnimal_Constantes;

extern ElementAnimal_Constantes C_Plancton;
extern ElementAnimal_Constantes C_Corail;
extern ElementAnimal_Constantes C_Bar;
extern ElementAnimal_Constantes C_Thon;
extern ElementAnimal_Constantes C_Pyranha;
extern ElementAnimal_Constantes C_Requin;
extern ElementAnimal_Constantes C_Orque;
extern ElementAnimal_Constantes C_Baleine;

typedef struct ElementAnimal
{

        struct Case* caseParent;
        Type type;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);

		unsigned int dernierRepas;
		unsigned int (*GetDernierRepas)(struct ElementAnimal*);
		void (*SetDernierRepas)(struct ElementAnimal* , unsigned int);

		int sasiete;
		int (*GetSasiete)(struct ElementAnimal*);
		void (*SetSasiete)(struct ElementAnimal* , int);

        unsigned int derniereReproduction;
		unsigned int (*GetDerniereReproduction)(struct ElementAnimal*);
		void (*SetDerniereReproduction)(struct ElementAnimal* , unsigned int);

		ElementAnimal_Constantes* constantes;

        void (*tour)(struct ElementAnimal*);
        Bool (*survie)(struct ElementAnimal *, unsigned int);
		Bool (*peutManger)(struct ElementAnimal*, Type t);
		void (*predation)(struct ElementAnimal*);
		void (*deplacement)(struct ElementAnimal*);
		void (*reproduction)(struct ElementAnimal*);

} ElementAnimal;

//Constructeurs
ElementAnimal* New_ElementAnimal(Case *c, Type t);
//ElementAnimal ElementAnimalCreate(Type t);

//ElementAnimal* New_ElementAnimal_v12(int v12);

//Initialisateur
char ElementAnimal_Init(Case *c, ElementAnimal* This, Type t);

//Destructeurs

//Others
unsigned int ElementAnimal_getDernierRepas(struct ElementAnimal *This);
void ElementAnimal_setDernierRepas(struct ElementAnimal *This, unsigned int toset);
int ElementAnimal_getSasiete(struct ElementAnimal *This);
void ElementAnimal_setSasiete(struct ElementAnimal *This, int toset);
unsigned int ElementAnimal_getderniereReproduction(struct ElementAnimal *This);
void ElementAnimal_setderniereReproduction(struct ElementAnimal *This, unsigned int toset);

Bool ElementAnimal_survie(struct ElementAnimal *This, unsigned int tourCourrant);
void ElementAnimal_tour(struct ElementAnimal *This);
void ElementAnimal_predation(struct ElementAnimal *This);
void ElementAnimal_deplacement(ElementAnimal *This);
void ElementAnimal_reproduction(ElementAnimal *This);
Bool ElementAnimal_peutManger(struct ElementAnimal* This, Type t);

void defineConstant();
void remplirListePredation();
void viderListePredation();

#ifdef __cplusplus
}
#endif

#endif // ELEMENTANIMAL_H
