TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    element.c \
    elementanimal.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    element.h \
    elementanimal.h

