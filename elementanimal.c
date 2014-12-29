#include <stdlib.h>
#include <stdio.h>

#include "elementanimal.h"
#include "math.h"
#include "Bool.h"

#include "listetype.h"

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

char remplirListePredation(ElementAnimal* This, Type t)
{
	This->listePredation=New_ListeType();
	switch (t){
	case PLANCTON:
		break;
	case CORAIL:
		This->listePredation->Push(This->listePredation, PLANCTON);
		break;
	case BAR:
		This->listePredation->Push(This->listePredation, PLANCTON);
		This->listePredation->Push(This->listePredation, PONT);
		break;
	case THON:
		This->listePredation->Push(This->listePredation, PLANCTON);
		break;
	case PYRANHA:
		This->listePredation->Push(This->listePredation, BAR);
		This->listePredation->Push(This->listePredation, THON);
		This->listePredation->Push(This->listePredation, PECHEUR);
		break;
	case REQUIN:
		This->listePredation->Push(This->listePredation, BAR);
		This->listePredation->Push(This->listePredation, PECHEUR);
		break;
	case ORQUE:
		This->listePredation->Push(This->listePredation, REQUIN);
		This->listePredation->Push(This->listePredation, PECHEUR);
		break;
	case BALEINE:
		This->listePredation->Push(This->listePredation, PLANCTON);
		This->listePredation->Push(This->listePredation, PONT);
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
	This->peutManger=ElementAnimal_peutManger;
	if (remplirListePredation(This, t) < 0){
		return ERR_TYPE_NOT_ANIMAL;

	}
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
	if(This) ElementAnimal_Clear(This);
	free(This);
	puts("Destruction de l'Animal dynamique.\n");
}

void ElementAnimal_Free(struct ElementAnimal *This){
    Element_Clear((Element*)This);
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
	Case* **MatriceAccessiblePredation;
	MatriceAccessiblePredation=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, 1);
	int i, j;
	Element* plusInteressant;
	char flag = 0;
	for(i=0; i<2*This->sautMax+1.0 && flag == 0; ++i){
		for(j=0; j<2*This->sautMax+1.0  && flag == 0; ++j){
			if (MatriceAccessiblePredation[i][j] != NULL){
				//Il y a une Case à cette position
				if(MatriceAccessiblePredation[i][j]->liste->HasAPecheur(MatriceAccessiblePredation[i][j]->liste) == 1){
					// Si il y a un pecheur
					if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){
						//sur un pont
						if(This->peutManger(This, PONT) == True){
							plusInteressant= MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste);
							flag = 1;
						}
					} else {
						//seul dans l'eau
						if(This->peutManger(This, PECHEUR) == True){
							plusInteressant = (Element*)MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste);
							flag=1;
						}
					}
				}
				if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){
					//Cas ou la case ciblée à un pont
					if(This->peutManger(This, PONT) == True){
						plusInteressant = (Element*)MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste);
						flag=1;
					}
				}
				if(MatriceAccessiblePredation[i][j]->liste->HasAnAnimal(MatriceAccessiblePredation[i][j]->liste) == 1){
					//Elle contient un animal
					ElementAnimal* current = (ElementAnimal*)MatriceAccessiblePredation[i][j]->liste->getAnimal(MatriceAccessiblePredation[i][j]->liste);
					if (This->peutManger(This, current->type) == True && This->tailleDuBide > current->taille && ((ElementAnimal*)plusInteressant)->taille < current->taille){
						// L'element semble plus intéressant, il faut maintenant vérifier qu'il ne soit pas sous un pont sans qu'on y ait accès
						if(This->taille < This->caseParent->g->TailleMaxSousPont){
							plusInteressant=(Element*)current;
						}
						else {
							if (MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){
								plusInteressant=(Element*)current;
							}
						}
					}
				}
			}
		}
	}
	if(plusInteressant->type==PECHEUR){
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, plusInteressant->caseParent->posX, plusInteressant->caseParent->posY);
		This->caseParent->liste->deleteElement(This->caseParent->liste, (Element*)This);
	} else if (plusInteressant->type == PONT){

	} else {
		if(This->sasiete+((ElementAnimal*)plusInteressant)->taille < This->tailleDuBide){
			This->dernierRepas=This->caseParent->g->TourCourant;
			This->sasiete=This->sasiete+((ElementAnimal*)plusInteressant)->taille;
		}
	}
}


Bool ElementAnimal_peutManger(ElementAnimal *This, Type t)
{
	if (This->listePredation->contain(This->listePredation, t) == True){
		return True;
	}
	return False;
}


void ElementAnimal_Clear(ElementAnimal *This)
{
	This->listePredation->Free(This->listePredation);
}
