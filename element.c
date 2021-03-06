#include "element.h"
#include <stdio.h>
#include <stdlib.h>

void Element_Init(Case *c, Element *This){
    This->caseParent=c;
	This->Clear = Element_Clear;
	This->type=VOID;
}

void Element_Free(Element *This){
	This->Clear(This);
	puts("Destruction de Element statique");
}

void Element_Clear(Element *This){
	//Ne fais rien mais fera quelque chose si on a dans notre classe des éléments malloc
    This=This;
}

Element* New_Element(Case *c){
	Element *This = malloc(sizeof(Element));
	if(!This) return NULL;
    Element_Init(c, This);
	This->Free = Element_New_Free;
	return This;
}

void Element_New_Free(Element* This){
	if(This) This->Clear(This);
	free(This);
}
