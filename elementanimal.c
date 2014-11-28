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
	   This->vaut12 = v12;
	   return This;
}

void ElementAnimal_Init(ElementAnimal* This){
	This->vaut12 = 12;
	This->Getvaut12 = ElementAnimal_getvaut12;
	This->Setvaut12 = ElementAnimal_setvaut12;
	This->Clear = (void*)Element_Clear;
}

int ElementAnimal_getvaut12(struct ElementAnimal *This){
	return This->vaut12;
}

void ElementAnimal_setvaut12(struct ElementAnimal *This, int toset){
	This->vaut12=toset;
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
