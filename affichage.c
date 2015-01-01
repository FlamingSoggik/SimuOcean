#include "affichage.h"
#include <SDL/SDL.h>

void METTRE_UN_NOM_DE_FONCTION_ET_LE_CHANGER_DANS_LE_FICHIER(struct Grille *grill){

	const long PROP_FENETRE=95; // (1-100) Proportion de la grille par rapport à la fenetre du jeu.
	const int NBR_CASES=grill->Taille; // Largeur de la grille

	/* Initialisation des variables nécessaires */
	SDL_Surface *ecran = NULL ,*fenetre = NULL, *curseur1 = NULL, *curseur2 = NULL;//, *boite = NULL;
	SDL_Event event;
	int continuer=1;
	int select_curseur2=0;
	int i=0; int j=0;
//
	SDL_Surface ***carre = malloc(sizeof(SDL_Surface**)*grill->Taille);
	unsigned int k;
	for(k=0;k<grill->Taille;++k){
		carre[k] = malloc(sizeof(Case*)*grill->Taille);
	}
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
						default:
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

			if (grill->tab[i][j].liste->HasAPecheur(grill->tab[i][j].liste)) {
				if (grill->tab[i][j].liste->HasAPont(grill->tab[i][j].liste)){
					SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 214, 0, 0)); // Violet pécheur
				}
				else {
					SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 138, 20, 79));// Violet pécheur
				}
			}
			else if (grill->tab[i][j].liste->HasAPont(grill->tab[i][j].liste)){
					SDL_FillRect(carre[i][j], NULL, SDL_MapRGB(ecran->format, 214, 0, 0)); // Gris pont
			}
			else if (grill->tab[i][j].liste->HasAnAnimal(grill->tab[i][j].liste)){
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
