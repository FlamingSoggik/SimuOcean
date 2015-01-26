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


SDL_Surface* Charger(int taille_case, SDL_Surface *ecran, int type); // Charge les différents type de case.
void Actualiser(SDLCase* Case_Tab, SDL_Surface **Case_Type, int absisse, int ordonnee);
Grille *SDL_Print(struct Grille *grill);
SDL_Surface** Select_Type(Grille *grill, SDL_Surface **Tab_Type, int i, int j, int *tab);


void Spinner_Print(SDL_Surface *ecran, int Plus_Ou_Moins, int ScreenH, int ScreenW, SDL_Surface *srf);
SDL_Surface* Charger_Image(const char* fic);
void Blit_Image(SDL_Surface* ecran,SDL_Surface* srf,int x,int y);
ElementAnimal_Constantes *Select_Legende(SDL_Surface** Legendes_Surface, TTF_Font* police, TTF_Font *police_underline, int selected);
void Print_Constantes(SDL_Surface *ecran, ElementAnimal_Constantes *Selected, TTF_Font *police, int ScreenH, int ScreenW);
ElementAnimal_Constantes *Edit_Constantes(int Plus_Ou_Moins, int position, ElementAnimal_Constantes *Selected);
void Init_Tab(int *tab);
void Print_Graphique(SDL_Surface *graph, int GraphH, int *nbr_espece, int NBR_CASES, Grille *grill);
void Print_NbTour(SDL_Surface *ecran, Grille *grill, TTF_Font* police, int ScreenH, int ScreenW );

#endif // AFFICHAGE_H
