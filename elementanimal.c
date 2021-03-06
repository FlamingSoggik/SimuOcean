#include <stdlib.h>
#include <stdio.h>

#include "elementanimal.h"
#include "elementpont.h"
#include "elementpecheur.h"
#include "math.h"
#include "Bool.h"

#include "listetype.h"
#include <time.h>

#define max(a,b) (a>=b?a:b)

ElementAnimal_Constantes C_Vide;
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
			//printf("Erreur lienVersConstantes %d\n", t);
			return ERR_TYPE_NOT_ANIMAL;
			break;
	}
	return 0;
}

void defineConstant()
{
    C_Vide.dureeSurvie=0;
    C_Vide.taille=0;
    C_Vide.tailleDuBide=0;
    C_Vide.sautMax=0;
    C_Vide.metabolisme=0;
    C_Vide.gestation=0;
    C_Vide.frequenceReproduction=0;

    C_Plancton.dureeSurvie=100;
    C_Plancton.taille=3;
    C_Plancton.tailleDuBide=1;
    C_Plancton.sautMax=0;
    C_Plancton.metabolisme=0;
    C_Plancton.gestation=0;
    C_Plancton.frequenceReproduction=5;

    C_Corail.dureeSurvie=6;
    C_Corail.taille=4;
    C_Corail.tailleDuBide=4;
    C_Corail.sautMax=0;
    C_Corail.metabolisme=1;
    C_Corail.gestation=1;
    C_Corail.frequenceReproduction=5;

    C_Bar.dureeSurvie=24;
    C_Bar.taille=4;
    C_Bar.tailleDuBide=4;
    C_Bar.sautMax=2;
    C_Bar.metabolisme=1;
    C_Bar.gestation=1;
    C_Bar.frequenceReproduction=2;

    C_Thon.dureeSurvie=14;
    C_Thon.taille=4;
    C_Thon.tailleDuBide=4;
    C_Thon.sautMax=1;
    C_Thon.metabolisme=1;
    C_Thon.gestation=1;
    C_Thon.frequenceReproduction=6;

    C_Pyranha.dureeSurvie=15;
    C_Pyranha.taille=5;
    C_Pyranha.tailleDuBide=5;
    C_Pyranha.sautMax=2;
    C_Pyranha.metabolisme=1;
    C_Pyranha.gestation=1;
    C_Pyranha.frequenceReproduction=7;

    C_Requin.dureeSurvie=20;
    C_Requin.taille=6;
    C_Requin.tailleDuBide=12;
    C_Requin.sautMax=5;
    C_Requin.metabolisme=1;
    C_Requin.gestation=1;
    C_Requin.frequenceReproduction=13;

    C_Orque.dureeSurvie=29;
    C_Orque.taille=7;
    C_Orque.tailleDuBide=7;
    C_Orque.sautMax=4;
    C_Orque.metabolisme=1;
    C_Orque.gestation=2;
    C_Orque.frequenceReproduction=18;

    C_Baleine.dureeSurvie=29;
    C_Baleine.taille=8;
    C_Baleine.tailleDuBide=8;
    C_Baleine.sautMax=4;
    C_Baleine.metabolisme=1;
    C_Baleine.gestation=5;
    C_Baleine.frequenceReproduction=50;
}

