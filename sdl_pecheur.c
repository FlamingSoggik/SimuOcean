//#include "sdl_pecheur.h"
//#include "elementpecheur.h"
//#include "affichage.h"

////Actualiser(carre[i][j], Selected_Type_Case, (j*taille_case+j+pos_fenetre.x), (i*taille_case+i+pos_fenetre.y));

//Afficher_Pecheurs( SDL_Surface *ecran, int taille_case, ElementPecheur **pt_Pecheur, int nbrpecheur, SDL_Rect Pos_Fenetre, SDL_Surface *rouge )
//{
//     int i=0;
//     SDL_Rect Pos_Pecheur;
//     for (; i<nbrpecheur; i++)
//     {
//         Pos_Pecheur.x=pt_Pecheur[i]->caseParent->posX; //Position sur la grille, pas sur l'écran
//         Pos_Pecheur.y=pt_Pecheur[i]->caseParent->posY;

//         Pos_Pecheur.x=(Pos_Pecheur.x)*taille_case+(Pos_Fenetre.x)

//         SDL_BlitSurface(rouge, NULL, ecran, Pos_Pecheur);
//     }

//}






////typedef struct SDLPecheur
////{
////    ElementPecheur *pt;
////    SDL_Surface *SDL_Rouge;

////}SDLPecheur;



//SDLPecheur** Init_Pecheurs( SDL_Surface *ecran, int taille_case, ElementPecheur **pt_Pecheur, int nbrpecheur,  )
//{
//    SDLPecheur **New_Pecheurs= malloc(sizeof(SDLPecheur)*nbrpecheur);
//    int i=0;
//    SDL_Surface *Rouge;
//    Rouge=SDL_CreateRGBSurface(SDL_HWSURFACE, taille_case, taille_case, 32, 0, 0, 0, 0);
//    SDL_FillRect(Rouge, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));

//    for(; i<nbrpecheur; i++)
//    {
//        New_Pecheur[i]->pt=pt_Pecheur[i];
//        Blit_Image(ecran, )
//    }




//    pt_Pecheur->caseParent->

//    return New_Pecheur;

//}


//Deplace_Pecheur ( )


//}
