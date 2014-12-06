#include<stdlib.h>
#include<stdio.h>

#include "elementanimal.h"

ElementAnimal* New_ElementAnimal(){
	ElementAnimal* This = malloc(sizeof(ElementAnimal));
	if (!This) return NULL;
	ElementAnimal_Init(This);
	This->Free = (void*)Element_New_Free;
	return This;
}

ElementAnimal ElementAnimalCreate(){
	ElementAnimal This;
	ElementAnimal_Init(&This);
	This.Free = (void*)Element_Free;
	return This;
}

ElementAnimal* New_ElementAnimal_v12(int v12)
{
	   ElementAnimal *This = malloc(sizeof(ElementAnimal));
	   if(!This) return NULL;
	   ElementAnimal_Init(This);
	   This->Free = (void*)Element_New_Free;
	   This->dernierRepas = v12;
	   return This;
}

void ElementAnimal_Init(ElementAnimal* This){
	This->dernierRepas = 0;
	This->GetDernierRepas = ElementAnimal_getDernierRepas;
	This->SetDernierRepas = ElementAnimal_setDernierRepas;
	This->sasiete = 0;
	This->GetSasiete = ElementAnimal_getSasiete;
	This->SetSasiete = ElementAnimal_setSasiete;
	This->derniereReproduction = 0;
	This->GetDerniereReproduction = ElementAnimal_getderniereReproduction;
	This->SetDerniereReproduction = ElementAnimal_setderniereReproduction;
	This->Clear = (void*)Element_Clear;
}

int ElementAnimal_getDernierRepas(struct ElementAnimal *This){
	return This->dernierRepas;
}

void ElementAnimal_setDernierRepas(struct ElementAnimal *This, int toset){
	This->dernierRepas=toset;
}

void ElementAnimal_New_Free(struct ElementAnimal *This){
	if(This) Element_Clear((Element*)This);
	free(This);
	puts("Destruction de l'Animal dynamique.\n");
}

void ElementAnimal_Free(struct ElementAnimal *This){
	Element_Clear((Element*)This);
	free(This);
	puts("Destruction de l'Animal statique.\n");
}

int ElementAnimal_getSasiete(struct ElementAnimal *This){
	return This->sasiete;
}

void ElementAnimal_setSasiete(struct ElementAnimal *This, int toset){
	This->sasiete=toset;
}

int ElementAnimal_getderniereReproduction(struct ElementAnimal *This){
	return This->derniereReproduction;
}

void ElementAnimal_setderniereReproduction(struct ElementAnimal *This, int toset){
	This->derniereReproduction=toset;
}

