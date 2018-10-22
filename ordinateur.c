#include "functions.h"
#include "ordinateur.h"

int ordinateur(){
    int result_tir = -1;
    int result_bat;
    int case_bateau[2];
    /*MLV_Color **grille=NULL, **tir;*/

    Joueur *joueur1, *ordinateur;

    joueur1 = malloc(sizeof(Joueur));
    ordinateur = malloc(sizeof(Joueur));

    if(joueur1 == NULL || ordinateur == NULL){
        return 0;
    }

    /*char orientation;*/
    /* Bateau *tab_bateau;*/

    joueur1->point = 17;
    ordinateur->point = 17;

    joueur1->grille_boat = initialiser_grille();
    if(joueur1->grille_boat == NULL){
        return 0;
    }

    ordinateur->grille_boat = initialiser_grille();
    if(joueur1->grille_boat == NULL){
        return 0;
    }

    joueur1->grille_tirs = initialiser_grille();
    if(joueur1->grille_tirs == NULL){
        return 0;
    }

    ordinateur->grille_tirs = initialiser_grille();
    if(ordinateur->grille_tirs == NULL){
        return 0;
    }

    joueur1->tab_bateau = malloc(5*sizeof(Bateau));
    if(joueur1->tab_bateau == NULL){
        return 0;
    }

    ordinateur->tab_bateau = malloc(5*sizeof(Bateau));
    if(ordinateur->tab_bateau == NULL){
        return 0;
    }

    /* Initialisation joueur 1 */
    /*printf("Grille du joueur 1 :\n");*/
    afficher_grille(joueur1->grille_boat, 10, 100);

    /*printf("Initialisation des bateaux du joueur 1 :\n");*/
    result_bat = init_tab_bateau(joueur1, 1);

    if(result_bat == 0){
        return 0;
    }

    /* Initialisation joueur 2 */
    /*printf("Grille du joueur 2 :\n");*/
    /*afficher_grille(ordinateur->grille_boat, 10, 100);*/


    /*printf("Initialisation des bateaux du joueur 2 :\n");*/
    MLV_draw_text(530, 600, "TOUR ORDINATEUR", MLV_COLOR_RED);
    /*MLV_wait_seconds(3);*/
    result_bat = init_tab_bateau(ordinateur, 0);
    MLV_draw_filled_rectangle(530, 600, 300, 17, MLV_COLOR_LIGHTYELLOW1);

    if(result_bat == 0){
        return 0;
    }


    /*Grille de tir mise en place*/
    MLV_draw_text(30, 20, "Ceci est votre grille de bateaux !", MLV_COLOR_BLACK);
   /* afficher_grille(tir, 510, 100);*/
    MLV_draw_text(530, 20, "Ceci est votre grille pour tirer !", MLV_COLOR_BLACK);

	/* Debut des tests de fonction : fonction tirer */

    while(joueur1->point != 0 && ordinateur->point != 0){

        /*    JOUEUR 1   */

        afficher_grille(joueur1->grille_boat, 10, 100);
        afficher_grille(joueur1->grille_tirs, 510, 100);
        MLV_draw_filled_rectangle(530, 600, 300, 17, MLV_COLOR_LIGHTYELLOW1);
        MLV_draw_text(530, 600, "JOUEUR 1", MLV_COLOR_BLACK);

        /*printf("Quelle case voulez-vous toucher ?\n");*/
        MLV_draw_text(530, 40, "Quelle case voulez-vous toucher ?", MLV_COLOR_BLACK);
        MLV_actualise_window();

        verif_coordonnees(case_bateau, 510, 100);

        MLV_draw_filled_rectangle(530, 40, 300, 17, MLV_COLOR_LIGHTYELLOW1);
        MLV_actualise_window();

        /*scanf("%s", coord);
        printf("Coordonnée : %s\n", coord);*/

        result_tir = tirer(ordinateur->tab_bateau, ordinateur->grille_boat, case_bateau, joueur1->grille_tirs);

        MLV_draw_filled_rectangle(530, 40, 300, 17, MLV_COLOR_LIGHTYELLOW1);
        MLV_actualise_window();

        if(result_tir != -1){
            creerGrilleTir(joueur1->grille_tirs, case_bateau, result_tir);
            afficher_grille(joueur1->grille_tirs, 510, 100);

            MLV_wait_seconds(2);

            if(result_tir == 1 || result_tir == 2){
                ordinateur->point--;
                creerGrilleTir(ordinateur->grille_boat, case_bateau, 2);
            }

        }

        if(ordinateur->point != 0){

            /*    ORDI  */

            /*afficher_grille(ordinateur->grille_boat, 10, 100);
            afficher_grille(ordinateur->grille_tirs, 510, 100);*/
            MLV_draw_filled_rectangle(530, 600, 300, 17, MLV_COLOR_LIGHTYELLOW1);
            MLV_draw_text(530, 600, "TOUR ORDINATEUR", MLV_COLOR_RED);

            /*printf("Quelle case voulez-vous toucher ?\n");*/
            /*MLV_draw_text(530, 40, "Quelle case voulez-vous toucher ?", MLV_COLOR_BLACK);*/
            MLV_actualise_window();

            coords_aleatoires(case_bateau);

            /*MLV_draw_filled_rectangle(530, 40, 300, 17, MLV_COLOR_LIGHTYELLOW1);
            MLV_actualise_window();*/

            result_tir = tirer(joueur1->tab_bateau, joueur1->grille_boat, case_bateau, ordinateur->grille_tirs);

            MLV_draw_filled_rectangle(530, 40, 300, 17, MLV_COLOR_LIGHTYELLOW1);
            MLV_actualise_window();

            if(result_tir != -1){
                creerGrilleTir(ordinateur->grille_tirs, case_bateau, result_tir);
                /*afficher_grille(ordinateur->grille_tirs, 510, 100);
                MLV_wait_seconds(2);*/

                if(result_tir == 1 || result_tir == 2){
                    joueur1->point--;
                    creerGrilleTir(joueur1->grille_boat, case_bateau, 2);
                }else{
                    creerGrilleTir(joueur1->grille_boat, case_bateau, 0);
                }

            }
        }

    }

    /*printf("Le jeu est terminé !\n");*/

    MLV_draw_filled_rectangle(0, 0, 1000, 700, MLV_COLOR_LIGHTYELLOW1);

    if(joueur1->point == 0){
        MLV_draw_text(460, 450, "Le joueur 2 gagne !", MLV_COLOR_BLACK);
    }
    else{
        MLV_draw_text(460, 450, "Le joueur 1 gagne !", MLV_COLOR_BLACK);
    }

    /*FREE ELEMENT J1*/
    free_mat(joueur1->grille_boat);
    free_mat(joueur1->grille_tirs);
    free(joueur1->tab_bateau);
    free(joueur1);

    /*FREE ELEMENT ORDI*/
    free_mat(ordinateur->grille_boat);
    free_mat(ordinateur->grille_tirs);
    free(ordinateur->tab_bateau);
    free(ordinateur);

    return 0;
}
