#include <stdio.h>
#include "case.h"

Case Case_Create(Grille *g, unsigned int posX, unsigned int posY)
{
	Case This;
    This.g = g;
    This.posX=posX;
    This.posY=posY;
	This.liste = New_ListeElem();
	This.Free=Case_Free;
	This.Clear=Case_Clear;
	This.Print=Case_Print;
	return This;
}

void Case_Free(Case *This){
	This->Clear(This);
	printf("Suppression de Case statique\n");
}

void Case_Clear(Case *This){
	This->liste->Free(This->liste);
}

void Case_Print(Case *This){
	This->liste->Print(This->liste);
}

