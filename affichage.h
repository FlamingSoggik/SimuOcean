#include "grille.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

typedef struct SDLCase
{
    int caca;
    SDL_Rect pos;
    SDL_Surface *srf;
}SDLCase;


void Charger(SDL_Surface *Case_Type, int taille_case, SDL_Surface *ecran);
void Actualiser(SDLCase* Case_Tab, SDL_Surface *Case_Type, int absisse, int ordonnee);
void SDL_Print(struct Grille *grill);







#endif // AFFICHAGE_H
