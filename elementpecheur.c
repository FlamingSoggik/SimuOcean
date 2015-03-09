#include "elementpecheur.h"
#include "stringreplace.h"
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "Bool.h"
#include "elementanimal.h"
#include "elementpont.h"
#include "listetype.h"
#include <time.h>
#include <string.h>

#define TAILLE_CANNE_A_PECHE 2
#define TAILLE_FILET 2
#define COUT_POSE_PONT 3
#define DISTANCE_DEPLACEMENT 2
#define DISTANCE_LANCE_FILET 3
#define max(a,b) (a>=b?a:b)
#define min(a,b) (a>=b?b:a)

ElementPecheur* New_ElementPecheur(Case *c){
	ElementPecheur* This = malloc(sizeof(ElementPecheur));
	if (!This) return NULL;
	if (ElementPecheur_Init(c, This) < 0){
		free(This);
		return NULL;
	}
	This->Free = ElementPecheur_New_Free;
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
	This->pecheParCanneSDL=ElementPecheur_pecheParCanneSDL;
	This->pecheParFilet=ElementPecheur_pecheParFilet;
	This->pecheParFiletSDL=ElementPecheur_pecheParFiletSDL;
	This->peutPecher=ElementPecheur_peutPecher;
	This->deplacement=ElementPecheur_deplacement;
	This->construirePont=ElementPecheur_construirePont;
	This->mourir=ElementPecheur_mourir;
	This->reinitSac=ElementPecheur_reinitSac;
	This->type=PECHEUR;
	This->Clear = ElementPecheur_Clear;
	This->sac = COUT_POSE_PONT*5;
	This->longueurCanne=TAILLE_CANNE_A_PECHE;
	This->tailleFilet=TAILLE_FILET;
	This->distanceDeplacement=DISTANCE_DEPLACEMENT;
	This->estSelectionne=0;
	return 0;
}

void ElementPecheur_Clear(Element *This){
	ElementPecheur *p = (ElementPecheur*)This;
	p->listeDePeche->Free(p->listeDePeche);
}

void ElementPecheur_New_Free(Element* This){
	ElementPecheur *p = (ElementPecheur*)This;
	if(p) This->Clear(This);
	free(p);
}

void ElementPecheur_pecheParCanne(ElementPecheur *This, char *buffer)
{
	int16_t k=0;
	char *buf1, *buf2;

	buf1 = str_replace(buffer, "68", "9");
	buf2 = str_replace(buf1, "86", "9");
	free(buf1);
	buf1 = str_replace(buf2, "86", "9");
	free(buf2);
	buf2 = str_replace(buf1, "48", "7");
	free(buf1);
	buf1= str_replace(buf2, "84", "7");
	free(buf2);
	buf2 = str_replace(buf1, "42", "1");
	free(buf1);
	buf1 = str_replace(buf2, "24", "1");
	free(buf2);
	buf2 = str_replace(buf1, "62", "3");
	free(buf1);
	buf1 = str_replace(buf2, "26", "3");
	free(buf2);

	int16_t deplX = 0, deplY = 0;
	int16_t nbrDirrectionDonne = strlen(buf1);

	while (k < nbrDirrectionDonne && k < TAILLE_CANNE_A_PECHE){
		switch (buf1[k]) {
			case '1':
				deplX+=1;
				deplY-=1;
				break;
			case '2':
				deplX+=1;
				break;
			case '3':
				deplX+=1;
				deplY+=1;
				break;
			case '4':
				deplY-=1;
				break;
			case '5':
				break;
			case '6':
				deplY+=1;
				break;
			case '7':
				deplX-=1;
				deplY-=1;
				break;
			case '8':
				deplX-=1;
				break;
			case '9':
				deplX=1;
				deplY+=1;
				break;
			default:
				printf("Error, la direction du pecheur doit être un nombre entre 1 et 9 compris\n");
				free(buf1);
				return;
		}
		++k;
	}
	free(buf1);

	ElementAnimal* e;

	if ((double)This->caseParent->posX+deplX < 0 || This->caseParent->posX+deplX > This->caseParent->g->Taille-1 || (double)This->caseParent->posY+deplY < 0 || This->caseParent->posY+deplY > This->caseParent->g->Taille-1){
		return;
	}
	Case *casePeche;
	casePeche=&This->caseParent->g->tab[This->caseParent->posX+deplX][This->caseParent->posY+deplY];
	if (casePeche->liste->HasAnAnimal(casePeche->liste)){
		e=(ElementAnimal*)casePeche->liste->getAnimal(casePeche->liste);
		if (This->peutPecher(This, e->type) == True){
			This->sac+=e->constantes->taille;
			e->caseParent->liste->deleteElement(e->caseParent->liste, (Element*)e);
		}
	}
}

