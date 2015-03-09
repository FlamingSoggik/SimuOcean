#include "affichage.h"
#include "sdl_pecheur.h"
#include "elementpecheur.h"
#include "Bool.h"
#include <math.h>


struct Grille* SDL_Print(struct Grille *grill){

	const long PROP_FENETRE=95; // (1-100) Proportion de la grille par rapport à la fenetre du jeu.
	const int16_t NBR_CASES=grill->Taille; // Largeur de la grille

	/* Initialisation des variables nécessaires */
	SDL_Surface **Selected_Type_Case=NULL, *blanc=NULL, *rouge=NULL, *plusIcone=NULL, *moinsIcone=NULL, *graphIcone=NULL,*paramIcone=NULL,*ecran = NULL ,*fenetre = NULL, *curseur1 = NULL, *curseur2 = NULL, *boite = NULL, *graphique=NULL;
	TTF_Font *police=NULL, *police_underline=NULL;
	SDL_Event event;
	int16_t continuer=1;
	int16_t select_curseur2=0;
	int16_t i=0; int16_t j=0, nbpecheurs=0;
	int16_t Est_Un_Dev =0;
	int16_t Compteur_Tours=0, Refresh_Timer=1;
	ElementAnimal_Constantes *C_Selected;
	int16_t nbr_espece[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	int16_t TourDuJoueur=-1;
	int16_t Commande_Selected=1;
	Bool boolean=False;
	int16_t pointeurX, pointeurY;
	int16_t Actif_Peche=0;
	double Arrondivision=0;

	SDLCase ***carre = malloc(sizeof(SDLCase**)*grill->Taille);
	uint16_t k;
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
	Tab_Type=(SDL_Surface**)malloc(sizeof(SDL_Surface*)*12);




	/* Initialisation de la SDL */
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	//	putenv("SDL_VIDEO_WINDOW_POS=center"); // Centrage

	/* On récupère la taille de l'écran */
	const SDL_VideoInfo *videoInfo;
	videoInfo=SDL_GetVideoInfo();
	int16_t ScreenW=videoInfo->current_w*0.9;
	int16_t ScreenH=videoInfo->current_h*0.9;


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

	C_Selected=Select_Legende(Legendes_Surface, police, police_underline, 0);



	/* Gestion de la grille */

	int16_t taille_fenetre=ScreenH*PROP_FENETRE/100; //Par défaut
	int16_t taille_case = taille_fenetre/NBR_CASES;
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
	curseur1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 2, 32, 0, 0, 0, 0);
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
	/*DevMode*/
	moinsIcone=Charger_Image("ICONE_moins.bmp");
	plusIcone=Charger_Image("ICONE_plus.bmp");
	paramIcone=Charger_Image("parametre.bmp");
	graphIcone=Charger_Image("graph.bmp");
	/*Graphique*/
	graphique=SDL_CreateRGBSurface(SDL_HWSURFACE, ScreenH-50, (ScreenH-50)/1.6, 32, 0, 0, 0, 0);
	SDL_FillRect(graphique, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	/*Monsieur le pécheur*/
	rouge = SDL_CreateRGBSurface(SDL_HWSURFACE, 0.8*taille_case, 0.8*taille_case, 32, 0, 0, 0, 0);
	SDL_FillRect(rouge, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
	blanc = SDL_CreateRGBSurface(SDL_HWSURFACE, 0.5*taille_case, 0.5*taille_case, 32, 0, 0, 0, 0);
	SDL_FillRect(blanc, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	/*Actions du pécheur*/
	SDL_Surface *Avancer=NULL, *Construire=NULL, *PecherCanne=NULL, *PecherFilet=NULL;






	/* Initialisation des cases */


	for(i=0; i<12; i++)
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
						case SDLK_F2: // Nettoie le graphique
							if (Est_Un_Dev==2) SDL_FillRect(graphique, NULL, SDL_MapRGB(ecran->format,255,255,255));
							break;
						case SDLK_F5: // Reset la grille
							i=grill->Taille;
							nbpecheurs = grill->nbPecheur;
							grill->Free(grill);
							grill=New_Grille(i, nbpecheurs);
							Compteur_Tours=0;
							TourDuJoueur=-1;
							Init_Tab(nbr_espece);
							break;
						case SDLK_KP1: // Pavé numérique
							if (TourDuJoueur != -1)
							{
								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '1');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '1');

								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}

							break;
						case SDLK_KP2:
							if (TourDuJoueur != -1)
							{
								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '2');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '2');

								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}

							break;
						case SDLK_KP3:
							if (TourDuJoueur != -1)
							{

								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '3');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '3');

								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}

							break;
						case SDLK_KP4:
							if (TourDuJoueur != -1)
							{

								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '4');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '4');


								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}

							break;
						case SDLK_KP5:

							if (TourDuJoueur != -1)
							{

								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '5');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '5');

								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}

							break;
						case SDLK_KP6:
							if (TourDuJoueur != -1)
							{

								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '6');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '6');

								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}

							break;
						case SDLK_KP7:
							if (TourDuJoueur != -1)
							{

								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '7');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '7');

								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}

							break;
						case SDLK_KP8:
							if (TourDuJoueur != -1)
							{

								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '8');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '8');
								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}
							break;
						case SDLK_KP9:
							if (TourDuJoueur != -1)
							{

								if (Commande_Selected == 1)
									boolean=grill->tabPecheur[TourDuJoueur]->deplacement(grill->tabPecheur[TourDuJoueur], '9');
								if (Commande_Selected ==2)
									boolean = grill->tabPecheur[TourDuJoueur]->construirePont(grill->tabPecheur[TourDuJoueur], '9');

								if(boolean)
								{
									TourDuJoueur=TourDuJoueur+1;
									if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
								}

							}

							break;
						case SDLK_SPACE:
							if (Refresh_Timer>=95) pos_curseur2.x=pos_curseur1.x+50-6;
							else if (pos_curseur2.x == (pos_curseur1.x+50-6)) pos_curseur2.x=pos_curseur1.x-6;
							else pos_curseur2.x=pos_curseur1.x+100-6;
							break;
						default: break;
					}
					break;

				case SDL_MOUSEBUTTONDOWN: // Moment de pression

					/*Curseur de vitesse*/
					if ((pos_curseur2.x<=event.button.x) && (event.button.x<=pos_curseur2.x+12) && (pos_curseur2.y<=event.button.y) && (event.button.y<=pos_curseur2.y+32))
						select_curseur2=1;
					/*Bouton dév*/
					if ((ScreenW-45<=event.button.x) && (event.button.x<=ScreenW-45+30) && (15<=event.button.y) && (event.button.y<=15+30))
					{
						if(Est_Un_Dev==0 && grill->nbPecheur==0)
							Est_Un_Dev=1;
						else {
							Est_Un_Dev=0;
						}
					}
					/*Bouton graphique*/
					if ((ScreenW-45<=event.button.x) && (event.button.x<=ScreenW-45+30) && (ScreenH-45<=event.button.y) && (event.button.y<=ScreenH-15))
					{ if(Est_Un_Dev==1) Est_Un_Dev=2; else if(Est_Un_Dev==2) Est_Un_Dev=1; }

					/*Selection espèce*/
					if (Est_Un_Dev)
						if (((ScreenH-40)<=event.button.x) && (event.button.x<=(ScreenH-40+100)) && ((180)<=event.button.y) && (event.button.y<=585))
							C_Selected=Select_Legende(Legendes_Surface, police, police_underline, ((event.button.y)-140)/((580-140)/11));

					if (((ScreenH +(ScreenW-ScreenH)/2-15)-100<=event.button.x) && (event.button.x<=(ScreenH +(ScreenW-ScreenH)/2-15)-70) && ((ScreenH/2 - 100)<=event.button.y) && (event.button.y<=(ScreenH/2 - 100)+330))
						C_Selected=Edit_Constantes(0, (event.button.y - (ScreenH/2 - 100)), C_Selected);
					if (((ScreenH +(ScreenW-ScreenH)/2-15)+100<=event.button.x) && (event.button.x<=(ScreenH +(ScreenW-ScreenH)/2-15)+130) && ((ScreenH/2 - 100)<=event.button.y) && (event.button.y<=(ScreenH/2 - 100)+330))
						C_Selected=Edit_Constantes(1, (event.button.y - (ScreenH/2 - 100)), C_Selected);

					/*Selection Commande Pecheur */
					if (!Est_Un_Dev)
					{
						if (((ScreenH +(ScreenW-ScreenH)/2)-40<=event.button.x) && (event.button.x<=(ScreenH +(ScreenW-ScreenH)/2)+40) && ((ScreenH/2 - 50)<=event.button.y) && (event.button.y<=(ScreenH/2 - 10)))
							Commande_Selected=1;
						if (((ScreenH +(ScreenW-ScreenH)/2)-40<=event.button.x) && (event.button.x<=(ScreenH +(ScreenW-ScreenH)/2)+45) && ((ScreenH/2)<=event.button.y) && (event.button.y<=(ScreenH/2 + 40)))
							Commande_Selected=2;
						if (((ScreenH +(ScreenW-ScreenH)/2)-40<=event.button.x) && (event.button.x<=(ScreenH +(ScreenW-ScreenH)/2)+50) && ((ScreenH/2 +50)<=event.button.y) && (event.button.y<=(ScreenH/2 + 90)))
							Commande_Selected=3;
						if (((ScreenH +(ScreenW-ScreenH)/2)-40<=event.button.x) && (event.button.x<=(ScreenH +(ScreenW-ScreenH)/2)+50) && ((ScreenH/2 +100)<=event.button.y) && (event.button.y<=(ScreenH/2 + 140)))
							Commande_Selected=4;
					}


					/*Peche 2.0*/


					if (event.button.x<=ScreenH && (event.button.y<=ScreenH) && ((grill->nbPecheur>0)))
					{

						pointeurX=event.button.x;
						pointeurY=event.button.y;
						if(event.button.button == SDL_BUTTON_LEFT)
							Commande_Selected=3;
						if(event.button.button == SDL_BUTTON_RIGHT)
							Commande_Selected=4;
						Actif_Peche=Commande_Selected; // Voir relachement du bouton ci-dessous

					}

					break;

				case SDL_MOUSEBUTTONUP:
					select_curseur2=0;

					/*Peche 2.0*/
					if ((Commande_Selected==3 || Commande_Selected==4) && (grill->nbPecheur>0))
					{
						if (Actif_Peche!=0 && event.button.x<=ScreenH && (event.button.y<=ScreenH))
						{
							pointeurX=event.button.x-pointeurX;
							pointeurY=event.button.y-pointeurY;


							/*Calcul de peche*/
							Arrondivision=(pointeurX/taille_case)*1.0;
							if(Arrondivision>=0.5)
							{
								pointeurX=ceil(Arrondivision);
							}
							else pointeurX=floor(Arrondivision);

							Arrondivision=(pointeurY/taille_case)*1.0;
							if(Arrondivision>=0.5)
							{
								pointeurY=ceil(Arrondivision);
							}
							else pointeurY=floor(Arrondivision);
							/*Peche*/
							if (Commande_Selected==3 && TourDuJoueur != -1)
							{
								grill->tabPecheur[TourDuJoueur]->pecheParCanneSDL(grill->tabPecheur[TourDuJoueur], ((grill->tabPecheur[TourDuJoueur]->caseParent->posX)+pointeurY), (grill->tabPecheur[TourDuJoueur]->caseParent->posY)+pointeurX);
								TourDuJoueur=TourDuJoueur+1;
								if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;

							}
							else if (Commande_Selected==4 && TourDuJoueur != -1)
							{
								grill->tabPecheur[TourDuJoueur]->pecheParFiletSDL(grill->tabPecheur[TourDuJoueur],  ((grill->tabPecheur[TourDuJoueur]->caseParent->posX)+pointeurY), (grill->tabPecheur[TourDuJoueur]->caseParent->posY)+pointeurX);
								TourDuJoueur=TourDuJoueur+1;
								if (TourDuJoueur==grill->nbPecheur) TourDuJoueur=-1;
							}

							Actif_Peche=0;
						}
					}
					break;

				case SDL_MOUSEMOTION:
					//printf(" Curseur x : %d\n Curseur y: %d\n", (event.motion.x), (event.motion.y)); // Affocher la position du curseur en temps réel
					if (select_curseur2 && (event.motion.x >= pos_curseur1.x) && (event.motion.x <= pos_curseur1.x+100)) // Movement du curseur2.
					{
						pos_curseur2.x=event.motion.x-6;

					}
					break;





			}
		}

		/* On efface l'écran */

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));

		Init_Tab(nbr_espece);

		/* Tous les BLIT */
		SDL_BlitSurface(fenetre, NULL, ecran, &pos_fenetre);
		SDL_BlitSurface(curseur1, NULL, ecran, &pos_curseur1);
		SDL_BlitSurface(curseur2, NULL, ecran, &pos_curseur2);
		Blit_Image(ecran, paramIcone, ScreenW-45, 15);
		Print_NbTour(ecran, grill, police, ScreenH, ScreenW );

		/* Opérations */

		if(Est_Un_Dev)
		{
			Spinner_Print(ecran, 0, ScreenH, ScreenW, plusIcone);
			Spinner_Print(ecran, 1, ScreenH, ScreenW, moinsIcone);
			Print_Constantes( ecran, C_Selected, police, ScreenH, ScreenW);
			Blit_Image(ecran, graphIcone, ScreenW-45, ScreenH-45);
		}


		if(!Est_Un_Dev)
		{
			Commandes_Pecheur(ecran, Avancer, Construire, PecherCanne, PecherFilet, police, police_underline, Commande_Selected, ScreenH, ScreenW);

			if (TourDuJoueur!=-1)
				Sac_Pecheur( ecran, police, grill->tabPecheur[TourDuJoueur], ScreenH, ScreenW );
		}


		if(Est_Un_Dev!=2) // Mode grille
		{
			for(i=0; i<NBR_CASES; i++)
				for(j=0; j<NBR_CASES; j++)
				{
					Selected_Type_Case=Select_Type(grill, Tab_Type, i, j, nbr_espece);
					Actualiser(carre[i][j], Selected_Type_Case, (j*taille_case+j+pos_fenetre.x), (i*taille_case+i+pos_fenetre.y));
					SDL_BlitSurface((carre[i][j]->srf), NULL, ecran, &(carre[i][j]->pos));
				}
		}


		if(Est_Un_Dev==2) // Mode Graphique
		{
			for(i=0; i<NBR_CASES; i++)
				for(j=0; j<NBR_CASES; j++)
					Selected_Type_Case=Select_Type(grill, Tab_Type, i, j, nbr_espece); // Permet d'actualiser le tableau des nombres d'espèce.

			Blit_Image(ecran, graphique, 25, (ScreenH/2)-((ScreenH-50)/1.6)/2);
			Print_Graphique(graphique, (ScreenH-50)/1.6, nbr_espece, NBR_CASES, grill);

		}

		/* Monsieur le Pécheur */

		if(Est_Un_Dev!=2)
		{
			Afficher_Pecheurs( ecran, taille_case, grill->tabPecheur, grill->nbPecheur, pos_fenetre, rouge );

			if (TourDuJoueur!=-1 && grill->nbPecheur!=0)
				Selected_Pecheur(ecran, taille_case, grill->tabPecheur[TourDuJoueur], pos_fenetre, blanc );
		}



		/*Legendes*/


		for (i=0; i<11; i++)
			Blit_Image(ecran, Legendes_Surface[i], (ScreenH), (140+40*i));







		/* Actualisation de la grille ! */

		/*Mise à jour vitesse*/
		Refresh_Timer=((pos_curseur2.x - pos_curseur1.x)+7); // La différence varie entre -6 et 94.


		if ((Compteur_Tours%Refresh_Timer==0) && (Refresh_Timer<=95)) // Cette boucle modifie la vitesse d'actualisation de la grille
		{


			// printf("%d\n", grill->TourCourant); // AFFICHAGE DU NOMBRE DE TOUR
			if (TourDuJoueur==-1)
			{
				grill->faireTour(grill, 1);

				if ((grill->nbPecheur!=0) && ((grill->TourCourant)%5)==0)
				{
					TourDuJoueur=(TourDuJoueur+1)%((grill->nbPecheur)+1);


				}
			}


		}





		/* Mise à jour de l'écran */
		SDL_Flip(ecran);

		//usleep(100000);

		++Compteur_Tours;

	} // End of while


	/*Fermeture de l'affichage*/

	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(curseur1);
	SDL_FreeSurface(curseur2);
	SDL_FreeSurface(boite);
	SDL_FreeSurface(plusIcone);
	SDL_FreeSurface(moinsIcone);
	SDL_FreeSurface(paramIcone);
	SDL_FreeSurface(graphIcone);
	SDL_FreeSurface(graphique);
	SDL_FreeSurface(rouge);
	SDL_FreeSurface(blanc);
	SDL_FreeSurface(Avancer);
	SDL_FreeSurface(Construire);
	SDL_FreeSurface(PecherCanne);
	SDL_FreeSurface(PecherFilet);


	for(i=0; i<12; i++){
		SDL_FreeSurface(Tab_Type[i]);
	}
	for(i=0; i<11; i++){
		SDL_FreeSurface(Legendes_Surface[i]);
	}

	free(Tab_Type);
	free(Legendes_Surface);

	for(i=0;i<NBR_CASES; ++i)
		for(j=0; j<NBR_CASES; ++j)
			free(carre[i][j]);


	for(k=0;k<grill->Taille;++k)
		free(carre[k]);
	free(carre);

	TTF_CloseFont(police);
	TTF_CloseFont(police_underline);
	SDL_Quit();
	TTF_Quit();
	return grill;
}


