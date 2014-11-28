#ifndef ELEMENTANIMAL_H
#define ELEMENTANIMAL_H

#include "element.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ElementAnimal
{
		int id;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);

		int (*Getvaut12)(struct ElementAnimal*);
		void (*Setvaut12)(struct ElementAnimal* , int);
		int vaut12;
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
int ElementAnimal_getvaut12(struct ElementAnimal *This);
void ElementAnimal_setvaut12(struct ElementAnimal *This, int toset);


#ifdef __cplusplus
}
#endif

#endif // ELEMENTANIMAL_H
