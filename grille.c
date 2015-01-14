#include "grille.h"
#include <stdlib.h>
#include <stdio.h>
#include "elementanimal.h"
#include "element.h"
#include <time.h>

#define EAU "\033[00m"				//NOIR
#define PVOID "\033[48;5;1m"		//ROUGE FONCE
#define PPLANCTON "\033[48;5;2m"	//VERT CLAIR
#define PCORAIL "\033[48;5;9m"		//ROUGE CLAIR
#define PBAR "\033[48;5;184m"		//MARON-JAUNE
#define PTHON "\033[48;5;8m"		//GRIS
#define PPOLLUTION "\033[48;5;7m"	//GRIS TRES CLAIR
#define PPYRANHA "\033[48;5;90m"	//VIOLET
#define PREQUIN "\033[48;5;18m"		//BLEU FONCE
#define PORQUE "\033[48;5;27m"		//BLEU CLAIR
#define PBALEINE "\033[48;5;22m"	//VERT FONCE
#define PPONT "\033[48;5;130m"		//MARRON
#define PPECHEUR "\033[48;5;48m"	//VERT-BLEU
#define NORMAL "\033[00m"			//NOIR
#define PGRAS "\033[01m"

Grille Grille_Create(int Taille){
	Grille g;
	Grille_Init(&g, Taille);
	g.Free=Grille_Free;
	return g;
}

void Grille_Init(Grille *This, unsigned int Taille){
	static int premierpassage = 1;
	if (premierpassage == 1){
		srand(time(NULL));
		defineConstant();
		premierpassage = 0;
	}
	unsigned int i,j;
	This->Clear = Grille_Clear;
	This->Print = Grille_Print;
	This->Taille=Taille;
	This->TailleMaxSousPont=10;
	This->TourCourant = 0;
	This->listePredationInitialise = 0;
	This->moveFromTo=Grille_moveFromTo;
	This->getMatriceVoisins=Grille_getMatriceVoisins;
	This->faireTour=Grille_faireTour;

	This->tab=malloc(sizeof(Case*)*Taille);
	for (i=0;i<Taille;++i){
		This->tab[i]=malloc(sizeof(Case)*Taille);
	}
	for(i=0;i<Taille;++i){
		for(j=0; j<Taille; ++j){
			This->tab[i][j]= Case_Create(This, i, j);
		}
	}

	remplirListePredation(This);
	int nbrCase = Taille*Taille;
	int nbrEspece = 0;
	int comptelemespece = 0;
	Type compteurTypeEspece = PLANCTON;


	//Désactivé pour tester le pecheur
	while (compteurTypeEspece < PONT){
		comptelemespece = 0;
		switch(compteurTypeEspece){
			case PLANCTON:
				nbrEspece = 40*nbrCase/100;
				break;
			case CORAIL:
				nbrEspece = 2*nbrCase/100;
				break;
			case BAR:
				nbrEspece = 5*nbrCase/100;
				break;
			case THON:
				nbrEspece = 5*nbrCase/100;
				break;
			case PYRANHA:
				nbrEspece = 2*nbrCase/100;
				break;
			case REQUIN:
				nbrEspece = 4*nbrCase/100;
				break;
			case ORQUE:
				nbrEspece = 2*nbrCase/100;
				break;
			case BALEINE:
				nbrEspece = 5*nbrCase/100;
				break;
			default:
				nbrEspece = 0;
				break;
		}
		while (comptelemespece != nbrEspece){
			i = rand()%Taille;
			j = rand()%Taille;
			if (This->tab[i][j].liste->HasAnAnimal(This->tab[i][j].liste) == 0){
				This->tab[i][j].liste->Push(This->tab[i][j].liste, (Element*)New_ElementAnimal(&This->tab[i][j], compteurTypeEspece));
				++comptelemespece;
			}
		}
		++compteurTypeEspece;
	}
}

void Grille_Clear(struct Grille *This){
	unsigned int i, j;
	for(i=0;i<This->Taille;++i){
		for(j=0; j<This->Taille; ++j){
			This->tab[i][j].Free(&(This->tab[i][j]));
		}
	}
	for(i=0; i<This->Taille; ++i){
		free(This->tab[i]);
	}
	free(This->tab);
	viderListePredation(This);
}

