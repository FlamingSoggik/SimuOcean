TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_ttf

SOURCES += main.c \
    element.c \
    elementanimal.c \
    case.c \
    listeelem.c \
    listetype.c \
    grille.c \
    affichage.c \
    listecase.c \
    elementpecheur.c \
    elementpont.c \
    elementterre.c \
    changermodeterminal.c \
    stringreplace.c \
    sdl_pecheur.c

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
    elementpecheur.h \
    elementpont.h \
    elementterre.h \
    changermodeterminal.h \
    stringreplace.h \
    sdl_pecheur.h
