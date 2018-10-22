#include "functions.h"
#include "solo.h"
#include "deux_joueurs.h"
#include "ordinateur.h"

/*POUR MODE 2 JOUEURS*/
int init_tab_bateau(Joueur *joueur, int type_joueur){

	if(joueur == NULL){
		return 0;
	}

	/*BATEAU 1*/
    joueur->tab_bateau[0] = initialiser_bateau(5, MLV_COLOR_BLUE, joueur->grille_boat, 10, 100, type_joueur);

    /*BATEAU 2*/
    joueur->tab_bateau[1] = initialiser_bateau(4, MLV_COLOR_GREEN, joueur->grille_boat, 10, 100, type_joueur);

    /*BATEAU 3*/
    joueur->tab_bateau[2] = initialiser_bateau(3, MLV_COLOR_YELLOW, joueur->grille_boat, 10, 100, type_joueur);

    /*BATEAU 4*/
    joueur->tab_bateau[3] = initialiser_bateau(3, MLV_COLOR_PURPLE, joueur->grille_boat, 10, 100, type_joueur);

    /*BATEAU 5*/
    joueur->tab_bateau[4] = initialiser_bateau(2, MLV_COLOR_PINK2, joueur->grille_boat, 10, 100, type_joueur);
    return 1;
}

/*POUR MODE ORDI*/
void bateau_aleatoire(int case_grille[], char* orientation){
	/*r�initialisation de orientation*/
	*orientation = ' ';
	int booloen;

	/* Definie les coordonn�es al�atoires */
	coords_aleatoires(case_grille);

	/* Tableau contenant les orientations possibles */
	char tab_orientation[] = {'h','v'};
	booloen = MLV_get_random_integer(0, 1);
	*orientation = tab_orientation[booloen];
}

void coords_aleatoires(int case_grille[]){
	/* G�n�re des coordonn�es al�atoires */
	case_grille[0] = MLV_get_random_integer(0, 9);
	case_grille[1] = MLV_get_random_integer(0, 9);
}

/* FONCTIONS COMMUNES AUX 3 MODES */
/*Demande un couple de coordonn�es X et Y puis l'orientation du bateau.
L'orientation n'est symbolis� que par 1 caract�re*/
void lire_coordonnees_bateau(int case_grille[], char* orientation, int debutX, int debutY){
	/*r�initialisation de orientation*/
	*orientation = ' ';
	char* test;

	/*verif des coordonn�es*/
	/*printf("Selection de la case la plus haute et la plus � gauche du bateau.\n");*/

	/*lit l'orientation du bateau*/
	while(!(test[0] == 'h' || test[0] == 'v')){
		MLV_wait_input_box(
			50, 60,
			150,17,
			MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_LIGHTYELLOW1,
			"orientation : ",
			&test
		);
	}

	*orientation = test[0];
	verif_coordonnees(case_grille, debutX, debutY);
}

/*Le but de cette fonction est de prendre une chaine de caract�re pour
la transformer en un duo de nb. La chaine doit �tre de la forme LettreNb
'Nb' est la coordonn�e de l'axe X et 'Lettre' la coordonn�es de l'axe Y
Nb est stock� dans case_grille[1]
L'indice correspondant � Lettre est stock� dans case_grille[0]*/
void verif_coordonnees(int case_grille[], int debutX, int debutY){
	int x, y;

	do{
		MLV_draw_text(debutX+20, 65, "cliquez sur la case que vous souhaitez", MLV_COLOR_BLACK);
		MLV_actualise_window();

		MLV_wait_mouse(&x, &y);
		/*printf("avant => x : %d, y : %d\n", x, y);*/
		x = (x-debutX)/35;
		y = (y-debutY)/35;
		/*printf("x : %d, y : %d\n", x, y);*/

	}while(!(x>=0 && x<=9 && y>=0 && y<=9));

	MLV_draw_filled_rectangle(debutX+20, 65, 300, 17, MLV_COLOR_LIGHTYELLOW1);
	MLV_actualise_window();
	case_grille[0] = x;
	case_grille[1] = y;
}

/*Alloue la matrice mat pour 2 dimensions de taille L et C
Rempli la matrice mat avec des '.' pour toutes ces cases
sauf pour la ligne des lettres et celle des chiffres
Pour les chiffres, le 0 symbolise en fait 10
return NULL si malloc ne marche pas
return la matrice si pas erreur*/
MLV_Color ** initialiser_grille(){
	int i, j;

	MLV_Color **mat = malloc(L*sizeof(MLV_Color*));

	if(mat == NULL){
		printf("Probl�me d'allocation de m�moire !\n");
		return NULL;
	}else{
		for(i=0; i<L; i++){
	        mat[i] = malloc(C*sizeof(MLV_Color));

	        if(mat[i] == NULL){
		    	printf("Probl�me d'allocation de m�moire !\n");
		    	return NULL;
		    }
	    }
	}

	/*initialise la grille*/
	for(i=0; i<L; i++){

		for(j=0; j<C; j++){
			mat[i][j] = MLV_COLOR_BLACK;
		}

	}

	return mat;

}

