#include <stdlib.h>
#include <stdio.h>

#include "elementanimal.h"
#include "elementpecheur.h"
#include "math.h"
#include "Bool.h"

#include "listetype.h"
#include <time.h>

#define max(a,b) (a>=b?a:b)

ElementAnimal_Constantes C_Vide;
ElementAnimal_Constantes C_Plancton;
ElementAnimal_Constantes C_Corail;
ElementAnimal_Constantes C_Bar;
ElementAnimal_Constantes C_Thon;
ElementAnimal_Constantes C_Pyranha;
ElementAnimal_Constantes C_Requin;
ElementAnimal_Constantes C_Orque;
ElementAnimal_Constantes C_Baleine;


ElementAnimal* New_ElementAnimal(Case *c, Type t){
	ElementAnimal* This = malloc(sizeof(ElementAnimal));
	if (!This) return NULL;
	if (ElementAnimal_Init(c, This, t) < 0){
		free(This);
		return NULL;
	}
	This->Free = Element_New_Free;
	return This;
}

char lienVersConstantes(ElementAnimal* This, Type t)
{
	switch (t){
		case PLANCTON:
			This->constantes=&C_Plancton;
			break;
		case CORAIL:
			This->constantes=&C_Corail;
			break;
		case BAR:
			This->constantes=&C_Bar;
			break;
		case THON:
			This->constantes=&C_Thon;
			break;
		case PYRANHA:
			This->constantes=&C_Pyranha;
			break;
		case REQUIN:
			This->constantes=&C_Requin;
			break;
		case ORQUE:
			This->constantes=&C_Orque;
			break;
		case BALEINE:
			This->constantes=&C_Baleine;
			break;
		default :
			//printf("Erreur lienVersConstantes %d\n", t);
			return ERR_TYPE_NOT_ANIMAL;
			break;
	}
	return 0;
}

void defineConstant()
{
	C_Vide.dureeSurvie=0;
	C_Vide.taille=0;
	C_Vide.tailleDuBide=0;
	C_Vide.sautMax=0;
	C_Vide.metabolisme=0;
	C_Vide.gestation=0;
	C_Vide.frequenceReproduction=0;

	C_Plancton.dureeSurvie=10000;
	C_Plancton.taille=2;
	C_Plancton.tailleDuBide=1;
	C_Plancton.sautMax=0;
	C_Plancton.metabolisme=0;
	C_Plancton.gestation=0;
	C_Plancton.frequenceReproduction=40;

	C_Corail.dureeSurvie=30;
	C_Corail.taille=2;
	C_Corail.tailleDuBide=3;
	C_Corail.sautMax=0;
	C_Corail.metabolisme=1;
	C_Corail.gestation=1;
	C_Corail.frequenceReproduction=25;

	C_Bar.dureeSurvie=30;
	C_Bar.taille=3;
	C_Bar.tailleDuBide=3;
	C_Bar.sautMax=3;
	C_Bar.metabolisme=1;
	C_Bar.gestation=1;
	C_Bar.frequenceReproduction=10;

	C_Thon.dureeSurvie=30;
	C_Thon.taille=4;
	C_Thon.tailleDuBide=3;
	C_Thon.sautMax=3;
	C_Thon.metabolisme=1;
	C_Thon.gestation=1;
	C_Thon.frequenceReproduction=15;

	C_Pyranha.dureeSurvie=60;
	C_Pyranha.taille=5;
	C_Pyranha.tailleDuBide=5;
	C_Pyranha.sautMax=3;
	C_Pyranha.metabolisme=1;
	C_Pyranha.gestation=1;
	C_Pyranha.frequenceReproduction=5;

	C_Requin.dureeSurvie=30;
	C_Requin.taille=6;
	C_Requin.tailleDuBide=4;
	C_Requin.sautMax=3;
	C_Requin.metabolisme=1;
	C_Requin.gestation=1;
	C_Requin.frequenceReproduction=2;

	C_Orque.dureeSurvie=60;
	C_Orque.taille=7;
	C_Orque.tailleDuBide=9;
	C_Orque.sautMax=3;
	C_Orque.metabolisme=1;
	C_Orque.gestation=2;
	C_Orque.frequenceReproduction=5;

	C_Baleine.dureeSurvie=30;
	C_Baleine.taille=8;
	C_Baleine.tailleDuBide=2;
	C_Baleine.sautMax=3;
	C_Baleine.metabolisme=1;
	C_Baleine.gestation=1;
	C_Baleine.frequenceReproduction=20;
}

