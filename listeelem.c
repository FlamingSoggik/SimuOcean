#include "listeelem.h"
#include "elementanimal.h"
#include <stdlib.h>
#include <stdio.h>


void ListeElem_Init(ListeElem* This){
	This->taille=0;
	This->Top=NULL;
	This->Push=ListeElem_Push;
	This->Pop=ListeElem_Pop;
	This->Clear=ListeElem_Clear;
	This->Taille=ListeElem_Taille;
	This->HasAPont=ListeElem_hasAPont;
	This->HasDirt=ListeElem_hasDirt;
	This->HasAPecheur=ListeElem_hasAPecheur;
	This->HasAnAnimal=ListeElem_hasAnAnimal;
	This->getAnimal=ListeElem_getAnimal;
	This->getPont=ListeElem_getPont;
	This->getDirt=ListeElem_getDirt;
	This->getPecheur=ListeElem_getPecheur;
	This->remove=ListeElem_remove;
	This->deleteElement=ListeElem_deleteElement;
	This->Print=ListeElem_Print;
	This->Vider=ListeElem_Vider;
	This->getNieme=ListeElem_getNieme;
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
	MaillonListeElem *tmp;
	while(This->Top != NULL){
		tmp=This->Top;
		This->Top=tmp->next;
		tmp->e->Free(tmp->e);
		free(tmp);
	}
	This->taille = 0;
}

int ListeElem_Push(ListeElem* This, Element *e){
	if (e == NULL){
		return ERROR_ELEMENT_PASSED_NULL;
	}
	if(e->type == VOID){
		return ERROR_BAD_TYPE_ELEMENT;
	}
	if (e->type == PONT && This->HasAPont(This)){
		return ERROR_ONE_PONT_MAX;
	}
	if (e->type == TERRE && This->HasDirt(This)){
		return ERROR_ONE_TERRE_MAX;
	}
	MaillonListeElem *il = malloc(sizeof(MaillonListeElem));
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
	MaillonListeElem *tmp = This->Top->next;
	Element *e = This->Top->e;
	free(This->Top);
	This->Top=tmp;
	--This->taille;
	return e;
}

unsigned int ListeElem_Taille(ListeElem* This){
	return This->taille;
}

char ListeElem_hasAPecheur(ListeElem* This){
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == PECHEUR)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}

char ListeElem_hasAPont(ListeElem* This){
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == PONT)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}

char ListeElem_hasDirt(ListeElem* This){
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == TERRE)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}

char ListeElem_hasAnAnimal(ListeElem* This){
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type != PECHEUR && tmp->e->type != PONT && tmp->e->type != POLLUTION && tmp->e->type != TERRE)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}

//Renvoie un pointeur sur un animal et le garde dans la liste
Element* ListeElem_getAnimal(ListeElem *This)
{
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type != PECHEUR && tmp->e->type != PONT && tmp->e->type != POLLUTION && tmp->e->type != TERRE)
			return tmp->e;
		tmp=tmp->next;
	}
	return NULL;
}

//Renvoie un pointeur sur un pont et le garde dans la liste
Element *ListeElem_getPont(ListeElem *This)
{
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == PONT)
			return tmp->e;
		tmp=tmp->next;
	}
	return NULL;
}

//Renvoie un pointeur sur un Terre et le garde dans la liste
Element *ListeElem_getDirt(ListeElem *This)
{
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == TERRE)
			return tmp->e;
		tmp=tmp->next;
	}
	return NULL;
}

Bool ListeElem_deleteElement(ListeElem *This, Element *e)
{
	MaillonListeElem *tmp = This->Top;
	MaillonListeElem *prec = NULL;
	while(tmp != NULL){
		if (tmp->e == e){
			e->Free(e);
			if (prec == NULL){
				This->Top=tmp->next;
			}
			else {
				prec->next=tmp->next;
			}
			--This->taille;
			free(tmp);
			return True;
		}
		prec=tmp;
		tmp=tmp->next;
	}
	return False;
}

Bool ListeElem_remove(ListeElem *This, Element *e)
{
	MaillonListeElem *tmp = This->Top;
	MaillonListeElem *prec = NULL;
	while(tmp != NULL){
		if (tmp->e == e){
			if (prec == NULL){
				This->Top=tmp->next;
			}
			else {
				prec->next=tmp->next;
			}
			--This->taille;
			free(tmp);
			return True;
		}
		prec=tmp;
		tmp=tmp->next;
	}
	return False;
}

void ListeElem_Print(ListeElem * This)
{
	printf("Taille liste : %d --> ", This->taille);
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		printf("%d ", tmp->e->type);
		tmp=tmp->next;
	}
	printf("\n");
}


Element *ListeElem_getPecheur(ListeElem *This)
{
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == PECHEUR)
			return tmp->e;
		tmp=tmp->next;
	}
	return NULL;
}

void ListeElem_Vider(ListeElem *This){
	MaillonListeElem *tmp;
	while(This->Top != NULL){
		tmp=This->Top;
		This->Top=tmp->next;
		free(tmp);
	}
	This->taille = 0;
}

Element *ListeElem_getNieme(ListeElem *This, unsigned int number)
{
	if (number > This->taille-1){
		return NULL;
	}
	MaillonListeElem *tmp = This->Top;
	while(number != 0){
		tmp=tmp->next;
		--number;
	}
	return tmp->e;
}
