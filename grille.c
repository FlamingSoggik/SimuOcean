#include "grille.h"
#include <stdlib.h>
#include <stdio.h>

#define EAU "\033[00;44m"
#define ANIMAL "\033[00;41m"
#define PONT "\033[48;5;130m"
#define PECHEUR "\033[00;47m"
#define NORMAL "\033[00m"
#define GRAS "\033[01m"

Grille Grille_Create(){
	Grille g;
	Grille_Init(&g);
	g.Free=Grille_Free;
	return g;
}

void Grille_Init(Grille *This){
	This->Clear = Grille_Clear;
	This->Print = Grille_Print;
	This->tab=malloc(sizeof(Case*)*10);
	int i,j;
	for (i=0;i<10;++i){
		This->tab[i]=malloc(sizeof(Case)*10);
	}
	for(i=0;i<10;++i){
		for(j=0; j<10; ++j){
			This->tab[i][j]= Case_Create();
		}
	}
}

void Grille_Clear(struct Grille *This){
	int i, j;
	for(i=0;i<10;++i){
		for(j=0; j<10; ++j){
			This->tab[i][j].Free(&(This->tab[i][j]));
		}
	}
}

void Grille_Print(struct Grille *This){
	int i, j;
	for(i=0;i<10;++i)
        printf("=====" NORMAL);
	printf("=\n");
	for(i=0;i<10;++i){
		printf("|");
		for(j=0; j<10; ++j){
			if (This->tab[i][j].liste->HasAPecheur(This->tab[i][j].liste)) {
				if (This->tab[i][j].liste->HasAPont(This->tab[i][j].liste)){
					printf(" " PONT " " PECHEUR " " NORMAL " |");
				}
				else {
					printf(" " EAU " " PECHEUR " " NORMAL " |");
				}
			}
			else if (This->tab[i][j].liste->HasAPont(This->tab[i][j].liste)){
				printf(" " PONT "  " NORMAL " |");
			}
			else if (This->tab[i][j].liste->HasAnAnimal(This->tab[i][j].liste)){
				printf(" " ANIMAL "  " NORMAL " |");
			}
			else {
				printf(" " EAU "  " NORMAL " |");
			}
		}
		printf("\n");
		for (j=0; j<10; j++)
			printf("—————");
		printf("—\n");
	}

}
void Grille_Free(struct Grille *This){
	This->Clear(This);
	puts("Grille detruite\n");
}