SDL_Surface* Charger(int16_t taille_case, SDL_Surface *ecran, int16_t type)
{

	SDL_Surface *Case;
	Case = SDL_CreateRGBSurface(SDL_HWSURFACE, taille_case, taille_case, 32,0,0,0,0);



	switch (type){

		case 1:
			SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 96, 96, 96)); // Pont gris
			break;
		case 2:
			SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 0, 0, 255)); //Baleine blanche
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
			SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 209, 0, 57)); // Thon rose
			break;
		case 9:
			SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 55, 49, 33)); // Requin marron
			break;
		case 10:
			SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 236, 68, 155)); // Pyranha rose
			break;
		case 11:
			SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 91, 60, 17)); // Terre Marron
			break;
		default:
			SDL_FillRect(Case, NULL, SDL_MapRGB(ecran->format, 254, 255, 255)); // Mer
			break;
	}


	return Case;

}

void Actualiser( SDLCase *Case_Tab, SDL_Surface **Case_Type, int16_t absisse, int16_t ordonnee)
{


	Case_Tab->pos.x=absisse;
	Case_Tab->pos.y=ordonnee;
	Case_Tab->srf=*Case_Type;

}

SDL_Surface** Select_Type(struct Grille *grill, SDL_Surface **Tab_Type, int16_t i, int16_t j, int16_t *tab)
{



	if (grill->tab[i][j].liste->HasAPont(grill->tab[i][j].liste)){
		tab[1]=tab[1]+1;
		return &Tab_Type[1];
	}
	else if (grill->tab[i][j].liste->HasDirt(grill->tab[i][j].liste)){
		tab[11]=tab[11]+1;
		return &Tab_Type[11];
	}
	else if (grill->tab[i][j].liste->HasAnAnimal(grill->tab[i][j].liste)){

		switch(grill->tab[i][j].liste->getAnimal(grill->tab[i][j].liste)->type){
			case BALEINE:
				tab[2]=tab[2]+1;
				return &Tab_Type[2];
				break;
			case BAR:
				tab[3]=tab[3]+1;
				return &Tab_Type[3];
				break;
			case CORAIL:
				tab[4]=tab[4]+1;
				return &Tab_Type[4];
				break;
			case ORQUE:
				tab[5]=tab[5]+1;
				return &Tab_Type[5];
				break;
			case PLANCTON:
				tab[6]=tab[6]+1;
				return &Tab_Type[6];
				break;
			case POLLUTION:
				tab[7]=tab[7]+1;
				return &Tab_Type[7];
				break;
			case PYRANHA:
				tab[8]=tab[8]+1;
				return &Tab_Type[8];
				break;
			case REQUIN:
				tab[9]=tab[9]+1;
				return &Tab_Type[9];
				break;
			case THON:
				tab[10]=tab[10]+1;
				return &Tab_Type[10];
				break;
			default:
				tab[0]=tab[0]+1;
				return &Tab_Type[0];
				break;
		}}
	else {
		return &Tab_Type[0];
	}

}

