#include <stdio.h>
#include "element.h"
#include "elementanimal.h"
#include "elementpecheur.h"
#include "elementpont.h"
#include "grille.h"
#include <stdlib.h>
#include "affichage.h"
#include <unistd.h>

#include "stringreplace.h"

int main(int argc, char **argv)
{
	Grille *g;


	int nbpecheurs = 0, tailleGrille=0;
	char interface = -1;
	if (argc < 4){
		printf("Taille d'un coté de la grille carré (30 conseillé): ");
		scanf("%d%*c", &tailleGrille);
		printf("Nombre de pecheurs (0 .. 10) : ");
		scanf("%d%*c", &nbpecheurs);
		printf("Interface Graphique avec/sans (a/s) : ");
		scanf("%c%*c", &interface);
	} else {
		tailleGrille=atoi(argv[1]);
		nbpecheurs=atoi(argv[2]);
		interface=argv[3][0];
	}
	if (tailleGrille > 80){
		tailleGrille = 80;
		printf("La taille maximum de la grille est 80\n");
	}
	switch (interface){
		case 'a' :
			g = New_Grille(tailleGrille, nbpecheurs);
			g=SDL_Print(g);
			g->Free(g);
			break;
		case 's':
			g = New_Grille(tailleGrille, nbpecheurs);
			g->Print(g);
			printf("Lancement du jeu dans 5 secondes. Si la grille ne s'affiche pas correctement, utilisez ctrl+- pour diminuer la taille ou ctrl+maj++ \n");
			sleep(5);
			while(g->TourCourant < 1000){
				g->faireTour(g, 0);
				system("clear");
				g->Print(g);
				usleep(100000);
			}
			g->Free(g);
			break;
		default:printf("Err %c\n", interface);
			return -1;
	}

	return 0;
}