void remplirListePredation(Grille* This)
{
	if (This->listePredationInitialise == 0){
		C_Plancton.listePredation = New_ListeType();
		C_Corail.listePredation = New_ListeType();
		C_Bar.listePredation = New_ListeType();
		C_Thon.listePredation = New_ListeType();
		C_Pyranha.listePredation = New_ListeType();
		C_Requin.listePredation = New_ListeType();
		C_Orque.listePredation = New_ListeType();
		C_Baleine.listePredation = New_ListeType();
		++This->listePredationInitialise;
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

void viderListePredation(Grille* This)
{
	C_Plancton.listePredation->Free(C_Plancton.listePredation);
	C_Corail.listePredation->Free(C_Corail.listePredation);
	C_Bar.listePredation->Free(C_Bar.listePredation);
	C_Thon.listePredation->Free(C_Thon.listePredation);
	C_Pyranha.listePredation->Free(C_Pyranha.listePredation);
	C_Requin.listePredation->Free(C_Requin.listePredation);
	C_Orque.listePredation->Free(C_Orque.listePredation);
	C_Baleine.listePredation->Free(C_Baleine.listePredation);
	This->listePredationInitialise=0;
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
	This->reproduction=ElementAnimal_reproduction;
	This->hasAlreadyPlayed=0;
	This->aFaitSonTour=ElementAnimal_aFaitSonTour;
	This->finDuTour=ElementAnimal_finDuTour;
	This->doitJouerCeTour=ElementAnimal_doitJouerCeTour;
	char ret = lienVersConstantes(This, t);
	This->sasiete = This->constantes->tailleDuBide;
	return ret;
}

uint16_t ElementAnimal_getDernierRepas(struct ElementAnimal *This){
	return This->dernierRepas;
}

void ElementAnimal_setDernierRepas(struct ElementAnimal *This, uint16_t toset){
	This->dernierRepas=toset;
}

void ElementAnimal_Free(struct ElementAnimal *This){
	Element_Clear((Element*)This);
	puts("Destruction de l'Animal statique.\n");
}

int16_t ElementAnimal_getSasiete(struct ElementAnimal *This){
	return This->sasiete;
}

void ElementAnimal_setSasiete(struct ElementAnimal *This, int16_t toset){
	This->sasiete=toset;
}

uint16_t ElementAnimal_getderniereReproduction(struct ElementAnimal *This){
	return This->derniereReproduction;
}

void ElementAnimal_setderniereReproduction(struct ElementAnimal *This, uint16_t toset){
	This->derniereReproduction=toset;
}

Bool ElementAnimal_survie(struct ElementAnimal *This){
	if (This->sasiete == 0 && This->caseParent->g->TourCourant - This->dernierRepas > This->constantes->dureeSurvie)
		return False;
	return True;
}

void ElementAnimal_tour(struct ElementAnimal *This){
	This->sasiete=max(This->sasiete-This->constantes->metabolisme, 0);
}

void ElementAnimal_predation(ElementAnimal *This)
{
	Case***MatriceAccessiblePredation = NULL;
	int16_t i, j;
	MatriceAccessiblePredation=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, 1);
	ListeElem *l_elementBouffable = New_ListeElem();
	char flag = 0;
	for(i=0; i<3 && flag == 0; ++i){
		for(j=0; j<3  && flag == 0; ++j){
			if (MatriceAccessiblePredation[i][j] != NULL){
				//Il y a une Case à cette position
				if(MatriceAccessiblePredation[i][j]->liste->HasDirt(MatriceAccessiblePredation[i][j]->liste) == 1)
					continue;
				if(MatriceAccessiblePredation[i][j]->liste->HasAPecheur(MatriceAccessiblePredation[i][j]->liste) == 1){

//					// Si il y a un pecheur
					if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){
						//sur un pont
						if(This->peutManger(This, PONT) == True){
							l_elementBouffable->Vider(l_elementBouffable);
							l_elementBouffable->Push(l_elementBouffable, MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste));
							flag = 1;
							continue;
						}
					} else {

						//seul dans l'eau
						if(This->peutManger(This, PECHEUR) == True){
							l_elementBouffable->Vider(l_elementBouffable);
							l_elementBouffable->Push(l_elementBouffable, MatriceAccessiblePredation[i][j]->liste->getPecheur(MatriceAccessiblePredation[i][j]->liste));
							flag=1;
							continue;
						}
					}
				}
				if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){

					//Cas ou la case ciblée à un pont
					if(This->peutManger(This, PONT) == True){
						l_elementBouffable->Vider(l_elementBouffable);
						l_elementBouffable->Push(l_elementBouffable, MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste));
						flag=1;
						continue;
					}
				}
				if(MatriceAccessiblePredation[i][j]->liste->HasAnAnimal(MatriceAccessiblePredation[i][j]->liste) == 1){

					//Elle contient un animal
					ElementAnimal* current = (ElementAnimal*)MatriceAccessiblePredation[i][j]->liste->getAnimal(MatriceAccessiblePredation[i][j]->liste);
					if (This->peutManger(This, current->type) == True && This->sasiete+current->constantes->taille < This->constantes->tailleDuBide){
						//L'élément est mangeable mais est-ce le plus intéressant ?

						if (l_elementBouffable->Taille(l_elementBouffable) == 0){
							//C'est le seul ou le premier testé donc oui, il est plus intéressant que rien
							//Mais est-il accessible?
							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont || MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){

								//Je passe sous un pont ou alors il n'y a pas de pont :  je vais le bouffer !
								l_elementBouffable->Push(l_elementBouffable, (Element*)current);
							}
						}
						else if (((ElementAnimal*)l_elementBouffable->Top->e)->constantes->taille < current->constantes->taille){
							// L'element semble plus intéressant, il faut maintenant vérifier qu'il ne soit pas sous un pont sans qu'on y ait accès
							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont || MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){
								// Je passe sous un pont ou alors il n'y a pas de pont, je l'ajoutte à la liste
								l_elementBouffable->Vider(l_elementBouffable);
								l_elementBouffable->Push(l_elementBouffable, (Element*)current);
							}
						}
						else if(((ElementAnimal*)l_elementBouffable->Top->e)->constantes->taille == current->constantes->taille){

							// L'element semble plus intéressant, il faut maintenant vérifier qu'il ne soit pas sous un pont sans qu'on y ait accès
							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont || MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){
								// Je passe sous un pont, let's go
								l_elementBouffable->Push(l_elementBouffable, (Element*)current);
							}
						}
					}
				}
			}
		}
	}


	// On a plus besoin de la matrice temporaire donc on peux la supprimer :
	for (i=0; i<3;++i){
		free(MatriceAccessiblePredation[i]);
	}
	free(MatriceAccessiblePredation);

	if(l_elementBouffable->Taille(l_elementBouffable) == 0){
		l_elementBouffable->Free(l_elementBouffable);
		return;
	}

	if(l_elementBouffable->Top->e->type == PECHEUR){
        ElementPecheur *p = (ElementPecheur*)l_elementBouffable->Top->e;
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, l_elementBouffable->Top->e->caseParent->posX, l_elementBouffable->Top->e->caseParent->posY);
        p->mourir(p);
        //This->caseParent->liste->deleteElement(This->caseParent->liste, (Element*)This);
	} else if (l_elementBouffable->Top->e->type == PONT){
		ElementPont *ep = (ElementPont*)l_elementBouffable->Top->e;
		//l_elementBouffable->getNieme(l_elementBouffable, rand()%l_elementBouffable->Taille(l_elementBouffable));
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, ep->caseParent->posX, ep->caseParent->posY);
		This->caseParent->g->detruirePont(This->caseParent->g, ep->caseParent);
	} else {
		ElementAnimal *ea = (ElementAnimal*)l_elementBouffable->getNieme(l_elementBouffable, rand()%l_elementBouffable->Taille(l_elementBouffable));
		This->dernierRepas=This->caseParent->g->TourCourant;
		This->sasiete=This->sasiete+ea->constantes->taille;
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, ea->caseParent->posX, ea->caseParent->posY);
		ea->caseParent->liste->deleteElement(ea->caseParent->liste, (Element*)ea);
	}
	l_elementBouffable->Vider(l_elementBouffable);
	l_elementBouffable->Free(l_elementBouffable);

}

