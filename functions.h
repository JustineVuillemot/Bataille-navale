#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

#define CoordMAX 3
#define NBBOAT 5
#define L 10
#define C 10

typedef struct Bateau{
	char orientation;
	int taille;
	int coordX;
	int coordY;
	MLV_Color indice;
}Bateau;

typedef struct Joueur{
	MLV_Color **grille_boat;
	MLV_Color **grille_tirs;
	Bateau *tab_bateau;
	int point;
}Joueur;

/*fonctions communes aux modes de jeux*/
MLV_Color ** initialiser_grille();
int init_tab_bateau(Joueur *joueur, int type_joueur);
void bateau_aleatoire(int case_grille[], char* orientation);
void coords_aleatoires(int case_grille[]);
void verif_coordonnees(int case_grille[], int debutX, int debutY);
void afficher_grille(MLV_Color **mat, int debutX, int debutY);
void lire_coordonnees_bateau(int case_grille[], char* orientation, int debutX, int debutY);
void ajouter_bateau(Bateau bat, MLV_Color **mat);
int verifier_bateau(int coordX, int coordY, char orientation, int taille, MLV_Color **mat);
Bateau initialiser_bateau(int taille_bat, MLV_Color indice, MLV_Color **mat, int debutX, int debutY, int type_joueur);
int tirer (Bateau * tab_bateau, MLV_Color **grille, int *coords, MLV_Color **tir);
void creerGrilleTir(MLV_Color **grille, int *coords, int result_tir);
int free_mat(MLV_Color **mat);


#endif
