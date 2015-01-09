#include "affichage.h"


void SDL_Print(struct Grille *grill){

	const long PROP_FENETRE=95; // (1-100) Proportion de la grille par rapport à la fenetre du jeu.
	const int NBR_CASES=grill->Taille; // Largeur de la grille

	/* Initialisation des variables nécessaires */
    SDL_Surface **Selected_Type_Case=NULL, *plus=NULL, *moins=NULL, *Dev_Icone=NULL,  *ecran = NULL ,*fenetre = NULL, *curseur1 = NULL, *curseur2 = NULL, *boite = NULL;
    TTF_Font *police=NULL, *police_underline=NULL;
	SDL_Event event;
	int continuer=1;
	int select_curseur2=0;
    int i=0; int j=0;
    int Est_Un_Dev =0;
    int Compteur_Tours=0, Refresh_Timer=1;



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
        Tab_Type=(SDL_Surface**)malloc(sizeof(SDL_Surface*)*11);




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


  police=TTF_OpenFont("ma-front.ttf", 30);
  police_underline=TTF_OpenFont("ma-front.ttf", 30);
  TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
  TTF_SetFontStyle(police_underline, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);

  SDL_Surface** Legendes_Surface;
      Legendes_Surface=(SDL_Surface**)malloc(sizeof(SDL_Surface*)*11);

      Legendes_Surface=Legendes_Print(Legendes_Surface, police);



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
    pos_curseur2.x=pos_curseur1.x-6;
	pos_curseur2.y=pos_curseur1.y-15;
        /*DevMode*/
    Dev_Icone=Charger_Image("ICONE_moins.bmp", ecran);







        /* Initialisation des cases */


    for(i=0; i<11; i++)
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
                        case SDLK_F5:
                            i=grill->Taille;
                            Grille_Init(grill, i);
                            break;
                        case SDLK_SPACE:
                            if (Refresh_Timer>=95) pos_curseur2.x=pos_curseur1.x+50-6;
                            else if (pos_curseur2.x == (pos_curseur1.x+50-6)) pos_curseur2.x=pos_curseur1.x-6;
                            else pos_curseur2.x=pos_curseur1.x+100-6;
                            break;


//SDL_Surface** Select_Legende(SDL_Surface** Legendes_Surface, TTF_Font* police, int selected)
//    for (i=0; i<11; i++)
  //       Blit_Image(ecran, Legendes_Surface[i], (ScreenH-40), (140+40*i));
                        default: break;
                    }
                break;

            case SDL_MOUSEBUTTONDOWN: // Moment de pression
                if ((pos_curseur2.x<=event.button.x) && (event.button.x<=pos_curseur2.x+12) && (pos_curseur2.y<=event.button.y) && (event.button.y<=pos_curseur2.y+32))
                    select_curseur2=1;
                if ((ScreenW-45<=event.button.x) && (event.button.x<=ScreenW-45+30) && (15<=event.button.y) && (event.button.y<=15+30))
                { Est_Un_Dev++; Est_Un_Dev=Est_Un_Dev%2; }
                if (Est_Un_Dev)
                    if (((ScreenH-40)<=event.button.x) && (event.button.x<=(ScreenH-40+300)) && ((180)<=event.button.y) && (event.button.y<=585))
                        Legendes_Surface=Select_Legende(Legendes_Surface, police, police_underline, ((event.button.y)-140)/((580-140)/11));
                break;

            case SDL_MOUSEBUTTONUP:
                select_curseur2=0;
                break;

            case SDL_MOUSEMOTION:
                if (select_curseur2 && (event.motion.x >= pos_curseur1.x) && (event.motion.x <= pos_curseur1.x+100)) // Movement du curseur2.
                {
                    pos_curseur2.x=event.motion.x-6;
                }
                 printf("%d\n", event.motion.y);
            break;




         }
}

    /* On efface l'écran */
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));

    /* Tous les BLIT */
    SDL_BlitSurface(fenetre, NULL, ecran, &pos_fenetre);
    SDL_BlitSurface(curseur1, NULL, ecran, &pos_curseur1);
    SDL_BlitSurface(curseur2, NULL, ecran, &pos_curseur2);
    Blit_Image(ecran, Dev_Icone, ScreenW-45, 15);

    /* Opérations */

    if(Est_Un_Dev)
    {
    plus=Spinner_Print(ecran, 0, ScreenH, ScreenW);
    moins=Spinner_Print(ecran, 1, ScreenH, ScreenW);
    }

    for(i=0; i<NBR_CASES; i++)
        for(j=0; j<NBR_CASES; j++){
            Selected_Type_Case=Select_Type(grill, Tab_Type, i, j);
            Actualiser(carre[i][j], Selected_Type_Case, (j*taille_case+j+pos_fenetre.x), (i*taille_case+i+pos_fenetre.y));
            SDL_BlitSurface((carre[i][j]->srf), NULL, ecran, &(carre[i][j]->pos));
        }


    /*Legendes*/


    for (i=0; i<11; i++)
        Blit_Image(ecran, Legendes_Surface[i], (ScreenH-40), (140+40*i));




    /* Mise à jour de l'écran */
    SDL_Flip(ecran);



    /* Actualisation de la grille ! */

                /*Mise à jour vitesse*/
 Refresh_Timer=((pos_curseur2.x - pos_curseur1.x)+7); // La différence varie entre -6 et 94.


    if ((Compteur_Tours%Refresh_Timer==0) && (Refresh_Timer<=95))
    {
        grill->faireTour(grill);
        system("clear");
    }

            //usleep(100000);

