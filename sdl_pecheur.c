#include "sdl_pecheur.h"
#include "elementpecheur.h"
#include "affichage.h"



void Afficher_Pecheurs( SDL_Surface *ecran, int taille_case, ElementPecheur **pt_Pecheur, int nbrpecheur, SDL_Rect Pos_Fenetre, SDL_Surface *rouge )
{
     int i=0;
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

void Selected_Pecheur(SDL_Surface *ecran, int taille_case, ElementPecheur *pt_Pecheur, SDL_Rect Pos_Fenetre, SDL_Surface *blanc )
{
    SDL_Rect Pos_Pecheur;

    Pos_Pecheur.x=pt_Pecheur->caseParent->posY; //Position sur la grille, pas sur l'écran
    Pos_Pecheur.y=pt_Pecheur->caseParent->posX;

    Pos_Pecheur.x=(Pos_Fenetre.x)+(Pos_Pecheur.x)*taille_case + (Pos_Pecheur.x) + (taille_case-(0.5*taille_case))/2; // Position sur l'écran
    Pos_Pecheur.y=(Pos_Fenetre.y)+(Pos_Pecheur.y)*taille_case + (Pos_Pecheur.y) + (taille_case-(0.5*taille_case))/2; // Position de la grille + position du pecheur + le grillage + la marge du peucheur.



    SDL_BlitSurface(blanc, NULL, ecran, &Pos_Pecheur);

}


void Commandes_Pecheur(SDL_Surface *ecran, SDL_Surface *Avancer, SDL_Surface *Construire, SDL_Surface *Pecher, TTF_Font* police, TTF_Font *police_underline, int Commande_Selected, int ScreenH, int ScreenW)
{


static int premierPassage = 1;

if (premierPassage == 1){
    premierPassage=0;
}
else {
    SDL_FreeSurface(Avancer);
    SDL_FreeSurface(Construire);
    SDL_FreeSurface(Pecher);
    }

SDL_Color Couleur_Commandes = {193, 205, 193,0};

if (Commande_Selected==0)
{
Avancer = TTF_RenderText_Blended(police, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police, "Construire", Couleur_Commandes);
Pecher = TTF_RenderText_Blended(police, "Pecher", Couleur_Commandes);
}
if (Commande_Selected==1)
{
Avancer = TTF_RenderText_Blended(police_underline, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police, "Construire", Couleur_Commandes);
Pecher = TTF_RenderText_Blended(police, "Pecher", Couleur_Commandes);
}
if (Commande_Selected==2)
{
Avancer = TTF_RenderText_Blended(police, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police_underline, "Construire", Couleur_Commandes);
Pecher = TTF_RenderText_Blended(police, "Pecher", Couleur_Commandes);
}
if (Commande_Selected==3)
{
Avancer = TTF_RenderText_Blended(police, "Avancer", Couleur_Commandes);
Construire = TTF_RenderText_Blended(police, "Construire", Couleur_Commandes);
Pecher = TTF_RenderText_Blended(police_underline, "Pecher", Couleur_Commandes);
}


int Centre_Commandes=(ScreenH +(ScreenW-ScreenH)/2);
Blit_Image(ecran, Avancer, Centre_Commandes - 40, ScreenH/2 - 50);
Blit_Image(ecran, Construire, Centre_Commandes - 40, ScreenH/2);
Blit_Image(ecran, Pecher, Centre_Commandes - 40, ScreenH/2 + 50);


}