/*place le bateau de coordonn�es (coordX;coordY) dans la matrice mat
taille et orientation servent � connaitre les autres cases � remplir*/
void ajouter_bateau(Bateau bat, MLV_Color **mat){
	int k;
	
	if(bat.orientation == 'v'){
		for(k=0; k<bat.taille; k++){
			mat[bat.coordX][bat.coordY+k] = bat.indice;
		}
	} else{
		if(bat.orientation == 'h'){
			for(k=0; k<bat.taille; k++){
				mat[bat.coordX+k][bat.coordY] = bat.indice;
			}
		}
	}

}

/*return 1 si pas erreur / 0 si erreur
une erreur peut �tre soit une sortie de grille soit un chevauchement de bateaux
en fonction de l'orientation du bateau qu'on veut placer,
on regarde si la ligne form�e par celui-ci ne contient pas de '*'*/
int verifier_bateau(int coordX, int coordY, char orientation, int taille, MLV_Color **mat){
	int k, compteur_erreur = 0;
	char text_bateau[100];

	/*printf("taille : %d\n", taille);*/
	
	/*BATEAU VERTICAL*/
	if(orientation == 'v'){
		/*on fait taille-1 car on ne compte pas la case 'j' 2 fois
		test de sortie de grille*/
		/*printf("test vertical entre\n");*/

		if(coordY+taille-1 >= C){
			MLV_draw_text(50, 60, "Le bateau sort de la grille !", MLV_COLOR_RED);
			MLV_actualise_window();

			MLV_wait_seconds( 2 );

			MLV_draw_filled_rectangle(50, 60, 300, 17, MLV_COLOR_LIGHTYELLOW1);
			MLV_actualise_window();
			return 0;
		}

		/*test de non pr�sence d'un autre bateau*/
		for(k=0; k<taille; k++){
			if(mat[coordX][coordY+k] != MLV_COLOR_BLACK){
				compteur_erreur++;
				/*printf("nb erreurs : %d\n", compteur_erreur);*/
			}
		}
	} else{
		/*BATEAU HORIZONTAL*/
		if(orientation == 'h'){
			/*on fait taille-1 car on ne compte pas la case 'i' 2 fois
			test de sortie de grille*/
			/*printf("test horizontal entre\n");*/

			if(coordX+taille-1 >= L){
				MLV_draw_text(50, 60, "Le bateau sort de la grille !", MLV_COLOR_RED);
				MLV_actualise_window();

				MLV_wait_seconds( 2 );

				MLV_draw_filled_rectangle(50, 60, 300, 17, MLV_COLOR_LIGHTYELLOW1);
				MLV_actualise_window();
				return 0;
			}

			/*test de non pr�sence d'un autre bateau*/
			for(k=0; k<taille; k++){
				if(mat[coordX+k][coordY] != MLV_COLOR_BLACK){
					compteur_erreur++;
					/*printf("nb erreurs : %d\n", compteur_erreur);*/
				}
			}
		}
	}

	/*test et potentiel affichage du nb d'erreur*/
	if(compteur_erreur == 0){
		return 1;
	}else{
		sprintf(text_bateau, "%d cases sont deja occupees !", compteur_erreur);

		MLV_draw_text(50, 60, text_bateau, MLV_COLOR_RED);
		MLV_actualise_window();

		MLV_wait_seconds( 2 );

		MLV_draw_filled_rectangle(50, 60, 300, 17, MLV_COLOR_LIGHTYELLOW1);
		MLV_actualise_window();
		/*printf("Attention, ce bateau chevauche %d cases d�j� pleines !\n", compteur_erreur);*/
		return 0;
	}
}