void ElementAnimal_deplacement(ElementAnimal *This){
	int16_t flag;
	Case*** MatriceAccessibleDeplacement = NULL;
	MatriceAccessibleDeplacement=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, This->constantes->sautMax);
	int16_t deplX, deplY, isNeg, deplXpositif, deplYpositif;
	int16_t i, j;
	flag=0;
	for(i=0;i<2*This->constantes->sautMax+1.0 && flag == 0;++i){
		for(j=0;j<2*This->constantes->sautMax+1.0 && flag == 0;++j){
			if (MatriceAccessibleDeplacement[i][j] != NULL)
				if (MatriceAccessibleDeplacement[i][j]->liste->HasAnAnimal(MatriceAccessibleDeplacement[i][j]->liste) == 0 && MatriceAccessibleDeplacement[i][j]->liste->HasDirt(MatriceAccessibleDeplacement[i][j]->liste) == 0)
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
	isNeg = 0;
	Case* caseDeDeplacement;
	while (flag == 0){
		deplX = 0;
		deplY = 0;
		deplXpositif = 0;
		deplYpositif = 0;
		while(deplXpositif == 0 && deplYpositif == 0){
			deplXpositif = (rand()%(This->constantes->sautMax+1));
			deplYpositif = (rand()%(This->constantes->sautMax+1));
		}
		isNeg=rand()%2;
		if(isNeg == 1){
			deplX=deplXpositif*-1;
		} else {
			deplX=deplXpositif;
		}
		isNeg=rand()%2;
		if(isNeg == 1){
			deplY=deplYpositif*-1;
		} else {
			deplY=deplYpositif;
		}
		caseDeDeplacement=MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY];
		if (caseDeDeplacement != NULL){
			if (caseDeDeplacement->liste->HasAnAnimal(caseDeDeplacement->liste) == 0 && caseDeDeplacement->liste->HasDirt(caseDeDeplacement->liste) == 0){
				if (This->constantes->taille <= This->caseParent->g->TailleMaxSousPont || caseDeDeplacement->liste->HasAPont(caseDeDeplacement->liste) == 0)
					flag=1;
			}
		}
	}
	if(This->sasiete-max(deplXpositif, deplYpositif)>=0){
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY]->posX, MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY]->posY);
		This->sasiete=This->sasiete-max(deplX, deplY);
	}
	for (i=0; i<2*This->constantes->sautMax+1.0;++i){
		free(MatriceAccessibleDeplacement[i]);
	}
	free(MatriceAccessibleDeplacement);
}

