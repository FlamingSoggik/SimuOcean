TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    element.c \
    elementanimal.c \
    case.c \
    listeelem.c \
    listetype.c \
    grille.c \
#    affichage.c \
    listecase.c

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
#    affichage.h \
    listecase.h