void ElementPecheur_pecheParCanneSDL(ElementPecheur *This, int16_t x, int16_t y)
{
	if (x < 0 || x > (double)This->caseParent->g->Taille-1 || y < 0 || y > (double)This->caseParent->g->Taille-1)
		return;
	int16_t deplX = (double)This->caseParent->posX-x;
	int16_t deplY = (double)This->caseParent->posY-y;
	if (deplX < 0)
		deplX*=-1;
	if (deplY < 0)
		deplY*=-1;
	if (deplX > TAILLE_CANNE_A_PECHE || deplY > TAILLE_CANNE_A_PECHE){
		return;
	}
	ElementAnimal *e;
	Case *casePeche;
	casePeche=&This->caseParent->g->tab[x][y];
	if (casePeche->liste->HasAnAnimal(casePeche->liste)){
		e=(ElementAnimal*)casePeche->liste->getAnimal(casePeche->liste);
		if (This->peutPecher(This, e->type) == True){
			This->sac+=e->constantes->taille;
			e->caseParent->liste->deleteElement(e->caseParent->liste, (Element*)e);
		}
	}
}

Bool ElementPecheur_peutPecher(ElementPecheur *This, Type t)
{
	if (This->listeDePeche->Contain(This->listeDePeche, t) == True){
			return True;
		}
	return False;
}


void ElementPecheur_pecheParFilet(ElementPecheur *This, char *buffer)
{
	int16_t  k = 0;
	int16_t i, j;
	char *buf1, *buf2;

	buf1 = str_replace(buffer, "68", "9");
	buf2 = str_replace(buf1, "86", "9");
	free(buf1);
	buf1 = str_replace(buf2, "86", "9");
	free(buf2);
	buf2 = str_replace(buf1, "48", "7");
	free(buf1);
	buf1= str_replace(buf2, "84", "7");
	free(buf2);
	buf2 = str_replace(buf1, "42", "1");
	free(buf1);
	buf1 = str_replace(buf2, "24", "1");
	free(buf2);
	buf2 = str_replace(buf1, "62", "3");
	free(buf1);
	buf1 = str_replace(buf2, "26", "3");
	free(buf2);

	int16_t deplX = 0, deplY = 0;
	int16_t nbrDirrectionDonne = strlen(buf1);

	while (k < nbrDirrectionDonne && k < DISTANCE_LANCE_FILET){
		switch (buf1[k]) {
			case '1':
				deplX+=1;
				deplY-=1;
				break;
			case '2':
				deplX+=1;
				break;
			case '3':
				deplX+=1;
				deplY+=1;
				break;
			case '4':
				deplY-=1;
				break;
			case '5':
				break;
			case '6':
				deplY+=1;
				break;
			case '7':
				deplX-=1;
				deplY-=1;
				break;
			case '8':
				deplX-=1;
				break;
			case '9':
				deplX=1;
				deplY+=1;
				break;
			default:
				printf("Error, la direction du pecheur doit être un nombre entre 1 et 9 compris\n");
				free(buf1);
				return;
		}
		++k;
	}
	free(buf1);



	ElementAnimal* e;
	Case*** MatriceAccessiblePeche= NULL;
	MatriceAccessiblePeche=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX+deplX, This->caseParent->posY+deplY, This->tailleFilet);
	MatriceAccessiblePeche[This->tailleFilet][This->tailleFilet]=&(This->caseParent->g->tab[This->caseParent->posX+deplX][This->caseParent->posY+deplX]);
	for(i=0;i<2*This->tailleFilet+1.0;++i){
		for(j=0;j<2*This->tailleFilet+1.0;++j){
			if (MatriceAccessiblePeche[i][j] != NULL) {
				if (MatriceAccessiblePeche[i][j]->liste->HasAnAnimal(MatriceAccessiblePeche[i][j]->liste)){
					e=(ElementAnimal*)MatriceAccessiblePeche[i][j]->liste->getAnimal(MatriceAccessiblePeche[i][j]->liste);
					if (This->peutPecher(This, e->type) == True){
						This->sac+=e->constantes->taille;
						e->caseParent->liste->deleteElement(e->caseParent->liste, (Element*)e);
					}
				}
			}
		}
	}
	for (i=0; i<2*This->tailleFilet+1.0;++i){
		free(MatriceAccessiblePeche[i]);
	}
	free(MatriceAccessiblePeche);
}

