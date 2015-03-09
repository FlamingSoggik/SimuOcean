#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "grille.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "elementanimal.h"

typedef struct SDLCase
{
    SDL_Rect pos;
    SDL_Surface *srf;
}SDLCase;


SDL_Surface* Charger(int16_t taille_case, SDL_Surface *ecran, int16_t type); // Charge les différents type de case.
void Actualiser(SDLCase* Case_Tab, SDL_Surface **Case_Type, int16_t absisse, int16_t ordonnee);
Grille *SDL_Print(struct Grille *grill);
SDL_Surface** Select_Type(Grille *grill, SDL_Surface **Tab_Type, int16_t i, int16_t j, int16_t *tab);


void Spinner_Print(SDL_Surface *ecran, int16_t Plus_Ou_Moins, int16_t ScreenH, int16_t ScreenW, SDL_Surface *srf);
SDL_Surface* Charger_Image(const char* fic);
void Blit_Image(SDL_Surface* ecran,SDL_Surface* srf,int16_t x,int16_t y);
ElementAnimal_Constantes *Select_Legende(SDL_Surface** Legendes_Surface, TTF_Font* police, TTF_Font *police_underline, int16_t selected);
void Print_Constantes(SDL_Surface *ecran, ElementAnimal_Constantes *Selected, TTF_Font *police, int16_t ScreenH, int16_t ScreenW);
ElementAnimal_Constantes *Edit_Constantes(int16_t Plus_Ou_Moins, int16_t position, ElementAnimal_Constantes *Selected);
void Init_Tab(int16_t *tab);
void Print_Graphique(SDL_Surface *graph, int16_t GraphH, int16_t *nbr_espece, int16_t NBR_CASES, Grille *grill);
void Print_NbTour(SDL_Surface *ecran, Grille *grill, TTF_Font* police, int16_t ScreenH, int16_t ScreenW );

#endif // AFFICHAGE_H
