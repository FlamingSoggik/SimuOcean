#include "case.h"
#include <stdio.h>


Case Case_Create()
{
	Case This;
	This.Free=Case_Free;
	This.Print=Case_Print;
	This.liste = New_ListeElem();
	return This;
}

void Case_Free(Case *This){
	This->Clear(This);
}

void Case_Clear(Case *This){
	This->liste->Free();
}

void Case_Print(Case *This){
	printf("Rien à afficher pour le moment\n");
}