Compteur_Tours++;

    } // End of while




    /*Fermeture de l'affichage*/

	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(curseur1);
	SDL_FreeSurface(curseur2);
    SDL_FreeSurface(boite);
    SDL_FreeSurface(plus);
    SDL_FreeSurface(moins);
    SDL_FreeSurface(Dev_Icone);

    for(i=0; i<11; i++){
            free(Tab_Type[i]);
            free(Legendes_Surface[i]);
    }

    for(k=0;k<grill->Taille;++k)
        free(carre[k]);
    free(carre);

    TTF_CloseFont(police);
    SDL_Quit();
    TTF_Init();
}


SDL_Surface* Charger(int taille_case, SDL_Surface *ecran, int type)
{

    SDL_Surface *Case;
    Case = SDL_CreateRGBSurface(SDL_HWSURFACE, taille_case, taille_case, 32,0,0,0,0);



    switch (type){

        case 1:
            SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 96, 96, 96)); // Pont gris
            break;
        case 2:
            SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 254, 255, 255)); //Baleine blanche
            break;
    case 3:
        SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 0, 114, 45)); // Bar Vert
        break;
        case 4:
            SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 255, 102, 0)); // Corail Orange
            break;
    case 5:
        SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 15, 14, 20)); //Orque noir
        break;
    case 6:
        SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 253, 190, 1)); // Plancton jaune
        break;
    case 7:
        SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 80, 24, 69)); //Polution viollet
        break;
    case 8:
        SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 236, 68, 155)); // Thon rose
        break;
    case 9:
        SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 55, 49, 33)); // Requin marron
        break;
    case 10:
        SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 209, 0, 57)); // Pyranha rose
        break;
    default:
        SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 204, 255, 229)); // Mer
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

