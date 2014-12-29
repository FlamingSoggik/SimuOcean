#include "listetype.h"
#include <stdlib.h>

void ListeType_Init(ListeType* This){
	This->taille=0;
	This->Push=ListeType_Push;
	This->Pop=ListeType_Pop;
	This->Clear=ListeType_Clear;
	This->Taille=ListeType_Taille;
}

ListeType* New_ListeType(){
	ListeType* This = malloc(sizeof(ListeType));
	if (!This) return NULL;
	ListeType_Init(This);
	This->Free=ListeType_New_Free;
	return This;
}

void ListeType_New_Free(ListeType *This){
	This->Clear(This);
	free(This);
}

void ListeType_Clear(ListeType *This){
	MaillonListeType *tmp;
	while(This->Top)
	{
		tmp = This->Top->next;
		free(This->Top);
		--This->taille;
		This->Top = tmp;
	}
}

int ListeType_Push(ListeType* This, Type t){
	MaillonListeType *il = malloc(sizeof(MaillonListeType));
	if (!il) return ERROR_MALLOC_ITEM;
	il->next=This->Top;
	il->t=t;
	This->Top=il;
	++This->taille;
	return 0;
}

Type ListeType_Pop(ListeType* This){
	if (This->taille == 0)
		return VOID;
	MaillonListeType *tmp = This->Top->next;
	Type t = This->Top->t;
	free(This->Top);
	This->Top=tmp;
	--This->taille;
	return t;
}

int ListeType_Taille(ListeType* This){
	return This->taille;
}


Bool ListeType_Contain(ListeType * This, Type t)
{
	if (This->taille == 0)
		return False;
	MaillonListeType *tmp=This->Top;
	while(tmp != NULL)
	{
		if (tmp->t == t)
			return True;
		tmp=tmp->next;
	}
	return False;
}
