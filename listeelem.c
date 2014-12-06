#include "listeelem.h"
#include <stdlib.h>

void ListeElem_Init(ListeElem* This){
	This->taille=0;
	This->Clear=ListeElem_Clear;
	This->Taille=ListeElem_Taille;
	This->HasAPont=ListeElem_hasAPont;
	This->HasAPecheur=ListeElem_hasAPecheur;
	This->HasAnAnimal=ListeElem_hasAnAnimal;
}

ListeElem* New_ListeElem(){
	ListeElem* This = malloc(sizeof(ListeElem));
	if (!This) return NULL;
	ListeElem_Init(This);
	This->Free=ListeElem_New_Free;
	return This;
}

void ListeElem_New_Free(ListeElem *This){
	This->Clear(This);
	free(This);
}

void ListeElem_Clear(ListeElem *This){
	ItemListeElem *tmp;
	while(This->Top)
	{
		tmp = This->Top->next;
		free(This->Top);
		This->Top = tmp;
	}
	This->taille = 0;
}

int ListeElem_Push(ListeElem* This, Element *e){
	if(e->type == VOID)
		return ERROR_BAD_TYPE_ELEMENT;
	if (e->type == PONT && This->HasAPont(This)){
		return ERROR_ONE_PONT_MAX;
	}
	ItemListeElem *il = malloc(sizeof(ItemListeElem));
	if (!il) return ERROR_MALLOC_ITEM;
	il->next=This->Top;
	il->e=e;
	This->Top=il;
	++This->taille;
	return 0;
}

Element* ListeElem_Pop(ListeElem* This){
	if (This->taille == 0)
		return NULL;
	ItemListeElem *tmp = This->Top->next;
	Element *e = This->Top->e;
	free(This->Top);
	This->Top=tmp;
	This->taille--;
	return e;
}

int ListeElem_Taille(ListeElem* This){
	return This->taille;
}


char ListeElem_hasAPecheur(ListeElem* This){
	ItemListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == PECHEUR)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}

char ListeElem_hasAPont(ListeElem* This){
	ItemListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == PONT)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}

char ListeElem_hasAnAnimal(ListeElem* This){
	ItemListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type != PECHEUR && tmp->e->type != PONT)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}