void Spinner_Print(SDL_Surface *ecran, int16_t Plus_Ou_Moins, int16_t ScreenH, int16_t ScreenW, SDL_Surface *srf)
{
	int16_t i;
	int16_t Centre_Commandes=(ScreenH +(ScreenW-ScreenH)/2-15); // Le 15 correspond à la largeur des images bmp !

	if(Plus_Ou_Moins==0)
	{
		for(i=0; i<7; i++)
			Blit_Image(ecran, srf, (Centre_Commandes + 100), (ScreenH/2 - 100 + 50*i));

	}
	else
	{
		for(i=0; i<7; i++)
			Blit_Image(ecran, srf, (Centre_Commandes - 100), (ScreenH/2 -100 + 50*i));
	}
}

SDL_Surface* Charger_Image(const char* fic)
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

void Blit_Image(SDL_Surface* ecran,SDL_Surface* srf,int16_t x,int16_t y)
{
	SDL_Rect R;
	R.x = x;
	R.y = y;
	SDL_BlitSurface(srf,NULL,ecran,&R);
}



ElementAnimal_Constantes *Select_Legende(SDL_Surface** Legendes_Surface, TTF_Font* police, TTF_Font *police_underline, int16_t selected)
{
	static int16_t premierPassage = 1;
	int16_t i;

	if (premierPassage == 1){
		premierPassage=0;
	}
	else {
		for(i=0; i<11; ++i){
			SDL_FreeSurface(Legendes_Surface[i]);
		}
	}
	ElementAnimal_Constantes *selected_animal=&C_Vide;

	SDL_Color Couleur_Mer = {254, 255, 255,0};
	SDL_Color Couleur_Pont = {96, 96, 96,0};
	SDL_Color Couleur_Baleine = {0, 0, 255,0};
	SDL_Color Couleur_Bar = {0, 114, 45,0};
	SDL_Color Couleur_Corail = {255, 102, 0,0 };
	SDL_Color Couleur_Orque = {15, 14, 20,0};
	SDL_Color Couleur_Plancton = {253, 190, 1,0};
	SDL_Color Couleur_Pollution = {80, 24, 69,0};
	SDL_Color Couleur_Thon = {236, 68, 155,0};
	SDL_Color Couleur_Requin = {55, 49, 33,0};
	SDL_Color Couleur_Pyranha = {209, 0, 57,0};




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
	{
		SDL_FreeSurface(Legendes_Surface[2]);
		Legendes_Surface[2] = TTF_RenderText_Blended(police_underline, "Baleine", Couleur_Baleine);
		selected_animal=&C_Baleine;
	}

	if (selected==3)
	{
		SDL_FreeSurface(Legendes_Surface[3]);
		Legendes_Surface[3] = TTF_RenderText_Blended(police_underline, "Bar", Couleur_Bar);
		selected_animal=&C_Bar;
	}

	if (selected==4)
	{
		SDL_FreeSurface(Legendes_Surface[4]);
		Legendes_Surface[4] = TTF_RenderText_Blended(police_underline, "Corail", Couleur_Corail);
		selected_animal=&C_Corail;
	}

	if (selected==5)
	{
		SDL_FreeSurface(Legendes_Surface[5]);
		Legendes_Surface[5] = TTF_RenderText_Blended(police_underline, "Orque", Couleur_Orque);
		selected_animal=&C_Orque;
	}

	if (selected==6)
	{
		SDL_FreeSurface(Legendes_Surface[6]);
		Legendes_Surface[6] = TTF_RenderText_Blended(police_underline, "Plancton", Couleur_Plancton);
		selected_animal=&C_Plancton;
	}

	if (selected==7)
	{
		SDL_FreeSurface(Legendes_Surface[7]);
		Legendes_Surface[7] = TTF_RenderText_Blended(police_underline, "Pollution", Couleur_Pollution);
		selected_animal=&C_Vide;
	}

	if (selected==8)
	{
		SDL_FreeSurface(Legendes_Surface[8]);
		Legendes_Surface[8] = TTF_RenderText_Blended(police_underline, "Thon", Couleur_Thon);
		selected_animal=&C_Thon;
	}

	if (selected==9)
	{
		SDL_FreeSurface(Legendes_Surface[9]);
		Legendes_Surface[9] = TTF_RenderText_Blended(police_underline, "Requin", Couleur_Requin);
		selected_animal=&C_Requin;
	}

	if (selected==10)
	{
		SDL_FreeSurface(Legendes_Surface[10]);
		Legendes_Surface[10] = TTF_RenderText_Blended(police_underline, "Pyranha", Couleur_Pyranha);
		selected_animal=&C_Pyranha;
	}

	return selected_animal;

}


