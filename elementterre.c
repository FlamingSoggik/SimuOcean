#include "elementterre.h"

#include <stdlib.h>
#include <stdio.h>
#include "listetype.h"

#define max(a,b) (a>=b?a:b)

ElementTerre *New_ElementTerre(Case *c){
	ElementTerre* This = malloc(sizeof(ElementTerre));
	if (!This) return NULL;
	if (ElementTerre_Init(c, This) < 0){
		free(This);
		return NULL;
	}
	This->Free = Element_New_Free;
	return This;
}

char ElementTerre_Init(Case *c, ElementTerre* This){
	if (c == NULL){
		puts("Erreur creation animal case parent vide");
	}
	This->caseParent=c;
	This->type=TERRE;
	This->Clear = Element_Clear;
	return 0;
}
