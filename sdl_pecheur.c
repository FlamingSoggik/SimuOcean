#include "sdl_pecheur.h"
#include "elementpecheur.h"
#include "affichage.h"

//Actualiser(carre[i][j], Selected_Type_Case, (j*taille_case+j+pos_fenetre.x), (i*taille_case+i+pos_fenetre.y));

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

         Pos_Pecheur.x=(Pos_Fenetre.x)+(Pos_Pecheur.x)*taille_case + (Pos_Pecheur.x); // Position sur l'écran
         Pos_Pecheur.y=(Pos_Fenetre.y)+(Pos_Pecheur.y)*taille_case + (Pos_Pecheur.y); // Position de la grille + position du pecheur + le grillage.

         SDL_BlitSurface(rouge, NULL, ecran, &Pos_Pecheur);
     }

}