void remplirListePredation(Grille* This)
{
	if (This->listePredationInitialise == 0){
		C_Plancton.listePredation = New_ListeType();
		C_Corail.listePredation = New_ListeType();
		C_Bar.listePredation = New_ListeType();
		C_Thon.listePredation = New_ListeType();
		C_Pyranha.listePredation = New_ListeType();
		C_Requin.listePredation = New_ListeType();
		C_Orque.listePredation = New_ListeType();
		C_Baleine.listePredation = New_ListeType();
		++This->listePredationInitialise;
	}
	else {
		C_Plancton.listePredation->Free(C_Plancton.listePredation);
		C_Plancton.listePredation = New_ListeType();

		C_Corail.listePredation->Free(C_Corail.listePredation);
		C_Corail.listePredation = New_ListeType();

		C_Bar.listePredation->Free(C_Bar.listePredation);
		C_Bar.listePredation = New_ListeType();

		C_Thon.listePredation->Free(C_Thon.listePredation);
		C_Thon.listePredation = New_ListeType();

		C_Pyranha.listePredation->Free(C_Pyranha.listePredation);
		C_Pyranha.listePredation = New_ListeType();

		C_Requin.listePredation->Free(C_Requin.listePredation);
		C_Requin.listePredation = New_ListeType();

		C_Orque.listePredation->Free(C_Orque.listePredation);
		C_Orque.listePredation = New_ListeType();

		C_Baleine.listePredation->Free(C_Baleine.listePredation);
		C_Baleine.listePredation = New_ListeType();
	}
	C_Corail.listePredation->Push(C_Corail.listePredation, PLANCTON);
	C_Bar.listePredation->Push(C_Bar.listePredation, PLANCTON);
	C_Bar.listePredation->Push(C_Bar.listePredation, PONT);
	C_Thon.listePredation->Push(C_Thon.listePredation, PLANCTON);
	C_Pyranha.listePredation->Push(C_Pyranha.listePredation, BAR);
	C_Pyranha.listePredation->Push(C_Pyranha.listePredation, THON);
	C_Pyranha.listePredation->Push(C_Pyranha.listePredation, PECHEUR);
	C_Requin.listePredation->Push(C_Requin.listePredation, BAR);
	C_Requin.listePredation->Push(C_Requin.listePredation, PECHEUR);
	C_Orque.listePredation->Push(C_Orque.listePredation, REQUIN);
	C_Orque.listePredation->Push(C_Orque.listePredation, PECHEUR);
	C_Baleine.listePredation->Push(C_Baleine.listePredation, PLANCTON);
	C_Baleine.listePredation->Push(C_Baleine.listePredation, PONT);
}

void viderListePredation(Grille* This)
{
	C_Plancton.listePredation->Free(C_Plancton.listePredation);
	C_Corail.listePredation->Free(C_Corail.listePredation);
	C_Bar.listePredation->Free(C_Bar.listePredation);
	C_Thon.listePredation->Free(C_Thon.listePredation);
	C_Pyranha.listePredation->Free(C_Pyranha.listePredation);
	C_Requin.listePredation->Free(C_Requin.listePredation);
	C_Orque.listePredation->Free(C_Orque.listePredation);
	C_Baleine.listePredation->Free(C_Baleine.listePredation);
	This->listePredationInitialise=0;
}

char ElementAnimal_Init(Case *c, ElementAnimal* This, Type t){
	if (c == NULL){
		puts("Erreur creation animal case parent vide");
	}
	This->caseParent=c;
	This->type=t;
	This->Clear = Element_Clear;
	This->dernierRepas = 0;
	This->GetDernierRepas = ElementAnimal_getDernierRepas;
	This->SetDernierRepas = ElementAnimal_setDernierRepas;
	This->GetSasiete = ElementAnimal_getSasiete;
	This->SetSasiete = ElementAnimal_setSasiete;
	This->derniereReproduction = 0;
	This->GetDerniereReproduction = ElementAnimal_getderniereReproduction;
	This->SetDerniereReproduction = ElementAnimal_setderniereReproduction;
	This->tour=ElementAnimal_tour;
	This->survie=ElementAnimal_survie;
	This->peutManger=ElementAnimal_peutManger;
	This->predation=ElementAnimal_predation;
	This->deplacement=ElementAnimal_deplacement;
	This->reproduction=ElementAnimal_reproduction;
	This->hasAlreadyPlayed=0;
	This->aFaitSonTour=ElementAnimal_aFaitSonTour;
	This->finDuTour=ElementAnimal_finDuTour;
	This->doitJouerCeTour=ElementAnimal_doitJouerCeTour;
	char ret = lienVersConstantes(This, t);
	This->sasiete = This->constantes->tailleDuBide;
	return ret;
}

