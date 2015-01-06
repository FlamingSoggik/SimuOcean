#include "elementpecheur.h"

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "Bool.h"

#include "listetype.h"
#include <time.h>

#define max(a,b) (a>=b?a:b)

ElementPecheur* New_ElementPecheur(Case *c, Type t){
	ElementPecheur* This = malloc(sizeof(ElementPecheur));
	if (!This) return NULL;
	if (ElementPecheur_Init(c, This, t) < 0){
		free(This);
		return NULL;
	}
	This->Free = Element_New_Free;
	return This;
}

char ElementPecheur_Init(Case *c, ElementPecheur* This, Type t){
	if (c == NULL){
		puts("Erreur creation animal case parent vide");
	}
	This->caseParent=c;
	This->type=t;
	This->Clear = Element_Clear;
	This->sac = 0;
	return 0;
}