SDL_Surface** Select_Type(struct Grille *grill, SDL_Surface **Tab_Type, int i, int j)
{



    if (grill->tab[i][j].liste->HasAPont(grill->tab[i][j].liste)){
        return &Tab_Type[1];
    }
    else if (grill->tab[i][j].liste->HasAnAnimal(grill->tab[i][j].liste)){

        switch(grill->tab[i][j].liste->getAnimal(grill->tab[i][j].liste)->type){
            case BALEINE:
                return &Tab_Type[2];
                break;
            case BAR:
                return &Tab_Type[3];
                break;
            case CORAIL:
                return &Tab_Type[4];
                break;
            case ORQUE:
                return &Tab_Type[5];
                break;
            case PLANCTON:
                return &Tab_Type[6];
                break;
            case POLLUTION:
                return &Tab_Type[7];
                break;
            case PYRANHA:
                return &Tab_Type[8];
                break;
            case REQUIN:
                return &Tab_Type[9];
                break;
            case THON:
                return &Tab_Type[10];
                break;
            default:
                return &Tab_Type[0];
                break;
        }}
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

SDL_Surface** Legendes_Print(SDL_Surface** Legendes_Surface, TTF_Font* police)
{
    SDL_Color Couleur_Mer = {204, 255, 229,0};
    SDL_Color Couleur_Pont = {96, 96, 96,0};
    SDL_Color Couleur_Baleine = {254, 255, 255,0};
    SDL_Color Couleur_Bar = {0, 114, 45,0};
    SDL_Color Couleur_Corail = {255, 102, 0,0 };
    SDL_Color Couleur_Orque = {15, 14, 20,0};
    SDL_Color Couleur_Plancton = {253, 190, 1,0};
    SDL_Color Couleur_Pollution = {80, 24, 69,0};
    SDL_Color Couleur_Thon = {236, 68, 155,0};
    SDL_Color Couleur_Requin = {55, 49, 33,0};
    SDL_Color Couleur_Pyranha = {209, 0, 57};

    Legendes_Surface[0] = TTF_RenderText_Blended(police, "Mer", Couleur_Mer);
    Legendes_Surface[1] = TTF_RenderText_Blended(police, "Pont", Couleur_Pont);
    Legendes_Surface[2] = TTF_RenderText_Blended(police, "Baleine", Couleur_Baleine);
    Legendes_Surface[3] = TTF_RenderText_Blended(police, "Bar", Couleur_Bar);
    Legendes_Surface[4] = TTF_RenderText_Blended(police, "Corail", Couleur_Corail);
    Legendes_Surface[5] = TTF_RenderText_Blended(police, "Orque", Couleur_Orque);
    Legendes_Surface[6] = TTF_RenderText_Blended(police, "Plancton", Couleur_Plancton);
    Legendes_Surface[7] = TTF_RenderText_Blended(police, "Pollution", Couleur_Pollution);
    Legendes_Surface[8] = TTF_RenderText_Blended(police, "Thon", Couleur_Thon);
    Legendes_Surface[9] = TTF_RenderText_Blended(police, "Requin", Couleur_Requin);
    Legendes_Surface[10] = TTF_RenderText_Blended(police, "Pyranha", Couleur_Pyranha);


    return Legendes_Surface;
}


SDL_Surface** Select_Legende(SDL_Surface** Legendes_Surface, TTF_Font* police, TTF_Font *police_underline, int selected)
{

    SDL_Color Couleur_Mer = {204, 255, 229,0};
    SDL_Color Couleur_Pont = {96, 96, 96,0};
    SDL_Color Couleur_Baleine = {254, 255, 255,0};
    SDL_Color Couleur_Bar = {0, 114, 45,0};
    SDL_Color Couleur_Corail = {255, 102, 0,0 };
    SDL_Color Couleur_Orque = {15, 14, 20,0};
    SDL_Color Couleur_Plancton = {253, 190, 1,0};
    SDL_Color Couleur_Pollution = {80, 24, 69,0};
    SDL_Color Couleur_Thon = {236, 68, 155,0};
    SDL_Color Couleur_Requin = {55, 49, 33,0};
    SDL_Color Couleur_Pyranha = {209, 0, 57};


    Legendes_Surface[0] = TTF_RenderText_Blended(police, "Mer", Couleur_Mer);
    Legendes_Surface[1] = TTF_RenderText_Blended(police, "Pont", Couleur_Pont);
    Legendes_Surface[2] = TTF_RenderText_Blended(police, "Baleine", Couleur_Baleine);
    Legendes_Surface[3] = TTF_RenderText_Blended(police, "Bar", Couleur_Bar);
    Legendes_Surface[4] = TTF_RenderText_Blended(police, "Corail", Couleur_Corail);
    Legendes_Surface[5] = TTF_RenderText_Blended(police, "Orque", Couleur_Orque);
    Legendes_Surface[6] = TTF_RenderText_Blended(police, "Plancton", Couleur_Plancton);
    Legendes_Surface[7] = TTF_RenderText_Blended(police, "Pollution", Couleur_Pollution);
    Legendes_Surface[8] = TTF_RenderText_Blended(police, "Thon", Couleur_Thon);
    Legendes_Surface[9] = TTF_RenderText_Blended(police, "Requin", Couleur_Requin);
    Legendes_Surface[10] = TTF_RenderText_Blended(police, "Pyranha", Couleur_Pyranha);

    if (selected==2)
    Legendes_Surface[2] = TTF_RenderText_Blended(police_underline, "Baleine", Couleur_Baleine);
    if (selected==3)
    Legendes_Surface[3] = TTF_RenderText_Blended(police_underline, "Bar", Couleur_Bar);
    if (selected==4)
    Legendes_Surface[4] = TTF_RenderText_Blended(police_underline, "Corail", Couleur_Corail);
    if (selected==5)
    Legendes_Surface[5] = TTF_RenderText_Blended(police_underline, "Orque", Couleur_Orque);
    if (selected==6)
    Legendes_Surface[6] = TTF_RenderText_Blended(police_underline, "Plancton", Couleur_Plancton);
    if (selected==7)
    Legendes_Surface[7] = TTF_RenderText_Blended(police_underline, "Pollution", Couleur_Pollution);
    if (selected==8)
    Legendes_Surface[8] = TTF_RenderText_Blended(police_underline, "Thon", Couleur_Thon);
    if (selected==9)
    Legendes_Surface[9] = TTF_RenderText_Blended(police_underline, "Requin", Couleur_Requin);
    if (selected==10)
    Legendes_Surface[10] = TTF_RenderText_Blended(police_underline, "Pyranha", Couleur_Pyranha);


    return Legendes_Surface;
}
