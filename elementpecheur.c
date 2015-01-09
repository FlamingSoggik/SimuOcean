#include "elementpecheur.h"

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "Bool.h"
#include "elementanimal.h"
#include "listetype.h"
#include <time.h>

#define TAILLE_CANNE_A_PECHE 2
#define TAILLE_FILET 2
#define COUT_POSE_PONT 3
#define max(a,b) (a>=b?a:b)

ElementPecheur* New_ElementPecheur(Case *c){
	ElementPecheur* This = malloc(sizeof(ElementPecheur));
	if (!This) return NULL;
	if (ElementPecheur_Init(c, This) < 0){
		free(This);
		return NULL;
	}
	This->Free = Element_New_Free;
	return This;
}

char ElementPecheur_Init(Case *c, ElementPecheur* This){
	if (c == NULL){
		puts("Erreur creation animal case parent vide");
	}
	This->listeDePeche=New_ListeType();
	This->caseParent=c;
	This->type=PECHEUR;
	This->Clear = Element_Clear;
	This->sac = COUT_POSE_PONT*3;
	This->longueurCanne=TAILLE_CANNE_A_PECHE;
	This->tailleFilet=TAILLE_FILET;
	return 0;
}


void ElementPecheur_pecheParCanne(ElementPecheur *This)
{
	static int first = 1;
	if(first == 1){
		srand(time(NULL));
		first = 0;
	}
	int i, j;
	unsigned int index=0;
	ElementAnimal* e;
	ListeCase *lc = New_ListeCase();
	Case *c;
	Case*** MatriceAccessibleReproduction= NULL;
	MatriceAccessibleReproduction=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, This->longueurCanne);
	for(i=0;i<2*This->longueurCanne+1.0;++i){
		for(j=0;j<2*This->longueurCanne+1.0;++j){
			if (MatriceAccessibleReproduction[i][j] != NULL) {
				if (MatriceAccessibleReproduction[i][j]->liste->HasAnAnimal(MatriceAccessibleReproduction[i][j]->liste)){
					e=(ElementAnimal*)MatriceAccessibleReproduction[i][j]->liste->getAnimal(MatriceAccessibleReproduction[i][j]->liste);
					if (This->peutPecher(This, e->type) == True)
						lc->Push(lc, MatriceAccessibleReproduction[i][j]);
				}
			}
		}
	}
	if (lc->Taille(lc) != 0){
		index=rand()%lc->Taille(lc);
		c=lc->getNieme(lc, index);
		e=(ElementAnimal*)c->liste->getAnimal(c->liste);
		This->sac+=e->constantes->taille;
		e->caseParent->liste->deleteElement(e->caseParent->liste, (Element*)e);

	}
	lc->Free(lc);
	for (i=0; i<2*This->longueurCanne+1.0;++i){
		free(MatriceAccessibleReproduction[i]);
	}
	free(MatriceAccessibleReproduction);
}


Bool ElementPecheur_peutPecher(ElementPecheur *This, Type t)
{
	if (This->listeDePeche->Contain(This->listeDePeche, t) == True){
			return True;
		}
	return False;
}


void ElementPecheur_pecheParFilet(ElementPecheur *This)
{
	static int first = 1;
	if(first == 1){
		srand(time(NULL));
		first = 0;
	}
	int i, j;
	ElementAnimal* e;
	Case*** MatriceAccessibleReproduction= NULL;
	MatriceAccessibleReproduction=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, This->longueurCanne);
	for(i=0;i<2*This->tailleFilet+1.0;++i){
		for(j=0;j<2*This->tailleFilet+1.0;++j){
			if (MatriceAccessibleReproduction[i][j] != NULL) {
				if (MatriceAccessibleReproduction[i][j]->liste->HasAnAnimal(MatriceAccessibleReproduction[i][j]->liste)){
					e=(ElementAnimal*)MatriceAccessibleReproduction[i][j]->liste->getAnimal(MatriceAccessibleReproduction[i][j]->liste);
					if (This->peutPecher(This, e->type) == True){
						This->sac+=e->constantes->taille;
						e->caseParent->liste->deleteElement(e->caseParent->liste, (Element*)e);
					}
				}
			}
		}
	}
	for (i=0; i<2*This->tailleFilet+1.0;++i){
		free(MatriceAccessibleReproduction[i]);
	}
	free(MatriceAccessibleReproduction);;
}
