#include <stdlib.h>
#include <stdio.h>

#include "elementanimal.h"
#include "math.h"
#include "Bool.h"

#include "listetype.h"
#include <time.h>

#define max(a,b) (a>=b?a:b)


ElementAnimal_Constantes C_Plancton;
ElementAnimal_Constantes C_Corail;
ElementAnimal_Constantes C_Bar;
ElementAnimal_Constantes C_Thon;
ElementAnimal_Constantes C_Pyranha;
ElementAnimal_Constantes C_Requin;
ElementAnimal_Constantes C_Orque;
ElementAnimal_Constantes C_Baleine;


ElementAnimal* New_ElementAnimal(Case *c, Type t){
	ElementAnimal* This = malloc(sizeof(ElementAnimal));
	if (!This) return NULL;
	if (ElementAnimal_Init(c, This, t) < 0){
		free(This);
		return NULL;
	}
	This->Free = Element_New_Free;
	return This;
}

char lienVersConstantes(ElementAnimal* This, Type t)
{
	switch (t){
		case PLANCTON:
			This->constantes=&C_Plancton;
			break;
		case CORAIL:
			This->constantes=&C_Corail;
			break;
		case BAR:
			This->constantes=&C_Bar;
			break;
		case THON:
			This->constantes=&C_Thon;
			break;
		case PYRANHA:
			This->constantes=&C_Pyranha;
			break;
		case REQUIN:
			This->constantes=&C_Requin;
			break;
		case ORQUE:
			This->constantes=&C_Orque;
			break;
		case BALEINE:
			This->constantes=&C_Baleine;
			break;
		default :
			puts("Erreur lienVersConstantes");
			return ERR_TYPE_NOT_ANIMAL;
			break;
	}
	return 0;
}

void defineConstant()
{
	C_Plancton.dureeSurvie=1;
	C_Plancton.taille=1;
	C_Plancton.tailleDuBide=1;
	C_Plancton.sautMax=1;
	C_Plancton.metabolisme=1;
	C_Plancton.gestation=1;
	C_Plancton.frequenceReproduction=1;
	C_Corail.dureeSurvie=1;
	C_Corail.taille=1;
	C_Corail.tailleDuBide=1;
	C_Corail.sautMax=1;
	C_Corail.metabolisme=1;
	C_Corail.gestation=1;
	C_Corail.frequenceReproduction=1;
	C_Bar.dureeSurvie=1;
	C_Bar.taille=2;
	C_Bar.tailleDuBide=1;
	C_Bar.sautMax=1;
	C_Bar.metabolisme=1;
	C_Bar.gestation=1;
	C_Bar.frequenceReproduction=1;
	C_Thon.dureeSurvie=1;
	C_Thon.taille=1;
	C_Thon.tailleDuBide=1;
	C_Thon.sautMax=1;
	C_Thon.metabolisme=1;
	C_Thon.gestation=1;
	C_Thon.frequenceReproduction=1;
	C_Pyranha.dureeSurvie=1;
	C_Pyranha.taille=15;
	C_Pyranha.tailleDuBide=14;
	C_Pyranha.sautMax=1;
	C_Pyranha.metabolisme=1;
	C_Pyranha.gestation=1;
	C_Pyranha.frequenceReproduction=1;
	C_Requin.dureeSurvie=1;
	C_Requin.taille=1;
	C_Requin.tailleDuBide=1;
	C_Requin.sautMax=1;
	C_Requin.metabolisme=1;
	C_Requin.gestation=1;
	C_Requin.frequenceReproduction=1;
	C_Orque.dureeSurvie=1;
	C_Orque.taille=1;
	C_Orque.tailleDuBide=1;
	C_Orque.sautMax=1;
	C_Orque.metabolisme=1;
	C_Orque.gestation=1;
	C_Orque.frequenceReproduction=1;
	C_Baleine.dureeSurvie=1;
	C_Baleine.taille=1;
	C_Baleine.tailleDuBide=1;
	C_Baleine.sautMax=1;
	C_Baleine.metabolisme=1;
	C_Baleine.gestation=1;
	C_Baleine.frequenceReproduction=1;
}

