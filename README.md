SimuOcean
=========

Simulation d'un océan en C

Utilisation :
Un makefile est à votre disposition, faites en bon usage.
Le programme généré s'appelle LifeGame et peut être lancé avec ou sans arguments.
* Le premier argument correspond à la taille de la grille
* Le second argument correspond au nombre de pecheurs en jeux
* Le dernier argument est un choix entre interface graphique (SDL) et l'interface terminal
	a : avec la Sdl
	s : sans la Sdl == interface terminal

Si les arguments ne sont pas fournis, ils sont récupérés par des scanf.

Lors du lancement sans SDL:
Le joueur qui doit jouer est entouré d'un délicat halo blanc
Il doit choisir ses actions (une par tour) :
	c : construire
		suivi d'une demande direction, envoyée à l'aide du pavé numérique (123456789) définissent les directions
	d : déplacement
		suivi d'une demande direction, envoyée à l'aide du pavé numérique (123456789) définissent les directions
	p : pecher
		suivi d'une demande de type de peche :
			c : par canne
				suivi d'une demande de dirrection : pecher en 68 rammene à pecher en 9 rammene à pecher sur la case au nord est (pour cette acquisition, la validation avec entrée est nécessaire)
			f : par filet
				suivi d'une demande de dirrection : lancer le filet en 68 rammene à lancer le filet en 9 rammene à lancer le filet sur la case au nord est  (pour cette acquisition, la validation avec entrée est nécessaire)

Lors du lancement avec la SDL:
Le joueur qui doit jouer est acculé d'un point blanc
	* Si il n'y a pas de pecheurs, le bouton parametres en haut à droite de l'interface permet d'afficher l'interface de réglage de l'écosysteme permettant :
		- de régler les constantes
		- d'afficher le graph d'évolution des espèces en appuyant sur le bouton corresponfdant en pas à droite
	* Si il y a un pecheur, il y a 4 elements sélectionnable :
		- avancer
			Une fois sélectionné, il suffit d'appuyer sur un nombre entre 1 et 9 pour avancer dans la dirrection correspondante
			Le pecheur a à nouveau la possibilité de construire
		- construire
			Une fois sélectionné, il suffit d'appuyer sur un nombre entre 1 et 9 pour construire dans la dirrection correspondante
			Le pecheur a à nouveau la possibilité de construire
		- pecher filet
			Pour pecher il faut cliquer sur le pecheur et relacher sur la cible que l'on tente de pecher
			La selection se fait automatiquement si l'action est réalisée avec un clic droit
		- pecher canne
			Pour pecher il faut cliquer sur le pecheur et relacher sur la case ou l'on souhaite lancer le filet
			La selection se fait automatiquement si l'action est réalisée avec un clic gauche
