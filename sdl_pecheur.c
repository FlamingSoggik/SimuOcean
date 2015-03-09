#include "sdl_pecheur.h"
#include "elementpecheur.h"
#include "affichage.h"



void Afficher_Pecheurs( SDL_Surface *ecran, int16_t taille_case, ElementPecheur **pt_Pecheur, int16_t nbrpecheur, SDL_Rect Pos_Fenetre, SDL_Surface *rouge )
{
	 int16_t i=0;
     SDL_Rect Pos_Pecheur;
     for (; i<nbrpecheur; i++)
     {
                 Pos_Pecheur.x=0;
                 Pos_Pecheur.y=0;

         Pos_Pecheur.x=pt_Pecheur[i]->caseParent->posY; //Position sur la grille, pas sur l'écran
         Pos_Pecheur.y=pt_Pecheur[i]->caseParent->posX;

         Pos_Pecheur.x=((Pos_Fenetre.x)+(Pos_Pecheur.x)*taille_case + (Pos_Pecheur.x) + (taille_case-(0.8*taille_case))/2); // Position sur l'écran
         Pos_Pecheur.y=(Pos_Fenetre.y)+(Pos_Pecheur.y)*taille_case + (Pos_Pecheur.y) + (taille_case-(0.8*taille_case))/2; // Position de la grille + position du pecheur + le grillage + la marge du peucheur.

         SDL_BlitSurface(rouge, NULL, ecran, &Pos_Pecheur);
     }

}

void Selected_Pecheur(SDL_Surface *ecran, int16_t taille_case, ElementPecheur *pt_Pecheur, SDL_Rect Pos_Fenetre, SDL_Surface *blanc )
{
    SDL_Rect Pos_Pecheur;

    Pos_Pecheur.x=pt_Pecheur->caseParent->posY; //Position sur la grille, pas sur l'écran
    Pos_Pecheur.y=pt_Pecheur->caseParent->posX;

    Pos_Pecheur.x=(Pos_Fenetre.x)+(Pos_Pecheur.x)*taille_case + (Pos_Pecheur.x) + (taille_case-(0.5*taille_case))/2; // Position sur l'écran
    Pos_Pecheur.y=(Pos_Fenetre.y)+(Pos_Pecheur.y)*taille_case + (Pos_Pecheur.y) + (taille_case-(0.5*taille_case))/2; // Position de la grille + position du pecheur + le grillage + la marge du peucheur.



    SDL_BlitSurface(blanc, NULL, ecran, &Pos_Pecheur);

}



void Commandes_Pecheur(SDL_Surface *ecran, SDL_Surface *Avancer, SDL_Surface *Construire, SDL_Surface *PecherCanne,  SDL_Surface *PecherFilet, TTF_Font* police, TTF_Font *police_underline, int16_t Commande_Selected, int16_t ScreenH, int16_t ScreenW)
{


//static int16_t premierPassage = 1;

//if (premierPassage == 1){
//	premierPassage=0;
//}
//else {
//	SDL_FreeSurface(Avancer);
//	SDL_FreeSurface(Construire);
//	SDL_FreeSurface(PecherCanne);
//	SDL_FreeSurface(PecherFilet);
//	}

SDL_Color Couleur_Commandes = {193, 205, 193,0};

if (Commande_Selected==0)
{
Avancer = TTF_RenderText_Blended(police, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police, "Construire", Couleur_Commandes);
PecherCanne = TTF_RenderText_Blended(police, "Pecher (Canne)", Couleur_Commandes);
PecherFilet = TTF_RenderText_Blended(police, "Pecher (Filet)", Couleur_Commandes);
}
if (Commande_Selected==1)
{
Avancer = TTF_RenderText_Blended(police_underline, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police, "Construire", Couleur_Commandes);
PecherCanne = TTF_RenderText_Blended(police, "Pecher (Canne)", Couleur_Commandes);
PecherFilet = TTF_RenderText_Blended(police, "Pecher (Filet)", Couleur_Commandes);
}
else if (Commande_Selected==2)
{
Avancer = TTF_RenderText_Blended(police, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police_underline, "Construire", Couleur_Commandes);
PecherCanne = TTF_RenderText_Blended(police, "Pecher (Canne)", Couleur_Commandes);
PecherFilet = TTF_RenderText_Blended(police, "Pecher (Filet)", Couleur_Commandes);
}
else if (Commande_Selected==3)
{
Avancer = TTF_RenderText_Blended(police, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police, "Construire", Couleur_Commandes);
PecherCanne = TTF_RenderText_Blended(police_underline, "Pecher (Canne)", Couleur_Commandes);
PecherFilet = TTF_RenderText_Blended(police, "Pecher (Filet)", Couleur_Commandes);
}
else if (Commande_Selected==4)
{
Avancer = TTF_RenderText_Blended(police, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police, "Construire", Couleur_Commandes);
PecherCanne = TTF_RenderText_Blended(police, "Pecher (Canne)", Couleur_Commandes);
PecherFilet = TTF_RenderText_Blended(police_underline, "Pecher (Filet)", Couleur_Commandes);
}

int16_t Centre_Commandes=(ScreenH +(ScreenW-ScreenH)/2);
Blit_Image(ecran, Avancer, Centre_Commandes - 40, ScreenH/2 - 50);
Blit_Image(ecran, Construire, Centre_Commandes - 40, ScreenH/2);
Blit_Image(ecran, PecherCanne, Centre_Commandes - 40, ScreenH/2 + 50);
Blit_Image(ecran, PecherFilet, Centre_Commandes - 40, ScreenH/2 + 100);

SDL_FreeSurface(Avancer);
SDL_FreeSurface(Construire);
SDL_FreeSurface(PecherCanne);
SDL_FreeSurface(PecherFilet);


}


void Sac_Pecheur( SDL_Surface *ecran, TTF_Font* police, ElementPecheur *pt_Pecheur, int16_t ScreenH, int16_t ScreenW )
{
    SDL_Surface *Sac_du_Pecheur=NULL;
    SDL_Color Couleur_Commandes = {193, 205, 193,0};

    char texte[30]="";
    sprintf(texte, "Sac = %d", pt_Pecheur->sac);
    Sac_du_Pecheur = TTF_RenderText_Blended(police, texte, Couleur_Commandes);

	int16_t Centre_Commandes=(ScreenH +(ScreenW-ScreenH)/2);

    Blit_Image(ecran, Sac_du_Pecheur, Centre_Commandes-30, ScreenH/2 - 150 );

 SDL_FreeSurface(Sac_du_Pecheur);


}
