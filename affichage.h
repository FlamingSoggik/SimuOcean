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


SDL_Surface* Spinner_Print(SDL_Surface *ecran, int Plus_Ou_Moins, int ScreenH, int ScreenW);
SDL_Surface* Charger_Image(const char* fic, SDL_Surface *ecran);
void Blit_Image(SDL_Surface* ecran,SDL_Surface* srf,int x,int y);
SDL_Surface** Legendes_Print(SDL_Surface** Legendes_Surface, TTF_Font *police);

#endif // AFFICHAGE_H
