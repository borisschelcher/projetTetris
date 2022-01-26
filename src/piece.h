/* piece.h */
#ifndef PIECE_H
#define PIECE_H

#include "shapes.h"

enum colors{ BLUE = 1, GRAY, ORANGE, YELLOW, GREEN, PURPLE, RED, GHOST } colors; // Les couleurs de chaque pi�ce, GHOST est pour la pi�ce fant�me
enum kinds{ O, I, S, Z, L, J, T} kinds;

/* Les coordonn�es du point de pivot de la pi�ce */
#define PIVOT_X 2
#define PIVOT_Y 1

typedef struct Piece Piece;
struct Piece {
    int kind; // Le type de la pi�ce
    int orientation; // Son orientation (sa rotation courante)
    int color; // Sa couleur
    int pos_x; // Son ordonn�e dans l'aire de jeu
    int pos_y; // Son abscisse dans l'aire de jeu
};

#endif