void Grille_Print(struct Grille *This){
	printf(EAU "EAU" NORMAL " " PVOID "RIEN(erreur)" NORMAL " " PPLANCTON "PLANCTON" NORMAL " " PCORAIL "CORAIL" NORMAL " " PBAR "BAR" NORMAL " " PTHON "THON" NORMAL " " PPOLLUTION "POLLUTION" NORMAL " " PPYRANHA "PYRANHA" NORMAL " " PREQUIN "PREQUIN" NORMAL " " PORQUE "ORQUE" NORMAL " " PBALEINE "BALEINE" NORMAL "\n");
	unsigned int i, j;
	for(i=0;i<This->Taille;++i)
		printf("=====" NORMAL);
	printf("=\n");
	for(i=0;i<This->Taille;++i){
		printf("|");
		for(j=0; j<This->Taille; ++j){
			if (This->tab[i][j].liste->HasAPecheur(This->tab[i][j].liste)) {
				if (This->tab[i][j].liste->HasAPont(This->tab[i][j].liste)){
					printf(" " PPONT " " PPECHEUR " " NORMAL " |");
				}
				else {
					printf(" " EAU " " PPECHEUR " " NORMAL " |");
				}
			}
			else if (This->tab[i][j].liste->HasAPont(This->tab[i][j].liste)){
				printf(" " PPONT "  " NORMAL " |");
			}
			else if (This->tab[i][j].liste->HasAnAnimal(This->tab[i][j].liste)){
				switch(This->tab[i][j].liste->getAnimal(This->tab[i][j].liste)->type){
					case VOID:
						printf(" " PVOID "  " NORMAL " |");
						break;
					case PLANCTON:
						printf(" " PPLANCTON "  " NORMAL " |");
						break;
					case CORAIL:
						printf(" " PCORAIL "  " NORMAL " |");
						break;
					case BAR:
						printf(" " PBAR "  " NORMAL " |");
						break;
					case THON:
						printf(" " PTHON "  " NORMAL " |");
						break;
					case POLLUTION:
						printf(" " PPOLLUTION "  " NORMAL " |");
						break;
					case PYRANHA:
						printf(" " PPYRANHA "  " NORMAL " |");
						break;
					case REQUIN:
						printf(" " PREQUIN "  " NORMAL " |");
						break;
					case ORQUE:
						printf(" " PORQUE "  " NORMAL " |");
						break;
					case BALEINE:
						printf(" " PBALEINE "  " NORMAL " |");
						break;
					default:
						printf(" " NORMAL "ER" NORMAL " |");
						break;
				}
			}
			else {
				printf(" " EAU "  " NORMAL " |");
			}
		}
		printf("\n");
		if (i == This->Taille-1){
			for (j=0; j<This->Taille; j++)
				printf("=====");
			printf("=\n");
		}
		else {
			for (j=0; j<This->Taille; j++)
				printf("—————");
			printf("—\n");
		}
	}
}

void Grille_Free(struct Grille *This){
	This->Clear(This);
}

void Grille_New_Free(struct Grille *This){
	if(This != NULL) This->Clear(This);
	free(This);
	puts("Grille detruite\n");
}

