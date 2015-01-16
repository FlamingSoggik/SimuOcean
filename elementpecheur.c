#include "elementpecheur.h"

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "Bool.h"
#include "elementanimal.h"
#include "elementpont.h"
#include "listetype.h"
#include <time.h>

#define TAILLE_CANNE_A_PECHE 2
#define TAILLE_FILET 2
#define COUT_POSE_PONT 3
#define DISTANCE_DEPLACEMENT 2
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
	This->listeDePeche->Push(This->listeDePeche, BAR);
	This->listeDePeche->Push(This->listeDePeche, THON);
	This->listeDePeche->Push(This->listeDePeche, PYRANHA);
	This->listeDePeche->Push(This->listeDePeche, REQUIN);
	This->listeDePeche->Push(This->listeDePeche, ORQUE);
	This->listeDePeche->Push(This->listeDePeche, BALEINE);
	This->caseParent=c;
	This->PositionInitialeX=This->caseParent->posX;
	This->PositionInitialeY=This->caseParent->posY;
	This->pecheParCanne=ElementPecheur_pecheParCanne;
	This->pecheParFilet=ElementPecheur_pecheParFilet;
	This->peutPecher=ElementPecheur_peutPecher;
	This->deplacement=ElementPecheur_deplacement;
	This->construirePont=ElementPecheur_construirePont;
	This->mourir=ElementPecheur_mourir;
	This->type=PECHEUR;
	This->Clear = Element_Clear;
	This->sac = COUT_POSE_PONT*3;
	This->longueurCanne=TAILLE_CANNE_A_PECHE;
	This->tailleFilet=TAILLE_FILET;
	This->distanceDeplacement=DISTANCE_DEPLACEMENT;
	return 0;
}


void ElementPecheur_pecheParCanne(ElementPecheur *This)
{
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
					printf("Type de l'animal testé tout de suite : %d\n", e->type);
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
		printf("Element mangé est de type : %d\n", e->type);
		This->sac+=e->constantes->taille;
		e->caseParent->liste->deleteElement(e->caseParent->liste, (Element*)e);

	}
	else {
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
	free(MatriceAccessibleReproduction);
}


void ElementPecheur_deplacement(ElementPecheur *This, char direction)
{
	int deplX = 0, deplY = 0;
	switch (direction) {
		case 1:
			deplX=1;
			deplY=-1;
			break;
		case 2:
			deplX=1;
			break;
		case 3:
			deplX=1;
			deplY=1;
			break;
		case 4:
			deplY=-1;
			break;
		case 5:
			break;
		case 6:
			deplY=1;
			break;
		case 7:
			deplX=-1;
			deplY=-1;
			break;
		case 8:
			deplX=-1;
			break;
		case 9:
			deplX=-1;
			deplY=1;
			break;
		default:
			printf("Error, la direction du pecheur doit être un nombre entre 1 et 9 compris\n");
			return;
	}
	if ((double)This->caseParent->posX+deplX < 0 || This->caseParent->posX+deplX > This->caseParent->g->Taille-1 || (double)This->caseParent->posY+deplY < 0 || This->caseParent->posY+deplY > This->caseParent->g->Taille-1){
		// Le joueur essaie de sortir de la grille
		// lancer cri de whilem
		return;
	}
	Case *caseDeplacement;
	caseDeplacement = &This->caseParent->g->tab[This->caseParent->posX+deplX][This->caseParent->posY+deplY];
	if ((caseDeplacement->liste->HasAPont(caseDeplacement->liste) == 1 || caseDeplacement->liste->HasDirt(caseDeplacement->liste) == 1) && caseDeplacement->liste->HasAPecheur(caseDeplacement->liste) == 0){
		//Il y a un pond et pas de pecheur sur ce pont, on peut s'y déplacer
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, This->caseParent->posX+deplX, This->caseParent->posY+deplY);
	}
	else {
		//pas possible
		return;
	}
}


void ElementPecheur_construirePont(ElementPecheur *This, char direction)
{
	int deplX = 0, deplY = 0;
	switch (direction) {
		case 1:
			deplX=1;
			deplY=-1;
			break;
		case 2:
			deplX=1;
			break;
		case 3:
			deplX=1;
			deplY=1;
			break;
		case 4:
			deplY=-1;
			break;
		case 5:
			break;
		case 6:
			deplY=1;
			break;
		case 7:
			deplX=-1;
			deplY=-1;
			break;
		case 8:
			deplX=-1;
			break;
		case 9:
			deplX=-1;
			deplY=1;
			break;
		default:
			printf("Error, la direction du pecheur doit être un nombre entre 1 et 9 compris\n");
			return;
	}
	if ((double)This->caseParent->posX+deplX < 0 || This->caseParent->posX+deplX > This->caseParent->g->Taille-1 || (double)This->caseParent->posY+deplY < 0 || This->caseParent->posY+deplY > This->caseParent->g->Taille-1){
		// Le joueur essaie de construire en dehors de la ligne
		// lancer cri de whilem
		return;
	}
	Case *caseCreationDuPont;
	caseCreationDuPont = &This->caseParent->g->tab[This->caseParent->posX+deplX][This->caseParent->posY+deplY];
	if (This->sac >= COUT_POSE_PONT && caseCreationDuPont->liste->HasAPont(caseCreationDuPont->liste) == 0 && caseCreationDuPont->liste->HasDirt(caseCreationDuPont->liste) == 0 && (caseCreationDuPont->liste->HasAnAnimal(caseCreationDuPont->liste) == 0 || (caseCreationDuPont->liste->HasAnAnimal(caseCreationDuPont->liste) == 1 && ((ElementAnimal*)caseCreationDuPont->liste->getAnimal(caseCreationDuPont->liste))->constantes->taille < This->caseParent->g->TailleMaxSousPont))){
		//Il y a un pond et pas de pecheur sur ce pont, on peut s'y déplacer
		caseCreationDuPont->liste->Push(caseCreationDuPont->liste, (Element*)New_ElementPont(caseCreationDuPont));
		This->sac-=COUT_POSE_PONT;
	}
	else {
		printf("%d\n", __LINE__);
		//pas possible
		return;
	}
}


void ElementPecheur_mourir(ElementPecheur *This)
{
	This->caseParent->g->reinitPecheur(This->caseParent->g, (Element*)This);
}