unsigned int ElementAnimal_getDernierRepas(struct ElementAnimal *This){
	return This->dernierRepas;
}

void ElementAnimal_setDernierRepas(struct ElementAnimal *This, unsigned int toset){
	This->dernierRepas=toset;
}

void ElementAnimal_Free(struct ElementAnimal *This){
	Element_Clear((Element*)This);
	puts("Destruction de l'Animal statique.\n");
}

int ElementAnimal_getSasiete(struct ElementAnimal *This){
	return This->sasiete;
}

void ElementAnimal_setSasiete(struct ElementAnimal *This, int toset){
	This->sasiete=toset;
}

unsigned int ElementAnimal_getderniereReproduction(struct ElementAnimal *This){
	return This->derniereReproduction;
}

void ElementAnimal_setderniereReproduction(struct ElementAnimal *This, unsigned int toset){
	This->derniereReproduction=toset;
}

Bool ElementAnimal_survie(struct ElementAnimal *This){
	if (This->sasiete == 0 && This->caseParent->g->TourCourant - This->dernierRepas > This->constantes->dureeSurvie)
		return False;
	return True;
}

void ElementAnimal_tour(struct ElementAnimal *This){
	This->sasiete=max(This->sasiete-This->constantes->metabolisme, 0);
}

//void ElementAnimal_predation(ElementAnimal *This)
//{
//	Case***MatriceAccessiblePredation = NULL;
//	int i, j;
//	MatriceAccessiblePredation=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, 1);
//	Element* plusInteressant = NULL;
//	char flag = 0;
//	for(i=0; i<3 && flag == 0; ++i){
//		for(j=0; j<3  && flag == 0; ++j){
//			if (MatriceAccessiblePredation[i][j] != NULL){
//				//Il y a une Case à cette position
//				if(MatriceAccessiblePredation[i][j]->liste->HasDirt(MatriceAccessiblePredation[i][j]->liste) == 1)
//					continue;
////				if(MatriceAccessiblePredation[i][j]->liste->HasAPecheur(MatriceAccessiblePredation[i][j]->liste) == 1){

////					// Si il y a un pecheur
////					if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){
////						//sur un pont
////						if(This->peutManger(This, PONT) == True){
////							plusInteressant= MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste);
////							flag = 1;
////						}
////					} else {

////						//seul dans l'eau
////						if(This->peutManger(This, PECHEUR) == True){
////							plusInteressant = (Element*)MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste);
////							flag=1;
////						}
////					}
////				}
////				///Necessaire ou non ?
////				if (flag == 1){
////					continue;
////				}
////				if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){

////					//Cas ou la case ciblée à un pont
////					if(This->peutManger(This, PONT) == True){
////						plusInteressant = (Element*)MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste);
////						flag=1;
////					}


////				}
////				///Necessaire ou non ?
////				if (flag == 1){
////					continue;
////				}
//				if(MatriceAccessiblePredation[i][j]->liste->HasAnAnimal(MatriceAccessiblePredation[i][j]->liste) == 1){

//					//Elle contient un animal
//					ElementAnimal* current = (ElementAnimal*)MatriceAccessiblePredation[i][j]->liste->getAnimal(MatriceAccessiblePredation[i][j]->liste);
//					if (This->peutManger(This, current->type) == True && This->sasiete+current->constantes->taille < This->constantes->tailleDuBide){
//						//L'élément est mangeable mais est-ce le plus intéressant ?
//						if (plusInteressant == NULL){

//							//C'est le seul ou le premioer testé donc oui, il est plus intéressant que rien
//							//Mais est-il accessible?
//							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont){

//								//Je peux passer sous un pont donc oui, je vais le bouffer !
//								plusInteressant=(Element*)current;
//							}
//							else {

//								//Je ne passe pas sous un pont, merde, est-ce que je vais pouvoir le bouffer ?
//								if (MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){

//									// Ouf, il y a pas de pont je peux le bouffer
//									plusInteressant=(Element*)current;
//								}
//							}
//						}
//						else if(((ElementAnimal*)plusInteressant)->constantes->taille < current->constantes->taille){