void ElementPecheur_pecheParFiletSDL(ElementPecheur *This, int16_t x, int16_t y)
{
	if (x < 0 || x > (double)This->caseParent->g->Taille-1 || y < 0 || y > (double)This->caseParent->g->Taille-1)
		return;
	int16_t deplX = (double)This->caseParent->posX-x;
	int16_t deplY = (double)This->caseParent->posY-y;
	if (deplX < 0)
		deplX*=-1;
	if (deplY < 0)
		deplY*=-1;
	if (deplX > TAILLE_CANNE_A_PECHE || deplY > TAILLE_CANNE_A_PECHE){
		return;
	}

	ElementAnimal* e;
	Case*** MatriceAccessiblePeche= NULL;
	MatriceAccessiblePeche=This->caseParent->g->getMatriceVoisins(This->caseParent->g, x, y, This->tailleFilet);
	MatriceAccessiblePeche[This->tailleFilet][This->tailleFilet]=&(This->caseParent->g->tab[x][y]);
	for(deplX=0;deplX<2*This->tailleFilet+1.0;++deplX){
		for(deplY=0;deplY<2*This->tailleFilet+1.0;++deplY){
			if (MatriceAccessiblePeche[deplX][deplY] != NULL) {
				if (MatriceAccessiblePeche[deplX][deplY]->liste->HasAnAnimal(MatriceAccessiblePeche[deplX][deplY]->liste)){
					e=(ElementAnimal*)MatriceAccessiblePeche[deplX][deplY]->liste->getAnimal(MatriceAccessiblePeche[deplX][deplY]->liste);
					if (This->peutPecher(This, e->type) == True){
						This->sac+=e->constantes->taille;
						e->caseParent->liste->deleteElement(e->caseParent->liste, (Element*)e);
					}
				}
			}
		}
	}
	for (deplX=0; deplX<2*This->tailleFilet+1.0;++deplX){
		free(MatriceAccessiblePeche[deplX]);
	}
	free(MatriceAccessiblePeche);
}


