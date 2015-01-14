#include "elementpont.h"

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "Bool.h"

#include "listetype.h"
#include <time.h>

#define max(a,b) (a>=b?a:b)

ElementPont* New_ElementPont(Case *c){
	ElementPont* This = malloc(sizeof(ElementPont));
	if (!This) return NULL;
	if (ElementPont_Init(c, This) < 0){
		free(This);
		return NULL;
	}
	This->Free = Element_New_Free;
	return This;
}

char ElementPont_Init(Case *c, ElementPont* This){
	if (c == NULL){
		puts("Erreur creation animal case parent vide");
	}
	This->caseParent=c;
	This->type=PONT;
	This->Clear = Element_Clear;
	return 0;
}
