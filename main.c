#include <stdio.h>
#include "element.h"
#include "elementanimal.h"
#include "grille.h"
#include <stdlib.h>
#include "affichage.h"

#define EAU "\033[00;44m"
#define ANIMAL "\033[00;41m"
#define PONT "\033[48;5;130m"
#define PECHEUR "\033[00;47m"
#define NORMAL "\033[00m"
#define GRAS "\033[01m"


int main(void)
{

	Grille *g = New_Grille(10);
//		METTRE_UN_NOM_DE_FONCTION_ET_LE_CHANGER_DANS_LE_FICHIER(&g);
	g->Print(g);
	g->tab[2][2].liste->Push(g->tab[2][2].liste, (Element*)New_ElementAnimal(&(g->tab[2][2]), PYRANHA));
	g->tab[1][1].liste->Push(g->tab[1][1].liste, (Element*)New_ElementAnimal(&(g->tab[1][1]), BAR));


	g->Print(g);
	ElementAnimal* e = (ElementAnimal*)g->tab[2][2].liste->getAnimal(g->tab[2][2].liste);
	e->predation(e);


	g->Print(g);

	g->Free(g);



//	//Constructction d'un tableau d'élément
//	Grille g = Grille_Create(10);
//	g.Print(&g);
////Test de la demande de matrice de mouvement
//	Case*** mattmp;
//	int i, j;
//	mattmp=Grille_getMatriceVoisins(&g, 1,1,2);
//	for(i=0; i<2*2+1.0; ++i){
//		for(j=0; j<2*2+1.0; ++j){
//			if (mattmp[i][j] == NULL)
//				printf(" NN |");
//			else {
//				if (mattmp[i][j]->liste->HasAPecheur(mattmp[i][j]->liste)) {
//					if (mattmp[i][j]->liste->HasAPont(mattmp[i][j]->liste)){
//						printf(" " PONT " " PECHEUR " " NORMAL " |");
//					}
//					else {
//						printf(" " EAU " " PECHEUR " " NORMAL " |");
//					}
//				}
//				else if (mattmp[i][j]->liste->HasAPont(mattmp[i][j]->liste)){
//					printf(" " PONT "  " NORMAL " |");
//				}
//				else if (mattmp[i][j]->liste->HasAnAnimal(mattmp[i][j]->liste)){
//					printf(" " ANIMAL "  " NORMAL " |");
//				}
//				else {
//					printf(" " EAU "  " NORMAL " |");
//				}
//			}
//		}

//		printf("\n");
//		for (j=0; j<2*2+1.0; j++)
//			printf("—————");
//		printf("—\n");
//	}
//	for (i=0; i<5;++i){
//		free(mattmp[i]);
//	}
//	free(mattmp);
//	g.Free(&g);
/////////////////////////////////////////////////////////////////////////////////////////

//	Element *tabElement[10][10];
//	int i, j, k=0, nbelem = 0;
//	for(i=0;i<10;++i){
//		for(j=0;j<10;++j){
//			if(k == 0){
//				tabElement[i][j]=New_Element();
//				++nbelem;
//				k=k+1%3;
//			}else if (k==1){
//				tabElement[i][j]=New_ElementAnimal_v12(15);
//				++nbelem;
//				k=k+1%3;
//			}
//			else {
//				tabElement[i][j]=New_ElementAnimal();
//				++nbelem;
//				k=k+1%3;
//			}
//		tabElement[i][j]=New_Element();
//		}
//	}
//	printf("%d\n", nbelem);
//	for(i=0;i<10;++i){
//		for(j=0;j<10;++j){
//			printf("%d\n", tabElement[i][j]->id);
//		}
//	}

///Test des fonctions de listeEmem --> GOOD !
//	Case c = Case_Create(NULL, 0, 0);
//	Element* e=(Element*)New_ElementAnimal(&c, BAR);
//	Element* d=(Element*)New_ElementAnimal(&c, PYRANHA);
//	c.liste->Push(c.liste, e);
//	c.liste->Push(c.liste, d);
//	c.liste->Print(c.liste);
//	Element* f = c.liste->getAnimal(c.liste);
//	c.liste->deleteElement(c.liste, f);
//	c.liste->Print(c.liste);

//	c.Free(&c);
/////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}

