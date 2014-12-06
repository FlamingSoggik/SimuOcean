#ifndef ELEMENT_H
#define ELEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Type {
	VOID, PLANCTON, CORAIL, BAR, THON, POLLUTION, PYRANHA, REQUIN, ORQUE, BALEINE, PECHEUR, PONT
}Type;

typedef struct Element
{
		Type type;
		void (*Free)(struct Element *This);
		void (*Clear)(struct Element *This);
} Element;

//Constructeurs
Element Element_Create();
Element* New_Element();

//Initialisateur
void Element_Init(Element *This);

//Destructructeurs
void Element_New_Free(Element* This);
void Element_Free(Element *This);

//Others
void Element_Clear(Element *This);

#ifdef __cplusplus
}
#endif

#endif // ELEMENT_H