//							// L'element semble plus intéressant, il faut maintenant vérifier qu'il ne soit pas sous un pont sans qu'on y ait accès
//							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont){
//								// Je passe sous un pont, let's go
//								plusInteressant=(Element*)current;
//							}
//							else if (MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){
//								//Je passe pas sous les ponts mais de toute façon, il y en a pas
//								plusInteressant=(Element*)current;
//							}
//						}
//						else if(((ElementAnimal*)plusInteressant)->constantes->taille == current->constantes->taille){
//							if (rand()%4 == 0){
//								// L'element semble plus intéressant, il faut maintenant vérifier qu'il ne soit pas sous un pont sans qu'on y ait accès
//								if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont){
//									// Je passe sous un pont, let's go
//									plusInteressant=(Element*)current;
//								}
//								else if (MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){
//									//Je passe pas sous les ponts mais de toute façon, il y en a pas
//									plusInteressant=(Element*)current;
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}

//	// On a plus besoin de la matrice temporaire donc on peux la supprimer :
//	for (i=0; i<3;++i){
//		free(MatriceAccessiblePredation[i]);
//	}
//	free(MatriceAccessiblePredation);


//	if(plusInteressant == NULL){
//		return;
//	}


//	if(plusInteressant->type==PECHEUR){
//		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, plusInteressant->caseParent->posX, plusInteressant->caseParent->posY);
//		This->caseParent->liste->deleteElement(This->caseParent->liste, (Element*)This);
//	} else if (plusInteressant->type == PONT){

//	} else {
//		This->dernierRepas=This->caseParent->g->TourCourant;
//		This->sasiete=This->sasiete+((ElementAnimal*)plusInteressant)->constantes->taille;
//		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, plusInteressant->caseParent->posX, plusInteressant->caseParent->posY);
//		plusInteressant->caseParent->liste->deleteElement(plusInteressant->caseParent->liste, plusInteressant);
//	}
//}

