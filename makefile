CPP=gcc    #Commande du compilateur
CFLAGS=`sdl-config --cflags` #Option d'optimisation du programme
LDFLAGS=`sdl-config --libs` #Linker
EXEC=SDL_01  #Nom du programme à modifier

all: ${EXEC}

${EXEC}:
	gcc `sdl-config --cflags` -Wall -Wextra -c *.c
	gcc `sdl-config --cflags --libs` -lm -lSDL_ttf -o LifeGame *.o






clean:	
	rm -fr *.o

mrproper: clean
	rm -fr ${EXEC}
