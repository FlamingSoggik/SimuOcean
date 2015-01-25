#ifndef SDL_PECHEUR_H
#define SDL_PECHEUR_H

#include "grille.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "elementanimal.h"
#include "elementpecheur.h"


void Afficher_Pecheurs( SDL_Surface *ecran, int taille_case, ElementPecheur **pt_Pecheur, int nbrpecheur, SDL_Rect Pos_Fenetre, SDL_Surface *rouge );

typedef struct SDLPecheur
{
    ElementPecheur *pt;
    SDL_Surface *SDL_Rouge;

}SDLPecheur;

void Selected_Pecheur(SDL_Surface *ecran, int taille_case, ElementPecheur *pt_Pecheur, SDL_Rect Pos_Fenetre, SDL_Surface *blanc );
void Commandes_Pecheur(SDL_Surface *ecran, SDL_Surface *Avancer, SDL_Surface *Construire, SDL_Surface *Pecher, TTF_Font* police, TTF_Font *police_underline, int Commande_Selected, int ScreenH, int ScreenW);

#endif // SDL_PECHEUR_H