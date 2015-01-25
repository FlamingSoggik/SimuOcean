SimuOcean
=========

Simulation d'un océan en C

Utilisation :
Un makefile est à votre disposition, faites en bon usage.
Le programme généré s'appelle TestSDL01 et peut être lancé avec ou sans arguments.
* Le premier argument correspond à la taille de la grille
* Le second argument correspond au nombre de pecheurs en jeux
* Le dernier argument est un choix entre interface graphique (SDL) et l'interface terminal
	a : avec la Sdl
	s : sans la Sdl

Lors du lancement sans SDL:
Il est possible de jouer, le joueur qui doit joué est entouré d'un délicat halo blanc
Il doit choisir ses actions (une par tour) :
	c : construire
		suivi d'une demande direction, envoyée à l'aide du pavé numérique (123456789) définissent les directions
	d : déplacement
		suivi d'une demande direction, envoyée à l'aide du pavé numérique (123456789) définissent les directions
	p : pecher
		suivi d'une demande de type de peche :
			c : par canne
				suivi d'une demande de dirrection : pecher en 68 rammene à pecher en 9 rammene à pecher sur la case au nord est
			f : par filet
				suivi d'une demande de dirrection : lancer le filet en 68 rammene à lancer le filet en 9 rammene à lancer le filet sur la case au nord est

Lors du lancement avec la SDL:
	Si il n'y a pas de pecheurs, le bouton "moins" en haut à droite de l'interface
