#include "affichage.h"


void SDL_Print(struct Grille *grill){

	const long PROP_FENETRE=95; // (1-100) Proportion de la grille par rapport à la fenetre du jeu.
	const int NBR_CASES=grill->Taille; // Largeur de la grille

	/* Initialisation des variables nécessaires */
    SDL_Surface **Selected_Type_Case=NULL, *plus=NULL, *moins=NULL,  *ecran = NULL ,*fenetre = NULL, *curseur1 = NULL, *curseur2 = NULL, *boite = NULL;
    TTF_Font *police=NULL;
	SDL_Event event;
	int continuer=1;
	int select_curseur2=0;
    int i=0; int j=0;


    SDLCase ***carre = malloc(sizeof(SDLCase**)*grill->Taille);
	unsigned int k;
	for(k=0;k<grill->Taille;++k){
        carre[k] = malloc(sizeof(SDLCase*)*grill->Taille);
    }


    for(i=0;i<NBR_CASES; ++i){
            for(j=0; j<NBR_CASES; ++j){
                    carre[i][j]= malloc(sizeof(SDLCase));
                    carre[i][j]->srf= NULL;
            }
    }


    SDL_Surface** Tab_Type;
    for(i=0; i<10; i++)
        Tab_Type=(SDL_Surface**)malloc(sizeof(SDL_Surface*)*10);

	/* Initialisation de la SDL */
	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
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



    /*Gestion de la police*/


  //  police=TTF_OpenFont("ma-front.ttf", 40);
  //  TTF_SetFontStyle(police, TTF_STYLE_BOLD);
  //  SDL_Color couleurInconnu = {24,158,158,0};
  //  boite = TTF_RenderText_Blended(police, "123456789", couleurInconnu);



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


        /* Initialisation des cases */


    for(i=0; i<10; i++)
    {
        Tab_Type[i]=Charger(taille_case, ecran, i);
    }





    while(continuer)
    {



while(SDL_PollEvent(&event)){
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
						default: break;
					}
				break;

			case SDL_MOUSEBUTTONDOWN: // Moment de pression
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
			break;




		 }
}

    /* On efface l'écran */
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));

    /* Tous les BLIT */
    SDL_BlitSurface(fenetre, NULL, ecran, &pos_fenetre);
    SDL_BlitSurface(curseur1, NULL, ecran, &pos_curseur1);
    SDL_BlitSurface(curseur2, NULL, ecran, &pos_curseur2);

    /* Opérations */

    plus=Spinner_Print(ecran, 0, ScreenH, ScreenW);
    moins=Spinner_Print(ecran, 1, ScreenH, ScreenW);

    for(i=0; i<NBR_CASES; i++)
        for(j=0; j<NBR_CASES; j++){
            Selected_Type_Case=Select_Type(grill, Tab_Type, i, j);
            Actualiser(carre[i][j], Selected_Type_Case, (j*taille_case+j+pos_fenetre.x), (i*taille_case+i+pos_fenetre.y));
            SDL_BlitSurface((carre[i][j]->srf), NULL, ecran, &(carre[i][j]->pos));
        }






    /* Mise à jour de l'écran */
    SDL_Flip(ecran);




    } // End of while




    /*Fermeture de l'affichage*/

	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(curseur1);
	SDL_FreeSurface(curseur2);
    SDL_FreeSurface(boite);
    SDL_FreeSurface(plus);
    SDL_FreeSurface(moins);

    for(i=0; i<10; i++)
            free(Tab_Type[i]);

    for(k=0;k<grill->Taille;++k)
        free(carre[k]);
    free(carre);

    TTF_CloseFont(police);
    SDL_Quit();
    TTF_Init();
}


SDL_Surface* Charger(int taille_case, SDL_Surface *ecran, int type){

    SDL_Surface *Case;
    Case = SDL_CreateRGBSurface(SDL_HWSURFACE, taille_case, taille_case, 32,0,0,0,0);



    switch (type){

        case 1:
            SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 96, 96, 96));
            break;
        case 2:
            SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
            break;
        default:
            SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 204, 255, 229));
            break;
    }


    return Case;

}

void Actualiser( SDLCase *Case_Tab, SDL_Surface **Case_Type, int absisse, int ordonnee)
{


    Case_Tab->pos.x=absisse;
    Case_Tab->pos.y=ordonnee;
    Case_Tab->srf=*Case_Type;

}

SDL_Surface** Select_Type(struct Grille *grill, SDL_Surface **Tab_Type, int i, int j){



    if (grill->tab[i][j].liste->HasAPont(grill->tab[i][j].liste)){
        return &Tab_Type[1];
    }
    else if (grill->tab[i][j].liste->HasAnAnimal(grill->tab[i][j].liste)){
        return &Tab_Type[2];
        }
    else {
        return &Tab_Type[0];
         }

}

SDL_Surface* Spinner_Print(SDL_Surface *ecran, int Plus_Ou_Moins, int ScreenH, int ScreenW)
{
    int i;
    int Centre_Commandes=(ScreenH +(ScreenW-ScreenH)/2-15); // Le 15 correspond à la largeur des images bmp !
    SDL_Surface *srf;

    if(Plus_Ou_Moins==0)
        {
			srf=Charger_Image("ICONE_plus.bmp", ecran);
            for(i=0; i<7; i++)
                Blit_Image(ecran, srf, (Centre_Commandes + 100), (ScreenH/2 - 100 + 50*i));
        }
    else
        {
            srf=Charger_Image("ICONE_moins.bmp", ecran);
            for(i=0; i<7; i++)
                Blit_Image(ecran, srf, (Centre_Commandes - 100), (ScreenH/2 -100 + 50*i));
        }


    return srf;
}

SDL_Surface* Charger_Image(const char* fic, SDL_Surface* ecran)
{
    SDL_Surface* res;
    SDL_Surface* tmp = SDL_LoadBMP(fic);
    if (tmp==NULL)
    {
        printf("Erreur chargement %s\n",fic);
        exit(-1);
    }
    res = SDL_DisplayFormat(tmp);


   /* Cas d'un carré rouge au lieu de l'image */
   // res = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0,0,0,0);
   // SDL_FillRect(res, NULL, SDL_MapRGB(ecran->format, 255, 0,0));


    SDL_FreeSurface(tmp);
    return res;

}

void Blit_Image(SDL_Surface* ecran,SDL_Surface* srf,int x,int y)
{
    SDL_Rect R;
    R.x = x;
    R.y = y;
    SDL_BlitSurface(srf,NULL,ecran,&R);
}
