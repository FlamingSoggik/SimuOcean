CPP=gcc    #Commande du compilateur
CFLAGS=`sdl-config --cflags` #Option d'optimisation du programme
LDFLAGS=`sdl-config --libs` #Linker
EXEC=SDL_01  #Nom du programme à modifier

all: ${EXEC}

${EXEC}:
	gcc `sdl-config --cflags` -g -Wall -Wextra -c *.c
	gcc `sdl-config --cflags --libs` -g -lSDL_ttf -o TestSDL01 *.o






clean:	
	rm -fr *.o

mrproper: clean
	rm -fr ${EXEC}
