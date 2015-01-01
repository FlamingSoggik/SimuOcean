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
	This->HasAPecheur=ListeElem_hasAPecheur;
	This->HasAnAnimal=ListeElem_hasAnAnimal;
	This->getAnimal=ListeElem_getAnimal;
	This->getPont=ListeElem_getPont;
	This->remove=ListeElem_remove;
	This->deleteElement=ListeElem_deleteElement;
	This->Print=ListeElem_Print;
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

int ListeElem_Taille(ListeElem* This){
	return This->taille;
}

//Cas non testé : la liste contient un pecheur
char ListeElem_hasAPecheur(ListeElem* This){
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == PECHEUR)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}

//Cas non testé : pont dans la liste
char ListeElem_hasAPont(ListeElem* This){
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type == PONT)
			return 1;
		tmp=tmp->next;
	}
	return 0;
}

char ListeElem_hasAnAnimal(ListeElem* This){
	MaillonListeElem *tmp = This->Top;
	while(tmp != NULL){
		if (tmp->e->type != PECHEUR && tmp->e->type != PONT && tmp->e->type != POLLUTION)
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
		if (tmp->e->type != PECHEUR && tmp->e->type != PONT)
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

Bool ListeElem_deleteElement(ListeElem *This, Element *e)
{
	MaillonListeElem *tmp = This->Top;
	MaillonListeElem *prec = NULL;
	while(tmp != NULL){
		if (tmp->e == e){
			e->Free(e);
			if (prec == NULL){
				This->Top=tmp->next;
				--This->taille;
				free(tmp);
				return True;
			}
			else {
				prec->next=tmp->next;
				--This->taille;
				free(tmp);
				return True;
			}
		}
		prec=tmp;
		tmp=tmp->next;
	}
	return False;
}

Bool ListeElem_remove(ListeElem *This, Element *e)
{
	{
		MaillonListeElem *tmp = This->Top;
		MaillonListeElem *prec = NULL;
		while(tmp != NULL){
			if (tmp->e == e){
				e->Free(e);
				if (prec == NULL){
					This->Top=tmp->next;
					--This->taille;
					return True;
				}
				else {
					prec->next=tmp->next;
					--This->taille;
					return True;
				}
			}
			prec=tmp;
			tmp=tmp->next;
		}
		return False;
	}
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