Bool ElementPecheur_deplacement(ElementPecheur *This, char direction)
{
	int16_t deplX = 0, deplY = 0;
	switch (direction) {
		case '1':
			deplX=1;
			deplY=-1;
			break;
		case '2':
			deplX=1;
			break;
		case '3':
			deplX=1;
			deplY=1;
			break;
		case '4':
			deplY=-1;
			break;
		case '5':
			break;
		case '6':
			deplY=1;
			break;
		case '7':
			deplX=-1;
			deplY=-1;
			break;
		case '8':
			deplX=-1;
			break;
		case '9':
			deplX=-1;
			deplY=1;
			break;
		default:
			printf("Error, la direction du pecheur doit être un nombre entre 1 et 9 compris\n");
			return False;
	}
	if ((double)This->caseParent->posX+deplX < 0 || This->caseParent->posX+deplX > This->caseParent->g->Taille-1 || (double)This->caseParent->posY+deplY < 0 || This->caseParent->posY+deplY > This->caseParent->g->Taille-1){
		// Le joueur essaie de sortir de la grille
		// lancer cri de whilem
		return False;
	}
	Case *caseDeplacement;
	caseDeplacement = &This->caseParent->g->tab[This->caseParent->posX+deplX][This->caseParent->posY+deplY];
	if ((caseDeplacement->liste->HasAPont(caseDeplacement->liste) == 1 || caseDeplacement->liste->HasDirt(caseDeplacement->liste) == 1 || (This->caseParent->liste->HasAPont(This->caseParent->liste) == 0 && This->caseParent->liste->HasDirt(This->caseParent->liste) == 0)) && caseDeplacement->liste->HasAPecheur(caseDeplacement->liste) == 0){
		//Il y a un pond et pas de pecheur sur ce pont, on peut s'y déplacer
		// ou alors on est déja dans l'eau donc on peux se déplacer de partout
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, This->caseParent->posX+deplX, This->caseParent->posY+deplY);
		return True;
	}
	else {
		//pas possible
		return False;
	}
}


Bool ElementPecheur_construirePont(ElementPecheur *This, char direction)
{
	int16_t deplX = 0, deplY = 0;
	switch (direction) {
		case '1':
			deplX=1;
			deplY=-1;
			break;
		case '2':
			deplX=1;
			break;
		case '3':
			deplX=1;
			deplY=1;
			break;
		case '4':
			deplY=-1;
			break;
		case '5':
			break;
		case '6':
			deplY=1;
			break;
		case '7':
			deplX=-1;
			deplY=-1;
			break;
		case '8':
			deplX=-1;
			break;
		case '9':
			deplX=-1;
			deplY=1;
			break;
		default:
			printf("Error, la direction du pecheur doit être un nombre entre 1 et 9 compris\n");
			return False;
	}
	if ((double)This->caseParent->posX+deplX < 0 || This->caseParent->posX+deplX > This->caseParent->g->Taille-1 || (double)This->caseParent->posY+deplY < 0 || This->caseParent->posY+deplY > This->caseParent->g->Taille-1){
		// Le joueur essaie de construire en dehors de la ligne
		// lancer cri de whilem
		return False;
	}
	Case *caseCreationDuPont;
	caseCreationDuPont = &This->caseParent->g->tab[This->caseParent->posX+deplX][This->caseParent->posY+deplY];
	if (This->sac >= COUT_POSE_PONT && caseCreationDuPont->liste->HasAPont(caseCreationDuPont->liste) == 0 && caseCreationDuPont->liste->HasDirt(caseCreationDuPont->liste) == 0 && (caseCreationDuPont->liste->HasAnAnimal(caseCreationDuPont->liste) == 0 || (caseCreationDuPont->liste->HasAnAnimal(caseCreationDuPont->liste) == 1 && ((ElementAnimal*)caseCreationDuPont->liste->getAnimal(caseCreationDuPont->liste))->constantes->taille < This->caseParent->g->TailleMaxSousPont))){
		//Il y a un pond et pas de pecheur sur ce pont, on peut s'y déplacer
		caseCreationDuPont->liste->Push(caseCreationDuPont->liste, (Element*)New_ElementPont(caseCreationDuPont));
		This->sac-=COUT_POSE_PONT;
		return True;
	}
	else {
		return False;
	}
}


void ElementPecheur_mourir(ElementPecheur *This)
{
    printf("%s\n", __FUNCTION__);
	This->caseParent->g->reinitPecheur(This->caseParent->g, (Element*)This);
}


void ElementPecheur_reinitSac(ElementPecheur *This)
{
	This->sac=COUT_POSE_PONT*5;
}
