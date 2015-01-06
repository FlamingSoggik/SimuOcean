TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image -lSDL_ttf

SOURCES += main.c \
    element.c \
	elementanimal.c \
    case.c \
    listeelem.c \
    listetype.c \
    grille.c \
	affichage.c \
    listecase.c \
    elementpecheur.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    element.h \
    elementanimal.h \
    case.h \
    listeelem.h \
    listetype.h \
    grille.h \
	Bool.h \
	affichage.h \
    listecase.h \
    elementpecheur.h

