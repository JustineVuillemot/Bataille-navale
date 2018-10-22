#include "functions.h"
#include "solo.h"
#include "deux_joueurs.h"
#include "ordinateur.h"
/*
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
*/
int main( int argc, char *argv[] ){
    int x, y, result_fct_mode=0;
    /*MLV_Color mlv_color_beige;

    mlv_color_beige = MLV_rgba(203, 172, 139, 255);*/

    /*
    // Créé et affiche la fenêtre
    */
    MLV_create_window( "bataille navale Justine et Pauline", "Bataille Navale", 1000, 700 );
    MLV_draw_filled_rectangle( 0, 0, 1000, 700, MLV_COLOR_LIGHTYELLOW1 );

    /*
    // Affiche "Bonjour !" a l'écran 
    */
    MLV_draw_text( /*en-tête*/
        400, 100, 
        "Quel mode voulez-vous choisir ?",
        MLV_COLOR_BLACK
    );

    MLV_draw_filled_rectangle( 350, 200, 300, 100, MLV_COLOR_BLACK ); /*haut*/
    MLV_draw_filled_rectangle( 350, 350, 300, 100, MLV_COLOR_BLACK ); /* milieu */
    MLV_draw_filled_rectangle( 350, 500, 300, 100, MLV_COLOR_BLACK ); /*bas*/

    MLV_draw_text( /*haut*/
        464, 225, 
        "Mode solo",
        MLV_COLOR_WHITE
    );

    MLV_draw_text( /*milieu*/
        417, 375, 
        "Mode contre ordinateur",
        MLV_COLOR_WHITE
    );

    MLV_draw_text( /*bas*/
        435, 525, 
        "Mode deux joueurs",
        MLV_COLOR_WHITE
    );

    /*
    // Met a jour l'affichage.
    */
    MLV_actualise_window();

    /*
    // Attend un click.
    */
    MLV_wait_mouse(&x, &y);

    /*clack haut*/
    if( x >= 350 && x <=650 && y >= 200 && y<= 300 ){
        MLV_draw_filled_rectangle( 0, 0, 1000, 700, MLV_COLOR_LIGHTYELLOW1 );
        /*MLV_draw_text(
            470,100, 
            "Mode Solo !",
            MLV_COLOR_BLACK
        ); */
        result_fct_mode = mode_solo();
    }

    /*click milieu*/
    if( x >= 350 && x <=650 && y >= 350 && y<= 450 ){
        MLV_draw_filled_rectangle( 0, 0, 1000, 700, MLV_COLOR_LIGHTYELLOW1 );
        /*MLV_draw_text(
            460, 100, 
            "Contre l'ordinateur !",
            MLV_COLOR_BLACK
        );*/
        result_fct_mode = ordinateur();
    }

    /*click bas*/
    if( x >= 350 && x <=650 && y >= 500 && y<= 600 ){
        MLV_draw_filled_rectangle( 0, 0, 1000, 700, MLV_COLOR_LIGHTYELLOW1 );
        /*MLV_draw_text(
            470, 100, 
            "Deux joueurs !",
            MLV_COLOR_BLACK
        );*/
        result_fct_mode = mode_deux_joueurs();
    }

    printf("retour main : %d\n", result_fct_mode);

    MLV_actualise_window();
    MLV_wait_seconds( 2 );
    /*
    // Ferme la fenêtre
    */
    MLV_free_window();

    return 0;
}