Case*** Grille_getMatriceVoisins(Grille *This, unsigned int posX, unsigned int posY, unsigned int nbSauts)
{
//printf("Taille de la grille : %d\n", This->Taille);
	unsigned int taille=2*nbSauts+1;
//printf("Taille du nouveau tableau : %d\n", taille);
	//Coordonnées de la case du milieu du nouveau tableau
	unsigned int cMNT = nbSauts;
//printf("Centre de la Matrice à renvoyer : %d\n", cMNT);
	Case* **tableau = malloc(sizeof(Case**)*taille);
	if (tableau == NULL){
		puts("ERROR creating matrice in detMatriceVoicins");
		return NULL;
	}
	unsigned int i;
	for(i=0;i<taille;++i){
		tableau[i] = malloc(sizeof(Case*)*taille);
	}
	tableau[cMNT][cMNT]=NULL;
	int j, k;
	for(i=nbSauts;i>0;--i){
//printf("Nous somme dans la boucle pour le saut de %d cases\n", i);
		for(j=posX-i,k=0;j<(double)posX+i+1;++j,++k){
//printf("J, qui correspond à la valeur de x qui varie afin de completer la première et dernière ligne vaut %d\n", j);
			if (j < 0 || j > (double)This->Taille-1 || (double)posY-i < 0 || (double)posY-i > This->Taille-1){
//printf("La position (ligne superieure) évaluée est en dehors de la Grille ([%d][%d]), la valeur null est placée dans la case [%d][%d]\n", j, posY-i, cMNT-i+k, cMNT-i);
				tableau[cMNT-i+k][cMNT-i]= NULL;
			} else {
//printf("La position (ligne superieure) évaluée est dans la Grille, l'adresse de la case correspondante ([%d][%d]) est placée dans la case [%d][%d]\n", j, posY-i, cMNT-i+k, cMNT-i);
				tableau[cMNT-i+k][cMNT-i]=&This->tab[j][posY-i];
			}
//printf("\n\n");
			if (j < 0 || j > (double)This->Taille-1 || (double)posY+i < 0 || (double)posY+i > This->Taille-1){
//printf("La position (ligne inferieure) évaluée est en dehors de la Grille ([%d][%d]), la valeur null est placée dans la case [%d][%d]\n", j, posY+i, cMNT-i+k, cMNT+i);
				tableau[cMNT-i+k][cMNT+i]= NULL;
			} else {
//printf("La position (ligne inferieure) évaluée est dans la Grille, l'adresse de la case correspondante ([%d][%d]) est placée dans la case [%d][%d]\n\n\n\n", j, posY+i, cMNT-i+k, cMNT+i);
				tableau[cMNT-i+k][cMNT+i]=&This->tab[j][posY+i];
			}
		}

		for(j=posY-i+1,k=1;j<(double)posY+i-1+1;++j,++k){
//printf("J, qui correspond à la valeur de y qui varie afin de completer la première et dernière colonne vaut %d\n", j);
			if (j < 0 || j > (double)This->Taille-1 || (double)posX-i < 0 || (double)posX-i > This->Taille-1){
//printf("La position (ligne superieure) évaluée est en dehors de la Grille ([%d][%d]), la valeur null est placée dans la case [%d][%d]\n", posX-i, j, cMNT-i, cMNT-i+k);
				tableau[cMNT-i][cMNT-i+k]= NULL;
			} else {
//printf("La position (ligne superieure) évaluée est dans la Grille, l'adresse de la case correspondante ([%d][%d]) est placée dans la case [%d][%d]\n", posX-i, j, cMNT-i, cMNT-i+k);
				tableau[cMNT-i][cMNT-i+k]=&This->tab[posX-i][j];
			}
//printf("\n\n");
			if (j < 0 || j > (double)This->Taille-1 || (double)posX+i < 0 || (double)posX+i > This->Taille-1){
//printf("La position (ligne inferieure) évaluée est en dehors de la Grille ([%d][%d]), la valeur null est placée dans la case [%d][%d]\n", posX+i, j, cMNT+i, cMNT-i+k);
				tableau[cMNT+i][cMNT-i+k]= NULL;
			} else {
//printf("La position (ligne inferieure) évaluée est dans la Grille, l'adresse de la case correspondante ([%d][%d]) est placée dans la case [%d][%d]\n\n\n\n", posX+i, j, cMNT+i, cMNT-i+k);
				tableau[cMNT+i][cMNT-i+k]=&This->tab[posX+i][j];
			}
		}


	}
	return tableau;
}

void Grille_moveFromTo(Grille *This, Element *elem, unsigned int posX, unsigned int posY)
{
	This->tab[elem->caseParent->posX][elem->caseParent->posY].liste->remove(This->tab[elem->caseParent->posX][elem->caseParent->posY].liste, elem);
	This->tab[posX][posY].liste->Push(This->tab[posX][posY].liste, elem);
	elem->caseParent=&(This->tab[posX][posY]);
}

void Grille_faireTour(Grille *This){
	unsigned int i, j;
	ElementAnimal *e;
	for (i=0; i<This->Taille; ++i){
		for (j=0; j<This->Taille; ++j){
			if (This->tab[i][j].liste->HasAnAnimal(This->tab[i][j].liste)){
				e=(ElementAnimal*)This->tab[i][j].liste->getAnimal(This->tab[i][j].liste);
				if (e->doitJouerCeTour(e) == False)
					continue;
				if (e->survie(e) == False){
					This->tab[i][j].liste->deleteElement(This->tab[i][j].liste, (Element*)e);;
				}
				else {
					e->reproduction(e);
					e->predation(e);
					e->deplacement(e); //<-- Contient le probleme de localisation dans la sous matrice
					e->tour(e);
					e->aFaitSonTour(e);
				}
			}
			e=NULL;
//			This->Print(This);
		}
	}
	for (i=0; i<This->Taille; ++i){
		for (j=0; j<This->Taille; ++j){
			if (This->tab[i][j].liste->HasAnAnimal(This->tab[i][j].liste)){
				e=(ElementAnimal*)This->tab[i][j].liste->getAnimal(This->tab[i][j].liste);
				e->finDuTour(e);
			}
		}
	}
	++This->TourCourant;
}

Grille *New_Grille(int Taille)
{
	Grille* This = malloc(sizeof(Grille));
	if(!This) return NULL;
	Grille_Init(This, Taille);
	This->Free=Grille_New_Free;
	return This;
}
