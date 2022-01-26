/* board.h */
#ifndef BOARD_H
#define BOARD_H
#define BOARD_HEIGHT 20 // La hauteur de l'aire de jeu
#define BOARD_WIDTH  10 // Sa largeur
#define ORIGIN_Y 0 // L'ordonnée du point de pivot
#define ORIGIN_X 5 // Son absisse


#include "piece.h"
#include <stdbool.h>
#include <stdlib.h>

/*
* FREE : indique que le point du tableau est vide
* FILLED: indique que le point du tableau contient un bloc (1 ou 2)
*/
enum states { FREE, FILLED };

typedef struct Board Board;
struct Board {
    Piece* current_piece; // La pièce courante se trouvant sur l'aire de jeu
    int area[BOARD_HEIGHT][BOARD_WIDTH]; // Le tableau représentant l'aire de jeu
    bool* piece_is_moving;
};

void init_board(Board* board);

void flood(int i, int j, int px, int py, int k, int o, int value, bool* visited[SIZE][SIZE], Board* board);
void flagged_flood(int i, int j, int px, int py, int k, int o, bool* flag, bool* visited[SIZE][SIZE], Board* board);
void flood_fill(int i, int j, int px, int py, int k, int o, int value, Board* board);

void clear(Board* board);

void draw_piece(Piece* p, Board* board);
void clear_piece(Piece* p, Board* board);
void new_piece(Piece* p, Board* board);

bool current_piece_can_move(int x, int y, Board* board);
bool current_piece_can_rotate(int o, Board* board);

void move_current_piece_down(Board* board);
void move_current_piece_left(Board* board);
void move_current_piece_right(Board* board);

void rotate_current_piece_left(Board* board);
void rotate_current_piece_right(Board* board);

void delete_line(int y, Board* board); // Supprime la ligne se trouvant à la position y
int  delete_possible_lines(Board* board); // Vérifie s'il existe des lignes pleines et les supprime
void drop_current_piece(Board* board); // Hard Drop
bool current_piece_fell(Board* board); // La pièce courante est-elle tombée ?
bool game_over(Board* board); // Le nom de la méthode est assez clair

void take_extra_lines(int count, Board* board);

#endif