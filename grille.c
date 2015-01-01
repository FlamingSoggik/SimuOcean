#include "grille.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#define EAU "\033[00;44m"
#define ANIMAL "\033[00;41m"
#define PONT "\033[48;5;130m"
#define PECHEUR "\033[00;47m"
#define NORMAL "\033[00m"
#define GRAS "\033[01m"

Grille Grille_Create(int Taille){
	Grille g;
	Grille_Init(&g, Taille);
	g.Free=Grille_Free;
	return g;
}

void Grille_Init(Grille *This, unsigned int Taille){
	This->Clear = Grille_Clear;
	This->Print = Grille_Print;
	This->Taille=Taille;
	This->TailleMaxSousPont=10;
	This->TourCourant = 0;
	This->moveFromTo=Grille_moveFromTo;
	This->tab=malloc(sizeof(Case*)*Taille);
    unsigned int i,j;
	for (i=0;i<Taille;++i){
		This->tab[i]=malloc(sizeof(Case)*Taille);
	}
	for(i=0;i<Taille;++i){
		for(j=0; j<Taille; ++j){
			This->tab[i][j]= Case_Create(This, i, j);
		}
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
}


/*void Grille_Print(struct Grille *This){
	unsigned int i, j;
    for(i=0;i<This->Taille;++i)
        printf("=====" NORMAL);
	printf("=\n");
    for(i=0;i<This->Taille;++i){
		printf("|");
		for(j=0; j<This->Taille; ++j){
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
		for (j=0; j<This->Taille; j++)
			printf("—————");
		printf("—\n");
	}
}

*/

void Grille_Print(struct Grille *This){

    const long PROP_FENETRE=95; // (1-100) Proportion de la grille par rapport à la fenetre du jeu.
    const int NBR_CASES=This->Taille; // Largeur de la grille

    /* Initialisation des variables nécessaires */
    SDL_Surface *ecran = NULL ,*fenetre = NULL, *curseur1 = NULL, *curseur2 = NULL;//, *boite = NULL;
    SDL_Event event;
    int continuer=1;
    int select_curseur2=0;
    int i=0; int j=0;
    SDL_Surface *carre[20][20];
    SDL_Rect pos_case;

    /* Initialisation de la SDL */
    SDL_Init(SDL_INIT_VIDEO);
    putenv("SDL_VIDEO_WINDOW_POS=center"); // Centrage

    /* On récupère la taille de l'écran */
    const SDL_VideoInfo *videoInfo;
    videoInfo=SDL_GetVideoInfo();
    int ScreenW=videoInfo->current_w*0.9;
    int ScreenH=videoInfo->current_h*0.9;


    ecran = SDL_SetVideoMode(ScreenW, ScreenH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    /* Test d'erreur d'affichage*/
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Nom de la fenetre */
    SDL_WM_SetCaption("Life Game !", NULL);

    /* Creation et Affichage des elements */

    /* Gestion de la grille */

    int taille_fenetre=ScreenH*PROP_FENETRE/100; //Par défaut
    int taille_case = taille_fenetre/NBR_CASES;
    if (taille_fenetre-taille_case*NBR_CASES <= NBR_CASES-1)
        taille_case--;
    taille_fenetre=taille_case*NBR_CASES+NBR_CASES-1;

        /*Fenetre (equivalent de la grille)*/

    fenetre = SDL_CreateRGBSurface(SDL_HWSURFACE, taille_fenetre, taille_fenetre, 32, 0, 0, 0, 0);
    SDL_FillRect(fenetre, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_Rect pos_fenetre;
    pos_fenetre.x=(ScreenH-taille_fenetre)/2;
    pos_fenetre.y=(ScreenH-taille_fenetre)/2;
        /*Curseur1*/
    curseur1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 100/*Attentionsiçachange, changer position PARTOUT*/, 2, 32, 0, 0, 0, 0);
    SDL_FillRect(curseur1, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_Rect pos_curseur1;
    pos_curseur1.x=ScreenH + (ScreenW-ScreenH)/2 - 50;
    pos_curseur1.y=ScreenH/10;
        /*Curseur2*/
    curseur2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 12, 32, 32, 0, 0, 0, 0);
    SDL_FillRect(curseur2, NULL, SDL_MapRGB(ecran->format, 104, 111, 140));
    SDL_Rect pos_curseur2;
    pos_curseur2.x=pos_curseur1.x+50-6;
    pos_curseur2.y=pos_curseur1.y-15;






    while(continuer)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                continuer=0;
                break;

            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;
                    }
                break;

            case SDL_MOUSEBUTTONDOWN: /* Moment de pression */
                if ((pos_curseur2.x<=event.button.x) && (event.button.x<=pos_curseur2.x+12) && (pos_curseur2.y<=event.button.y) && (event.button.y<=pos_curseur2.y+32))
                    select_curseur2=1;
                break;

            case SDL_MOUSEBUTTONUP:
                select_curseur2=0;
                break;

            case SDL_MOUSEMOTION:
                if (select_curseur2 && (event.motion.x >= pos_curseur1.x) && (event.motion.x <= pos_curseur1.x+100)) // Movement du curseur2.
                {
                    pos_curseur2.x=event.motion.x-6;
                }
            default: break ;
         }

    /* On efface l'écran */
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));

    /* Tous les BLIT */
    SDL_BlitSurface(fenetre, NULL, ecran, &pos_fenetre);
    SDL_BlitSurface(curseur1, NULL, ecran, &pos_curseur1);
    SDL_BlitSurface(curseur2, NULL, ecran, &pos_curseur2);


    /* Opérations */


    for(i=0; i<NBR_CASES; i++){
        for(j=0; j<NBR_CASES; j++){

            carre[i][j]=SDL_CreateRGBSurface(SDL_HWSURFACE, taille_case, taille_case, 32, 0,0,0,0);
            pos_case.x=(j*taille_case)+j+pos_fenetre.x;
            pos_case.y=(i*taille_case)+i+pos_fenetre.y;

            if (This->tab[i][j].liste->HasAPecheur(This->tab[i][j].liste)) {
                if (This->tab[i][j].liste->HasAPont(This->tab[i][j].liste)){
                    SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 214, 0, 0)); // Violet pécheur
                }
                else {
                    SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 138, 20, 79));// Violet pécheur
                }
            }
            else if (This->tab[i][j].liste->HasAPont(This->tab[i][j].liste)){
                    SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 214, 0, 0)); // Gris pont
            }
            else if (This->tab[i][j].liste->HasAnAnimal(This->tab[i][j].liste)){
                SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 134, 160, 45)); // Vert poisson
            }
            else {
                SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 204, 255, 229)); //Bleu mer
            }

            /*if(i==5)
                 SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 134, 160, 45)); // Vert poisson*/
            SDL_BlitSurface(carre[i][j], NULL, ecran, &pos_case);
        }
    }








    /* Mise à jour de l'écran */
    SDL_Flip(ecran);

    } // End of while
printf("\nTaille de la case : %d\n", taille_case);
    SDL_FreeSurface(fenetre);
    SDL_FreeSurface(curseur1);
    SDL_FreeSurface(curseur2);
    for(i=0; i<NBR_CASES; i++)
        for(j=0; j<NBR_CASES; j++)
            SDL_FreeSurface(carre[i][j]);
    SDL_Quit();

}













void Grille_Free(struct Grille *This){
	This->Clear(This);
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

		for(j=posY-i+1,k=1;j<(double)posX+i-1+1;++j,++k){
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