void Print_Constantes(SDL_Surface *ecran, ElementAnimal_Constantes *Selected, TTF_Font *police, int16_t ScreenH, int16_t ScreenW)
{
	char texte[30]="";
	int16_t Centre_Commandes=(ScreenH +(ScreenW-ScreenH)/2-15); // Le 15 correspond à la largeur des images bmp !

    sprintf(texte, "Survie=%d", Selected->dureeSurvie);
	SDL_Surface *Surface_texte;
	SDL_Color Blanc = {254, 255, 255,0};
	Surface_texte=TTF_RenderText_Blended(police, texte, Blanc );
	Blit_Image(ecran, Surface_texte, Centre_Commandes - 45 , ScreenH/2 - 100);
	SDL_FreeSurface(Surface_texte);

	sprintf(texte, "Taille=%d", Selected->taille);
	Surface_texte=TTF_RenderText_Blended(police, texte, Blanc );
	Blit_Image(ecran, Surface_texte, Centre_Commandes - 45, ScreenH/2 - 50);
	SDL_FreeSurface(Surface_texte);

	sprintf(texte, "Bide=%d", Selected->tailleDuBide);
	Surface_texte=TTF_RenderText_Blended(police, texte, Blanc );
	Blit_Image(ecran, Surface_texte, Centre_Commandes - 45, ScreenH/2);
	SDL_FreeSurface(Surface_texte);

	sprintf(texte, "Saut=%d", Selected->sautMax);
	Surface_texte=TTF_RenderText_Blended(police, texte, Blanc );
	Blit_Image(ecran, Surface_texte, Centre_Commandes - 45, ScreenH/2 + 50);
	SDL_FreeSurface(Surface_texte);

	sprintf(texte, "Metab=%d", Selected->metabolisme);
	Surface_texte=TTF_RenderText_Blended(police, texte, Blanc );
	Blit_Image(ecran, Surface_texte, Centre_Commandes - 45, ScreenH/2 + 100);
	SDL_FreeSurface(Surface_texte);

	sprintf(texte, "Gestation=%d", Selected->gestation);
	Surface_texte=TTF_RenderText_Blended(police, texte, Blanc );
	Blit_Image(ecran, Surface_texte, Centre_Commandes - 45, ScreenH/2 + 150 );
	SDL_FreeSurface(Surface_texte);

	sprintf(texte, "Repro=%d", Selected->frequenceReproduction);
	Surface_texte=TTF_RenderText_Blended(police, texte, Blanc );
	Blit_Image(ecran, Surface_texte, Centre_Commandes - 45, ScreenH/2 + 200);
	SDL_FreeSurface(Surface_texte);

	return;
}

