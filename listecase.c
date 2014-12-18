#include "listecase.h"
#include <stdlib.h>


void ListeCase_Init(ListeCase* This){
    This->taille=0;
    This->Clear=ListeCase_Clear;
    This->Taille=ListeCase_Taille;
}

ListeCase* New_ListeCase(){
    ListeCase* This = malloc(sizeof(ListeCase));
    if (!This) return NULL;
    ListeCase_Init(This);
    This->Free=ListeCase_New_Free;
    return This;
}

void ListeCase_New_Free(ListeCase *This){
    This->Clear(This);
    free(This);
}

void ListeCase_Clear(ListeCase *This){
    MaillonListeCase *tmp;
    while(This->Top)
    {
        tmp = This->Top->next;
        free(This->Top);
        This->Top = tmp;
    }
    This->taille = 0;
}

int ListeCase_Push(ListeCase* This, Case *c){
    MaillonListeCase *il = malloc(sizeof(MaillonListeCase));
    if (!il) return ERROR_MALLOC_ITEM;
    il->next=This->Top;
    il->c=c;
    This->Top=il;
    ++This->taille;
    return 0;
}

Case* ListeCase_Pop(ListeCase* This){
    if (This->taille == 0)
        return NULL;
    MaillonListeCase *tmp = This->Top->next;
    Case *c = This->Top->c;
    free(This->Top);
    This->Top=tmp;
    This->taille--;
    return c;
}

int ListeCase_Taille(ListeCase* This){
    return This->taille;
}
