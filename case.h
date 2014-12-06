#ifndef CASE_H
#define CASE_H

#include "listeelem.h"

typedef struct Case {
	ListeElem *liste;
	void(*Free)();
	void(*Clear)(struct Case*);
	void (*Print)(struct Case *This);
}Case;

Case Case_Create();
void Case_Free(Case *This);
void Case_Clear(Case *This);
void Case_Print(Case *This);

#endif // CASE_H