ElementAnimal_Constantes *Edit_Constantes(int16_t Plus_Ou_Moins, int16_t position, ElementAnimal_Constantes *Selected)
{
	if (Plus_Ou_Moins==0) Plus_Ou_Moins=-1;

	if (position<=30)
		Selected->dureeSurvie=Selected->dureeSurvie+Plus_Ou_Moins;

	if ((position>=50) && (position<=80))
		Selected->taille=Selected->taille+Plus_Ou_Moins;

	if ((position>=100) && (position<=130))
		Selected->tailleDuBide=Selected->tailleDuBide+Plus_Ou_Moins;

	if ((position>=150) && (position<=180)){
		if (Selected->sautMax != 0 || Plus_Ou_Moins != -1) // Saut max ne peut pas etre negatif
			Selected->sautMax=Selected->sautMax+Plus_Ou_Moins;
	}

	if ((position>=200) && (position<=230))
		Selected->metabolisme=Selected->metabolisme+Plus_Ou_Moins;

	if ((position>=250) && (position<=280))
		Selected->gestation=Selected->gestation+Plus_Ou_Moins;

	if ((position>=300) && (position<=330))
		Selected->frequenceReproduction=Selected->frequenceReproduction+Plus_Ou_Moins;

	return Selected;


}

void Init_Tab(int16_t *tab)
{
	int16_t i=0;
	for (i=0; i<11; i++)
		tab[i]=0;
	return;

}