/*Cette fonction lit des coordonn�es et une orientation
ensuite elle appelle la fonction pour v�rifier si on peut placer le bateau
lorsqu'aucune erreur n'apparait, elle ajoute le bateau � la grille*/
Bateau initialiser_bateau(int taille_bat, MLV_Color indice, MLV_Color **mat, int debutX, int debutY, int type_joueur){
	int verif_bateau=0;
	int case_bateau[CoordMAX];
	char orientation;
	Bateau bat;
	char text_bateau[100];


	sprintf(text_bateau, "Selection du bateau de dimension %d !", taille_bat);
	MLV_draw_text(30, 20, text_bateau, MLV_COLOR_BLACK);

	do{
		if(type_joueur == 1){
			lire_coordonnees_bateau(case_bateau, &orientation, debutX, debutY);
		}else{
			bateau_aleatoire(case_bateau, &orientation);
		}
		
		/*printf("case bateau 1 : %d\n", case_bateau[1]);*/
		verif_bateau = verifier_bateau(case_bateau[0], case_bateau[1], orientation, taille_bat, mat);
		/*printf("verif bateau : %d\n", verif_bateau);*/

	}while(verif_bateau == 0);

	/* Entr�e des valeurs dans la structure */
	bat.coordX = case_bateau[0];
	bat.coordY = case_bateau[1];
	bat.orientation = orientation;
	bat.taille = taille_bat;
	bat.indice = indice;

	/*printf("coordX bat : %d\n", bat.coordX);
	printf("orientation bat : %c\n", bat.orientation);*/

	MLV_draw_filled_rectangle(30, 20, 300, 17, MLV_COLOR_LIGHTYELLOW1);
	MLV_actualise_window();

	ajouter_bateau(bat, mat);
	
	if(type_joueur == 1){
		afficher_grille(mat, debutX, debutY);
	}

	return bat;
}

/*AFFICHAGE GRILLE*/
void afficher_grille(MLV_Color **mat, int debutX, int debutY){
	int i, j;

	for(i=0; i<L; i++){
		for(j=0; j<C; j++){
			MLV_draw_filled_rectangle( i*(30+5)+debutX, j*(30+5)+debutY, 30, 30, mat[i][j] );
			/*printf("%d\n", (i*30)+20);*/
		}
	}

	MLV_actualise_window();
}

/* coords doit contenir : coords[0] = axe Y et coords[1] = axe X
return -1 si le tir a d�j� eus lieu dans la case pass�e en param�tre!
return 0 si case touch� ne contient rien
return 1 si la case touch�e contient une partie de bateau*/
int tirer (Bateau * tab_bateau, MLV_Color **grille, int *coords, MLV_Color **tir){
	int i;

	/*V�rification qu'aucun tir n'a �t� effectu� avant dans cette case !*/
	if(tir[coords[0]][coords[1]] != MLV_COLOR_BLACK){
		MLV_draw_text(530, 40, "Vous avez deja tire sur cette case !", MLV_COLOR_BLACK);
        MLV_actualise_window();
        MLV_wait_seconds(2);

		return -1;
	}

	/*printf("Fonction tirer marche !\n");*/
	
	/*v�rification que la case contient une partie de bateau*/
	if(grille[coords[0]][coords[1]] != MLV_COLOR_BLACK){

		/*printf("Fonction tirer avec bateau\n");*/

		for(i=0; i<NBBOAT; i++){
			if(grille[coords[0]][coords[1]] == tab_bateau[i].indice){
				tab_bateau[i].taille--;

				if(tab_bateau[i].taille == 0){
					MLV_draw_text(530, 40, "Le bateau est coule !", MLV_COLOR_RED);
        			MLV_actualise_window();

        			MLV_wait_seconds(2);

					return 2;
				}
			}

		}

		MLV_draw_text(530, 40, "Le bateau est touche !", MLV_COLOR_RED);
        MLV_actualise_window();
        MLV_wait_seconds(2);

        return 1;
        /* printf("Coordonn�es : %d / %d", i,y); */
	}

	/*printf("fonction tirer avec eau\n");*/
	/*Aucun des autres cas => � l'eau*/
	MLV_draw_text(530, 40, "A l'eau ! Loupe !", MLV_COLOR_RED);
    MLV_actualise_window();
    MLV_wait_seconds(2);

	return 0;
}

/* Envoyer un boleen pour voir si c'�tait touch� ou plouf 
Met le bon caract�re dans la case pass�e en param�tre*/
void creerGrilleTir(MLV_Color **grille, int *coords, int result_tir){

    if(result_tir == 1){
    	grille[coords[0]][coords[1]] = MLV_COLOR_ORANGE;
    }
    else if(result_tir == 2){
    	grille[coords[0]][coords[1]] = MLV_COLOR_RED;
    }else{
    	grille[coords[0]][coords[1]] = MLV_COLOR_CYAN;
    }

}

/*return 1 si matrice vid� || 0 si matrice d�j� vide*/
int free_mat(MLV_Color **mat){
	int i=0;

	if(mat == NULL){
		return 0;
	}

	for(i=0; i<L; i++){
		free(mat[i]);
	}

	free(mat);
	return 1;
}