void ElementAnimal_predation(ElementAnimal *This)
{
	Case***MatriceAccessiblePredation = NULL;
	int i, j;
	MatriceAccessiblePredation=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, 1);
	ListeElem *le = New_ListeElem();
	char flag = 0;
	for(i=0; i<3 && flag == 0; ++i){
		for(j=0; j<3  && flag == 0; ++j){
			if (MatriceAccessiblePredation[i][j] != NULL){
				//Il y a une Case à cette position
				if(MatriceAccessiblePredation[i][j]->liste->HasDirt(MatriceAccessiblePredation[i][j]->liste) == 1)
					continue;
				//				if(MatriceAccessiblePredation[i][j]->liste->HasAPecheur(MatriceAccessiblePredation[i][j]->liste) == 1){

				//					// Si il y a un pecheur
				//					if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){
				//						//sur un pont
				//						if(This->peutManger(This, PONT) == True){
				//							le->Vider(le);
				//							le->Push(le, MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste));
				//							flag = 1;
				//							continue;
				//						}
				//					} else {

				//						//seul dans l'eau
				//						if(This->peutManger(This, PECHEUR) == True){
				//							le->Vider(le);
				//							le->Push(le, MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste));
				//							flag=1;
				//							continue;
				//						}
				//					}
				//				}
				//				if(MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == 1){

				//					//Cas ou la case ciblée à un pont
				//					if(This->peutManger(This, PONT) == True){
				//						le->Vider(le);
				//						le->Push(le, MatriceAccessiblePredation[i][j]->liste->getPont(MatriceAccessiblePredation[i][j]->liste));
				//						flag=1;
				//						continue;
				//					}
				//				}
				if(MatriceAccessiblePredation[i][j]->liste->HasAnAnimal(MatriceAccessiblePredation[i][j]->liste) == 1){

					//Elle contient un animal
					ElementAnimal* current = (ElementAnimal*)MatriceAccessiblePredation[i][j]->liste->getAnimal(MatriceAccessiblePredation[i][j]->liste);
					if (This->peutManger(This, current->type) == True && This->sasiete+current->constantes->taille < This->constantes->tailleDuBide){
						//L'élément est mangeable mais est-ce le plus intéressant ?

						if (le->Taille(le) == 0){
							//C'est le seul ou le premier testé donc oui, il est plus intéressant que rien
							//Mais est-il accessible?
							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont){

								//Je peux passer sous un pont donc oui, je vais le bouffer !
								le->Push(le, (Element*)current);
							}
							else {

								//Je ne passe pas sous un pont, merde, est-ce que je vais pouvoir le bouffer ?
								if (MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){

									// Ouf, il y a pas de pont je peux le bouffer
									le->Push(le, (Element*)current);
								}
							}
						}
						else if (((ElementAnimal*)le->Top->e)->constantes->taille < current->constantes->taille){
							// L'element semble plus intéressant, il faut maintenant vérifier qu'il ne soit pas sous un pont sans qu'on y ait accès
							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont){
								// Je passe sous un pont, let's go
								le->Vider(le);
								le->Push(le, (Element*)current);
							}
							else if (MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){
								//Je passe pas sous les ponts mais de toute façon, il y en a pas
								le->Vider(le);
								le->Push(le, (Element*)current);
							}
						}
						else if(((ElementAnimal*)le->Top->e)->constantes->taille == current->constantes->taille){

							// L'element semble plus intéressant, il faut maintenant vérifier qu'il ne soit pas sous un pont sans qu'on y ait accès
							if(This->constantes->taille < This->caseParent->g->TailleMaxSousPont){
								// Je passe sous un pont, let's go
								le->Push(le, (Element*)current);
							}
							else if (MatriceAccessiblePredation[i][j]->liste->HasAPont(MatriceAccessiblePredation[i][j]->liste) == False){
								//Je passe pas sous les ponts mais de toute façon, il y en a pas
								le->Push(le, (Element*)current);
							}
						}
					}
				}
			}
		}
	}


	// On a plus besoin de la matrice temporaire donc on peux la supprimer :
	for (i=0; i<3;++i){
		free(MatriceAccessiblePredation[i]);
	}
	free(MatriceAccessiblePredation);

	if(le->Taille(le) == 0){
		le->Free(le);
		return;
	}


	if(le->Top->e->type == PECHEUR){
		ElementPecheur *p = (ElementPecheur*)le->Top->e;
		p->mourir(p);
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, le->Top->e->caseParent->posX, le->Top->e->caseParent->posY);
		This->caseParent->liste->deleteElement(This->caseParent->liste, (Element*)This);
	} else if (le->Top->e->type == PONT){
		printf("%s:%d: Cas du pont ? wtf ?\n)", __FUNCTION__, __LINE__);
	} else {
		ElementAnimal *ea = (ElementAnimal*)le->getNieme(le, rand()%le->Taille(le));
		This->dernierRepas=This->caseParent->g->TourCourant;
		This->sasiete=This->sasiete+((ElementAnimal*)ea)->constantes->taille;
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, ea->caseParent->posX, ea->caseParent->posY);
		ea->caseParent->liste->deleteElement(ea->caseParent->liste, (Element*)ea);
	}
	le->Vider(le);
	le->Free(le);

}

void ElementAnimal_deplacement(ElementAnimal *This){
	int flag;
	Case*** MatriceAccessibleDeplacement = NULL;
	MatriceAccessibleDeplacement=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, This->constantes->sautMax);
	int deplX, deplY, isNeg;
	int i, j;
	flag=0;
	for(i=0;i<2*This->constantes->sautMax+1.0 && flag == 0;++i){
		for(j=0;j<2*This->constantes->sautMax+1.0 && flag == 0;++j){
			if (MatriceAccessibleDeplacement[i][j] != NULL)
				if (MatriceAccessibleDeplacement[i][j]->liste->HasAnAnimal(MatriceAccessibleDeplacement[i][j]->liste) == 0 && MatriceAccessibleDeplacement[i][j]->liste->HasDirt(MatriceAccessibleDeplacement[i][j]->liste) == 0)
					if (This->constantes->taille <= This->caseParent->g->TailleMaxSousPont || MatriceAccessibleDeplacement[i][j]->liste->HasAPont(MatriceAccessibleDeplacement[i][j]->liste) == 0)
						flag=1;
		}
	}

	if (flag == 0){
		for (i=0; i<2*This->constantes->sautMax+1.0;++i){
			free(MatriceAccessibleDeplacement[i]);
		}
		free(MatriceAccessibleDeplacement);
		return;
	}

	flag = 0;
	Case* caseDeDeplacement;
	while (flag == 0){
		deplX = 0;
		deplY = 0;
		while(deplX == 0 && deplY == 0){
			deplX = (rand()%(This->constantes->sautMax*2))+1-This->constantes->sautMax;
			deplY = (rand()%(This->constantes->sautMax*2))+1-This->constantes->sautMax;
		}
		isNeg=rand()%2;
		if(isNeg){
			deplX*=-1;
		}
		isNeg=rand()%2;
		if(isNeg){
			deplY*=-1;
		}
		caseDeDeplacement=MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY];
		if (caseDeDeplacement != NULL){
			if (caseDeDeplacement->liste->HasAnAnimal(caseDeDeplacement->liste) == 0 && caseDeDeplacement->liste->HasDirt(caseDeDeplacement->liste) == 0){
				if (This->constantes->taille <= This->caseParent->g->TailleMaxSousPont || caseDeDeplacement->liste->HasAPont(caseDeDeplacement->liste) == 0)
					flag=1;
			}
		}
	}
	if(This->sasiete-max(deplX, deplY)>=0){
		This->caseParent->g->moveFromTo(This->caseParent->g, (Element*)This, MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY]->posX, MatriceAccessibleDeplacement[This->constantes->sautMax+deplX][This->constantes->sautMax+deplY]->posY);
		This->sasiete=This->sasiete-max(deplX, deplY);
	}
	for (i=0; i<2*This->constantes->sautMax+1.0;++i){
		free(MatriceAccessibleDeplacement[i]);
	}
	free(MatriceAccessibleDeplacement);
}