void Print_Graphique(SDL_Surface *graph, int16_t GraphH, int16_t *nbr_espece, int16_t NBR_CASES, Grille *grill)
{



	SDL_Surface *Gros_Pixel=NULL;
	Gros_Pixel=SDL_CreateRGBSurface(SDL_HWSURFACE, 2, 2, 32, 0, 0, 0, 0);


	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 204, 255, 0));
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[6]*GraphH)/(NBR_CASES*NBR_CASES)));

    SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 0, 0, 255));//Baleine
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[2]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 0, 114, 45));//Bar
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[3]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 255, 102, 0));//Corail
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[4]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 15, 14, 20));//Orque
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[5]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 223, 190, 1));//Plancton
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[6]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 80, 24, 69));//Pollution
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[7]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 236, 68, 155));//Thon
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[8]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 55, 49, 33));//Requin
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[9]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FillRect(Gros_Pixel, NULL, SDL_MapRGB(graph->format, 209, 0, 57));//Pyranha
	Blit_Image(graph,Gros_Pixel,(grill->TourCourant), GraphH-((nbr_espece[10]*GraphH)/(NBR_CASES*NBR_CASES)));

	SDL_FreeSurface(Gros_Pixel);
}


void Print_NbTour(SDL_Surface *ecran, Grille *grill, TTF_Font* police, int16_t ScreenH, int16_t ScreenW )
{
	SDL_Surface *NombreTour=NULL;
	SDL_Color Couleur_Commandes = {193, 205, 193,0};

	char texte[30]="";
	sprintf(texte, "Tour = %d", grill->TourCourant);
	NombreTour = TTF_RenderText_Blended(police, texte, Couleur_Commandes);

	int16_t Centre_Commandes=(ScreenH +(ScreenW-ScreenH)/2);

	Blit_Image(ecran, NombreTour, Centre_Commandes-30, ScreenH/2 - 200 );

	SDL_FreeSurface(NombreTour);


}
















