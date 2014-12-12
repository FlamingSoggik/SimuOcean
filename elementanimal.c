#include<stdlib.h>
#include<stdio.h>

#include "elementanimal.h"
#include "math.h"

#define max(a,b) (a>=b?a:b)

ElementAnimal* New_ElementAnimal(Case *c, Type t){
	ElementAnimal* This = malloc(sizeof(ElementAnimal));
	if (!This) return NULL;
    if (ElementAnimal_Init(c, This, t) < 0){
        free(This);
        return NULL;
    }
	This->Free = (void*)Element_New_Free;
	return This;
}

//ElementAnimal ElementAnimalCreate(Type t){
//	ElementAnimal This;
//    if (ElementAnimal_Init(&This, t) < 0){
//        return;
//    }
//	This.Free = (void*)Element_Free;
//	return This;
//}

//ElementAnimal* New_ElementAnimal_v12(int v12)
//{
//	   ElementAnimal *This = malloc(sizeof(ElementAnimal));
//	   if(!This) return NULL;
//	   ElementAnimal_Init(This);
//	   This->Free = (void*)Element_New_Free;
//	   This->dernierRepas = v12;
//	   return This;
//}

char defineConstant(ElementAnimal* This, Type t)
{
    switch (t){
    case PLANCTON:
        This->dureeSurvie=1;
        This->taille=1;
        This->tailleDuBide=1;
        This->sautMax=1;
        This->metabolisme=1;
        This->gestation=1;
        This->frequenceReproduction=1;
        break;
    case CORAIL:
        This->dureeSurvie=1;
        This->taille=1;
        This->tailleDuBide=1;
        This->sautMax=1;
        This->metabolisme=1;
        This->gestation=1;
        This->frequenceReproduction=1;
        break;
    case BAR:
        This->dureeSurvie=1;
        This->taille=1;
        This->tailleDuBide=1;
        This->sautMax=1;
        This->metabolisme=1;
        This->gestation=1;
        This->frequenceReproduction=1;
        break;
    case THON:
        This->dureeSurvie=1;
        This->taille=1;
        This->tailleDuBide=1;
        This->sautMax=1;
        This->metabolisme=1;
        This->gestation=1;
        This->frequenceReproduction=1;
        break;
    case PYRANHA:
        This->dureeSurvie=1;
        This->taille=1;
        This->tailleDuBide=1;
        This->sautMax=1;
        This->metabolisme=1;
        This->gestation=1;
        This->frequenceReproduction=1;
        break;
    case REQUIN:
        This->dureeSurvie=1;
        This->taille=1;
        This->tailleDuBide=1;
        This->sautMax=1;
        This->metabolisme=1;
        This->gestation=1;
        This->frequenceReproduction=1;
        break;
    case ORQUE:
        This->dureeSurvie=1;
        This->taille=1;
        This->tailleDuBide=1;
        This->sautMax=1;
        This->metabolisme=1;
        This->gestation=1;
        This->frequenceReproduction=1;
        break;
    case BALEINE:
        This->dureeSurvie=1;
        This->taille=1;
        This->tailleDuBide=1;
        This->sautMax=1;
        This->metabolisme=1;
        This->gestation=1;
        This->frequenceReproduction=1;
        break;
    default :
        return ERR_TYPE_NOT_ANIMAL;
    }

    return 0;
}

char ElementAnimal_Init(Case *c, ElementAnimal* This, Type t){
    This->caseParent=c;
	This->dernierRepas = 0;
	This->GetDernierRepas = ElementAnimal_getDernierRepas;
	This->SetDernierRepas = ElementAnimal_setDernierRepas;
	This->sasiete = 0;
	This->GetSasiete = ElementAnimal_getSasiete;
	This->SetSasiete = ElementAnimal_setSasiete;
	This->derniereReproduction = 0;
	This->GetDerniereReproduction = ElementAnimal_getderniereReproduction;
	This->SetDerniereReproduction = ElementAnimal_setderniereReproduction;
    This->Clear = (void*)Element_Clear;
    This->survie=ElementAnimal_survie;
    This->tour=ElementAnimal_tour;
    if (defineConstant(This, t) < 0){
        return ERR_TYPE_NOT_ANIMAL;
    }
    return 0;
}

unsigned int ElementAnimal_getDernierRepas(struct ElementAnimal *This){
	return This->dernierRepas;
}

void ElementAnimal_setDernierRepas(struct ElementAnimal *This, unsigned int toset){
	This->dernierRepas=toset;
}

void ElementAnimal_New_Free(struct ElementAnimal *This){
	if(This) Element_Clear((Element*)This);
	free(This);
	puts("Destruction de l'Animal dynamique.\n");
}

void ElementAnimal_Free(struct ElementAnimal *This){
	Element_Clear((Element*)This);
	free(This);
	puts("Destruction de l'Animal statique.\n");
}

int ElementAnimal_getSasiete(struct ElementAnimal *This){
	return This->sasiete;
}

void ElementAnimal_setSasiete(struct ElementAnimal *This, int toset){
	This->sasiete=toset;
}

unsigned int ElementAnimal_getderniereReproduction(struct ElementAnimal *This){
	return This->derniereReproduction;
}

void ElementAnimal_setderniereReproduction(struct ElementAnimal *This, unsigned int toset){
	This->derniereReproduction=toset;
}

Bool ElementAnimal_survie(struct ElementAnimal *This, unsigned int tourCourrant){
    if (This->sasiete == 0 && tourCourrant-This->dernierRepas > This->dureeSurvie)
        return False;
    return True;
}

void ElementAnimal_tour(struct ElementAnimal *This){
    This->sasiete=max(This->sasiete-This->metabolisme, 0);
}


void ElementAnimal_predation(ElementAnimal *This)
{
    This->caseParent->g->getListVoisins(This->caseParent);

//    Si X a dans son voisinnage immédiat (8 cases) un élément Y et satiete(X)+ taille(Y)<
//    taille_du_bide(X), Alors il se déplace sur la case de Y et dernier_repas(X)< tour_courant et
//    satiete(X)< satiete(X)+ taille(Y). L’animal Y meurt et disparait.
}
