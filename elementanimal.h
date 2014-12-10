#ifndef ELEMENTANIMAL_H
#define ELEMENTANIMAL_H

#include "element.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ElementAnimal
{
		Type id;
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

		unsigned int dureeSurvie;
		unsigned int taille;
		unsigned int tailleDuBide;
		unsigned int sautMax;
		int metabolisme;
		int gestation;
		int frequenceReproduction;



} ElementAnimal;

//Constructeurs
ElementAnimal* New_ElementAnimal();
ElementAnimal ElementAnimalCreate();

//ElementAnimal* New_ElementAnimal_v12(int v12);

//Initialisateur
void ElementAnimal_Init(ElementAnimal* This);
void ElementAnimal_setType(ElementAnimal *This, Type t);

//Destructeurs
void ElementAnimal_Free(struct ElementAnimal *This);
void ElementAnimal_New_Free(struct ElementAnimal *This);

//Others
unsigned int ElementAnimal_getDernierRepas(struct ElementAnimal *This);
void ElementAnimal_setDernierRepas(struct ElementAnimal *This, unsigned int toset);
int ElementAnimal_getSasiete(struct ElementAnimal *This);
void ElementAnimal_setSasiete(struct ElementAnimal *This, int toset);
unsigned int ElementAnimal_getderniereReproduction(struct ElementAnimal *This);
void ElementAnimal_setderniereReproduction(struct ElementAnimal *This, unsigned int toset);


#ifdef __cplusplus
}
#endif

#endif // ELEMENTANIMAL_H