void remplirListePredation()
{
	static char i = 0;
	if (i == 0){
		C_Plancton.listePredation = New_ListeType();
		C_Corail.listePredation = New_ListeType();
		C_Bar.listePredation = New_ListeType();
		C_Thon.listePredation = New_ListeType();
		C_Pyranha.listePredation = New_ListeType();
		C_Requin.listePredation = New_ListeType();
		C_Orque.listePredation = New_ListeType();
		C_Baleine.listePredation = New_ListeType();
		++i;
	}
	else {
		C_Plancton.listePredation->Free(C_Plancton.listePredation);
		C_Plancton.listePredation = New_ListeType();

		C_Corail.listePredation->Free(C_Corail.listePredation);
		C_Corail.listePredation = New_ListeType();

		C_Bar.listePredation->Free(C_Bar.listePredation);
		C_Bar.listePredation = New_ListeType();

		C_Thon.listePredation->Free(C_Thon.listePredation);
		C_Thon.listePredation = New_ListeType();

		C_Pyranha.listePredation->Free(C_Pyranha.listePredation);
		C_Pyranha.listePredation = New_ListeType();

		C_Requin.listePredation->Free(C_Requin.listePredation);
		C_Requin.listePredation = New_ListeType();

		C_Orque.listePredation->Free(C_Orque.listePredation);
		C_Orque.listePredation = New_ListeType();

		C_Baleine.listePredation->Free(C_Baleine.listePredation);
		C_Baleine.listePredation = New_ListeType();
	}
	C_Corail.listePredation->Push(C_Corail.listePredation, PLANCTON);
	C_Bar.listePredation->Push(C_Bar.listePredation, PLANCTON);
	C_Bar.listePredation->Push(C_Bar.listePredation, PONT);
	C_Thon.listePredation->Push(C_Thon.listePredation, PLANCTON);
	C_Pyranha.listePredation->Push(C_Pyranha.listePredation, BAR);
	C_Pyranha.listePredation->Push(C_Pyranha.listePredation, THON);
	C_Pyranha.listePredation->Push(C_Pyranha.listePredation, PECHEUR);
	C_Requin.listePredation->Push(C_Requin.listePredation, BAR);
	C_Requin.listePredation->Push(C_Requin.listePredation, PECHEUR);
	C_Orque.listePredation->Push(C_Orque.listePredation, REQUIN);
	C_Orque.listePredation->Push(C_Orque.listePredation, PECHEUR);
	C_Baleine.listePredation->Push(C_Baleine.listePredation, PLANCTON);
	C_Baleine.listePredation->Push(C_Baleine.listePredation, PONT);
}

void viderListePredation()
{
	C_Plancton.listePredation->Free(C_Plancton.listePredation);
	C_Corail.listePredation->Free(C_Corail.listePredation);
	C_Bar.listePredation->Free(C_Bar.listePredation);
	C_Thon.listePredation->Free(C_Thon.listePredation);
	C_Pyranha.listePredation->Free(C_Pyranha.listePredation);
	C_Requin.listePredation->Free(C_Requin.listePredation);
	C_Orque.listePredation->Free(C_Orque.listePredation);
	C_Baleine.listePredation->Free(C_Baleine.listePredation);
}

