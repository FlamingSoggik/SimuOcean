#include <stdio.h>
#include "element.h"
#include "elementanimal.h"
#include "grille.h"
#include <stdlib.h>

int main(void)
{

	//Constructction d'un tableau d'élément
	Grille g = Grille_Create(10);
	g.Print(&g);
	Case*** mattmp;
//	mattmp=Grille_getMatriceVoisins(&g, 1,1,2);
//	int i;
//	for (i=0; i<g.Taille;++i){
//		free(mattmp[0]);
//		free(mattmp);
//	}
	g.Free(&g);

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
	return 0;
}

