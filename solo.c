#include "functions.h"
#include "solo.h"
#include "deux_joueurs.h"

int mode_solo(){
    int result_tir = -1;
    MLV_Color **grille=NULL, **tir;
    int case_bateau[2], nb_cases = 17;
    /*char orientation;*/
    Bateau *tab_bateau;

    grille = initialiser_grille();
    if(grille == NULL){
        return 0;
    }

    tir = initialiser_grille();
    if(tir == NULL){
        return 0;
    }

    tab_bateau = malloc(5*sizeof(Bateau));
    if(tab_bateau == NULL){
        return 0;
    }

    /*printf("Voici votre grille :\n");*/
    afficher_grille(grille, 10, 100);

    /*BATEAU 1*/
    tab_bateau[0] = initialiser_bateau(5, MLV_COLOR_BLUE, grille, 10, 100, 1);

    /*BATEAU 2*/
    tab_bateau[1] = initialiser_bateau(4, MLV_COLOR_GREEN, grille, 10, 100, 1);

    /*BATEAU 3*/
    tab_bateau[2] = initialiser_bateau(3, MLV_COLOR_YELLOW, grille, 10, 100, 1);

    /*BATEAU 4*/
    tab_bateau[3] = initialiser_bateau(3, MLV_COLOR_PURPLE, grille, 10, 100, 1);

    /*BATEAU 5*/
    tab_bateau[4] = initialiser_bateau(2, MLV_COLOR_HOTPINK2, grille, 10, 100, 1);

    /*Grille de tir mise en place*/
    MLV_draw_text(30, 20, "Ceci est votre grille de bateaux !", MLV_COLOR_BLACK);
    afficher_grille(tir, 510, 100);
    MLV_draw_text(530, 20, "Ceci est votre grille pour tirer !", MLV_COLOR_BLACK);

	/* Debut des tests de fonction : fonction tirer */

    while(nb_cases > 0){

        /*printf("Quelle case voulez-vous toucher ?\n");*/
        MLV_draw_text(530, 40, "Quelle case voulez-vous toucher ?", MLV_COLOR_BLACK);
        MLV_actualise_window();

        verif_coordonnees(case_bateau, 510, 100);

        MLV_draw_filled_rectangle(530, 40, 300, 17, MLV_COLOR_LIGHTYELLOW1);
        MLV_actualise_window();

        /*scanf("%s", coord);
        printf("Coordonnée : %s\n", coord);*/

        result_tir = tirer(tab_bateau, grille, case_bateau, tir);

        MLV_draw_filled_rectangle(530, 40, 300, 17, MLV_COLOR_LIGHTYELLOW1);
        MLV_actualise_window();

        if(result_tir != -1){
            creerGrilleTir(tir, case_bateau, result_tir);
            /*printf("Voici vos tirs :\n");*/
            afficher_grille(tir, 510, 100);

            if(result_tir == 1 || result_tir == 2){
                nb_cases--;
                creerGrilleTir(grille, case_bateau, 2);
            }
        }

        /*nb_cases = 0;*/
    }

    MLV_draw_filled_rectangle( 0, 0, 1000, 700, MLV_COLOR_LIGHTYELLOW1 );
    MLV_draw_text(460, 450, "Vous avez gagne !", MLV_COLOR_BLACK);

    free_mat(grille);
    free_mat(tir);
    free(tab_bateau);

    return 0;
}