char ElementAnimal_Init(Case *c, ElementAnimal* This, Type t){
	if (c == NULL){
		puts("Erreur creation animal case parent vide");
	}
	This->caseParent=c;
	This->type=t;
	This->Clear = Element_Clear;
	This->dernierRepas = 0;
	This->GetDernierRepas = ElementAnimal_getDernierRepas;
	This->SetDernierRepas = ElementAnimal_setDernierRepas;
	This->sasiete = 0;
	This->GetSasiete = ElementAnimal_getSasiete;
	This->SetSasiete = ElementAnimal_setSasiete;
	This->derniereReproduction = 0;
	This->GetDerniereReproduction = ElementAnimal_getderniereReproduction;
	This->SetDerniereReproduction = ElementAnimal_setderniereReproduction;
	This->tour=ElementAnimal_tour;
	This->survie=ElementAnimal_survie;
	This->peutManger=ElementAnimal_peutManger;
	This->predation=ElementAnimal_predation;
	This->deplacement=ElementAnimal_deplacement;
	if (lienVersConstantes(This, t) < 0){
		puts("Erreur définition des constantes");
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
	if (This->sasiete == 0 && tourCourrant-This->dernierRepas > This->constantes->dureeSurvie)
		return False;
	return True;
}

void ElementAnimal_tour(struct ElementAnimal *This){
	This->sasiete=max(This->sasiete-This->constantes->metabolisme, 0);
}


void ElementAnimal_predation(ElementAnimal *This)
{
	Case***MatriceAccessiblePredation = NULL;
	int i, j;
	MatriceAccessiblePredation=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, This->constantes->sautMax);
	Element* plusInteressant = NULL;
	char flag = 0;
	for(i=0; i<2*This->constantes->sautMax+1.0 && flag == 0; ++i){
		for(j=0; j<2*This->constantes->sautMax+1.0  && flag == 0; ++j){
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
				///Necessaire ou non ?
//				if (flag == 1){
//					continue;
//				}
				if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){
					//Cas ou la case ciblée à un pont
					if(This->peutManger(This, PONT) == True){
						plusInteressant = (Element*)MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste);
						flag=1;
					}
				}
				///Necessaire ou non ?
//				if (flag == 1){
//					continue;
//				}
				if(MatriceAccessiblePredation[i][j]->liste->HasAnAnimal(MatriceAccessiblePredation[i][j]->liste) == 1){
					//Elle contient un animal
					ElementAnimal* current = (ElementAnimal*)MatriceAccessiblePredation[i][j]->liste->getAnimal(MatriceAccessiblePredation[i][j]->liste);
					if (This->peutManger(This, current->type) == True && This->sasiete+current->constantes->taille < This->constantes->tailleDuBide){
						//L'élément est mangeable mais est-ce le plus intéressant ?
						if (plusInteressant == NULL){
							//C'est le seul ou le premioer testé donc oui, il est plus intéressant que rien
							//Mais est-il accessible?
							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont){
								//Je peux passer sous un pont donc oui, je vais le bouffer !
								plusInteressant=(Element*)current;
							}
							else {
								//Je ne passe pas sous un pont, merde, est-ce que je vais pouvoir le bouffer ?
								if (MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){
									// Ouf, il y a pas de pont je peux le bouffer
									plusInteressant=(Element*)current;
								}
							}
						}
						else if(((ElementAnimal*)plusInteressant)->constantes->taille < current->constantes->taille){
							// L'element semble plus intéressant, il faut maintenant vérifier qu'il ne soit pas sous un pont sans qu'on y ait accès
							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont){
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
	}
	// On a plus besoin de la matrice temporaire donc on peux la supprimer :
	for (i=0; i<2*This->constantes->sautMax+1.0;++i){
		free(MatriceAccessiblePredation[i]);
	}
	free(MatriceAccessiblePredation);

	if(plusInteressant == NULL){
		return;
	}
	if(plusInteressant->type==PECHEUR){
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, plusInteressant->caseParent->posX, plusInteressant->caseParent->posY);
		This->caseParent->liste->deleteElement(This->caseParent->liste, (Element*)This);
	} else if (plusInteressant->type == PONT){

	} else {
			This->dernierRepas=This->caseParent->g->TourCourant;
			This->sasiete=This->sasiete+((ElementAnimal*)plusInteressant)->constantes->taille;
			This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, plusInteressant->caseParent->posX, plusInteressant->caseParent->posY);
			plusInteressant->caseParent->liste->deleteElement(plusInteressant->caseParent->liste, plusInteressant);
	}
}

void ElementAnimal_deplacement(ElementAnimal *This){
	static int first = 0;
	int flag;
	if (first == 0)
	{
		srand (time(NULL));
		first = 1;
	}
	Case*** MatriceAccessibleDeplacement = NULL;
	MatriceAccessibleDeplacement=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, This->constantes->sautMax);
	int deplX, deplY;
	int i, j;
	flag=0;
	for(i=0;i<2*This->constantes->sautMax+1.0 && flag == 0;++i){
		for(j=0;j<2*This->constantes->sautMax+1.0 && flag == 0;++j){
			if (MatriceAccessibleDeplacement[i][j] != NULL)
				if (MatriceAccessibleDeplacement[i][j]->liste->HasAnAnimal(MatriceAccessibleDeplacement[i][j]->liste) == 0)
					if (This->constantes->taille <= This->caseParent->g->TailleMaxSousPont || MatriceAccessibleDeplacement[i][j]->liste->HasAPont(MatriceAccessibleDeplacement[i][j]->liste) == 0)
						flag=1;
		}
	}
	if (flag == 0){
		for (i=0; i<2*This->constantes->sautMax+1.0;++i){
			free(MatriceAccessibleDeplacement[i]);
		}
		free(MatriceAccessibleDeplacement);
		return;
	}
	flag = 0;
	while (flag == 0){
		deplX = 0;
		deplY = 0;
		while(deplX == 0 && deplY == 0){
			deplX = (rand()%(This->constantes->sautMax*2))+1-This->constantes->sautMax;
			deplY = (rand()%(This->constantes->sautMax*2))+1-This->constantes->sautMax;
		}
		if (MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY] != NULL){
			if (MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY]->liste->HasAnAnimal(MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY]->liste) == 0){
				flag = 1;
			}
		}
	}
	if(This->sasiete-max(deplX, deplY)>=0){
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, This->constantes->sautMax+deplX, This->constantes->sautMax+deplY);
		This->sasiete=This->sasiete-max(deplX, deplY);
	}
	for (i=0; i<2*This->constantes->sautMax+1.0;++i){
		free(MatriceAccessibleDeplacement[i]);
	}
	free(MatriceAccessibleDeplacement);
}

Bool ElementAnimal_peutManger(ElementAnimal *This, Type t)
{
	if (This->constantes->listePredation->Contain(This->constantes->listePredation, t) == True){
		return True;
	}
	return False;
}
