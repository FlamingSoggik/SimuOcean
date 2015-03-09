#ifndef SDL_PECHEUR_H
#define SDL_PECHEUR_H

#include "grille.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "elementanimal.h"
#include "elementpecheur.h"


void Afficher_Pecheurs( SDL_Surface *ecran, int16_t taille_case, ElementPecheur **pt_Pecheur, int16_t nbrpecheur, SDL_Rect Pos_Fenetre, SDL_Surface *rouge );

typedef struct SDLPecheur
{
    ElementPecheur *pt;
    SDL_Surface *SDL_Rouge;

}SDLPecheur;

void Selected_Pecheur(SDL_Surface *ecran, int16_t taille_case, ElementPecheur *pt_Pecheur, SDL_Rect Pos_Fenetre, SDL_Surface *blanc );
void Commandes_Pecheur(SDL_Surface *ecran, SDL_Surface *Avancer, SDL_Surface *Construire, SDL_Surface *PecherCanne,  SDL_Surface *PecherFilet, TTF_Font* police, TTF_Font *police_underline, int16_t Commande_Selected, int16_t ScreenH, int16_t ScreenW);
void Sac_Pecheur( SDL_Surface *ecran, TTF_Font* police, ElementPecheur *pt_Pecheur, int16_t ScreenH, int16_t ScreenW );
#endif // SDL_PECHEUR_H
