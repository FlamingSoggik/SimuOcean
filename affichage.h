#include "grille.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

typedef struct SDLCase
{
    SDL_Rect pos;
    SDL_Surface *srf;
}SDLCase;


SDL_Surface* Charger(int taille_case, SDL_Surface *ecran, int type); // Charge les différents type de case.
void Actualiser(SDLCase* Case_Tab, SDL_Surface **Case_Type, int absisse, int ordonnee);
void SDL_Print(struct Grille *grill);
SDL_Surface** Select_Type(Grille *grill, SDL_Surface **Tab_Type, int i, int j);






#endif // AFFICHAGE_H
