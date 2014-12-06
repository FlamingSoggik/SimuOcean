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

		int dernierRepas;
		int (*GetDernierRepas)(struct ElementAnimal*);
		void (*SetDernierRepas)(struct ElementAnimal* , int);

		int sasiete;
		int (*GetSasiete)(struct ElementAnimal*);
		void (*SetSasiete)(struct ElementAnimal* , int);

		int derniereReproduction;
		int (*GetDerniereReproduction)(struct ElementAnimal*);
		void (*SetDerniereReproduction)(struct ElementAnimal* , int);
} ElementAnimal;

//Constructeurs
ElementAnimal* New_ElementAnimal(void);
ElementAnimal ElementAnimalCreate(void);
ElementAnimal* New_ElementAnimal_v12(int v12);

//Initialisateur
void ElementAnimal_Init(ElementAnimal* This);

//Destructeurs
void ElementAnimal_Free(struct ElementAnimal *This);
void ElementAnimal_New_Free(struct ElementAnimal *This);

//Others
int ElementAnimal_getDernierRepas(struct ElementAnimal *This);
void ElementAnimal_setDernierRepas(struct ElementAnimal *This, int toset);
int ElementAnimal_getSasiete(struct ElementAnimal *This);
void ElementAnimal_setSasiete(struct ElementAnimal *This, int toset);
int ElementAnimal_getderniereReproduction(struct ElementAnimal *This);
void ElementAnimal_setderniereReproduction(struct ElementAnimal *This, int toset);


#ifdef __cplusplus
}
#endif

#endif // ELEMENTANIMAL_H