void ElementAnimal_reproduction(ElementAnimal *This){
	if (This->sasiete < This->constantes->gestation*This->constantes->metabolisme){
		return;
	}
	if (This->derniereReproduction + This->constantes->frequenceReproduction >= This->caseParent->g->TourCourant){
		return;
	}
	int flag;
	Case*** MatriceAccessibleReproduction= NULL;
	MatriceAccessibleReproduction=This->caseParent->g->getMatriceVoisins(This->caseParent->g, This->caseParent->posX, This->caseParent->posY, 1);
	int i, j;
	flag=0;
	Case *caseNaissance = NULL;
	ListeCase *lcaseNaissance = New_ListeCase();
	ElementAnimal* e = NULL, *amoureux = NULL;
		for(i=0;i<3 && flag == 0;++i){
			for(j=0;j<3 && flag == 0;++j){
				if (MatriceAccessibleReproduction[i][j] != NULL && MatriceAccessibleReproduction[i][j]->liste->HasDirt(MatriceAccessibleReproduction[i][j]->liste) == 0) {
					if (MatriceAccessibleReproduction[i][j]->liste->HasAnAnimal(MatriceAccessibleReproduction[i][j]->liste)){
						e=(ElementAnimal*)MatriceAccessibleReproduction[i][j]->liste->getAnimal(MatriceAccessibleReproduction[i][j]->liste);
						if (e->type == This->type)
							amoureux=e;
					}
					else if (This->constantes->taille <= This->caseParent->g->TailleMaxSousPont || MatriceAccessibleReproduction[i][j]->liste->HasAPont(MatriceAccessibleReproduction[i][j]->liste) == 0){
						lcaseNaissance->Push(lcaseNaissance, MatriceAccessibleReproduction[i][j]);
					}
				}
			}
		}

		if (lcaseNaissance->Taille(lcaseNaissance) == 0|| amoureux == NULL){
			for (i=0; i<3;++i){
				free(MatriceAccessibleReproduction[i]);
			}
			free(MatriceAccessibleReproduction);
			return;
		}
		caseNaissance = lcaseNaissance->getNieme(lcaseNaissance, rand()%lcaseNaissance->Taille(lcaseNaissance));

	This->sasiete-=(This->constantes->gestation*This->constantes->metabolisme);
	caseNaissance->liste->Push(caseNaissance->liste, (Element*)New_ElementAnimal(caseNaissance, This->type));
	This->derniereReproduction=This->caseParent->g->TourCourant;
	for (i=0; i<3;++i){
		free(MatriceAccessibleReproduction[i]);
	}
	free(MatriceAccessibleReproduction);
}

Bool ElementAnimal_peutManger(ElementAnimal *This, Type t)
{
	if (This->constantes->listePredation->Contain(This->constantes->listePredation, t) == True){
		return True;
	}
	return False;
}


void ElementAnimal_aFaitSonTour(ElementAnimal *This)
{
	This->hasAlreadyPlayed=1;
}

void ElementAnimal_finDuTour(ElementAnimal *This)
{
	This->hasAlreadyPlayed=0;
}


Bool ElementAnimal_doitJouerCeTour(ElementAnimal *This)
{
	if (This->hasAlreadyPlayed == 1)
		return False;
	return True;
}