void ElementAnimal_reproduction(ElementAnimal *This){
	if (This->sasiete < This->constantes->gestation*This->constantes->metabolisme){
		return;
	}
	if (This->derniereReproduction + This->constantes->frequenceReproduction >= This->caseParent->g->TourCourant){
		return;
	}
	int16_t flag;
	Case*** MatriceAccessibleReproduction= NULL;
	MatriceAccessibleReproduction=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, 1);
	int16_t i, j;
	flag=0;
	Case *caseNaissance = NULL;
	ListeCase *lcaseNaissance = New_ListeCase();
	ElementAnimal* e = NULL, *amoureux = NULL;
		for(i=0;i<3 && flag == 0;++i){
			for(j=0;j<3 && flag == 0;++j){
				if (MatriceAccessibleReproduction[i][j] != NULL && MatriceAccessibleReproduction[i][j]->liste->HasDirt(MatriceAccessibleReproduction[i][j]->liste) == 0) {
					if (MatriceAccessibleReproduction[i][j]->liste->HasAnAnimal(MatriceAccessibleReproduction[i][j]->liste)){
						e=(ElementAnimal*)MatriceAccessibleReproduction[i][j]->liste->getAnimal(MatriceAccessibleReproduction[i][j]->liste);
						if (e->type == This->type)
							amoureux=e;
					}
					else if (This->constantes->taille <= This->caseParent->g->TailleMaxSousPont || MatriceAccessibleReproduction[i][j]->liste->HasAPont(MatriceAccessibleReproduction[i][j]->liste) == 0){
						lcaseNaissance->Push(lcaseNaissance, MatriceAccessibleReproduction[i][j]);
					}
				}
			}
		}

		if (lcaseNaissance->Taille(lcaseNaissance) == 0|| amoureux == NULL){
			for (i=0; i<3;++i){
				free(MatriceAccessibleReproduction[i]);
			}
			free(MatriceAccessibleReproduction);
			lcaseNaissance->Free(lcaseNaissance);
			return;
		}
		caseNaissance = lcaseNaissance->getNieme(lcaseNaissance, rand()%lcaseNaissance->Taille(lcaseNaissance));

	This->sasiete-=(This->constantes->gestation*This->constantes->metabolisme);
	caseNaissance->liste->Push(caseNaissance->liste, (Element*)New_ElementAnimal(caseNaissance, This->type));
	This->derniereReproduction=This->caseParent->g->TourCourant;
	for (i=0; i<3;++i){
		free(MatriceAccessibleReproduction[i]);
	}
	free(MatriceAccessibleReproduction);
	lcaseNaissance->Free(lcaseNaissance);
}

Bool ElementAnimal_peutManger(ElementAnimal *This, Type t)
{
	if (This->constantes->listePredation->Contain(This->constantes->listePredation, t) == True){
		return True;
	}
	return False;
}


void ElementAnimal_aFaitSonTour(ElementAnimal *This)
{
	This->hasAlreadyPlayed=1;
}

void ElementAnimal_finDuTour(ElementAnimal *This)
{
	This->hasAlreadyPlayed=0;
}


Bool ElementAnimal_doitJouerCeTour(ElementAnimal *This)
{
	if (This->hasAlreadyPlayed == 1)
		return False;
	return True;
}
