/* board.c */

#include "board.h"
#include <stdio.h>

void init_board(Board* board) {
	for (int line = 0; line < BOARD_HEIGHT; line++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
			board->area[line][column] = FREE;
		}
	}
    board->piece_is_moving = malloc(sizeof(bool));
    board->piece_is_moving = false;
}

/*
* (i, j): Les coordonnées de la case à partir de laquelle floodfiller dans l'aire de jeu
* (px, py): Les coordonnées de la case à partir de laquelle floodfiller dans la matrice de la pièce
* k: pour kind (type), le type de la pièce
* o: pour orientation, l'orientation de la pièce
* value: valeur avec laquelle remplir l'aire de jeu
*/
void flood(int i, int j, int px, int py, int k, int o, int value, bool* visited[SIZE][SIZE], Board* board)
{
    if (px < 0 || px >= SIZE || py < 0 || py >= SIZE || visited[py][px] || PIECES[k][o][py][px] == FREE)
        return;

    visited[py][px] = true;
    board->area[j][i] = value; // On remplit la case de la valeur dans l'aire

    flood(i, j - 1, px, py - 1, k, o, value, visited, board);
    flood(i + 1, j, px + 1, py, k, o, value, visited, board);
    flood(i, j + 1, px, py + 1, k, o, value, visited, board);
    flood(i - 1, j, px - 1, py, k, o, value, visited, board);
}

void flagged_flood(int i, int j, int px, int py, int k, int o, bool* flag, bool* visited[SIZE][SIZE], Board* board)
{
    if (PIECES[k][o][py][px] == FREE || px < 0 || px >= SIZE || py < 0 || py >= SIZE || visited[py][px])
        return;

    visited[py][px] = true;

    /* Si on dépasse les limites de l'aire de jeu
     * ou si la case sur laquelle on est n'est pas vide
     */
    if (i < 0 || i >= BOARD_WIDTH || j < 0 || j >= BOARD_HEIGHT || board->area[j][i] != FREE)
    {
        *flag = false; // on met flag à false
        return;
    }


    flagged_flood(i, j - 1, px, py - 1, k, o, flag, visited, board);
    flagged_flood(i + 1, j, px + 1, py, k, o, flag, visited, board);
    flagged_flood(i, j + 1, px, py + 1, k, o, flag, visited, board);
    flagged_flood(i - 1, j, px - 1, py, k, o, flag, visited, board);
}

/* Cette fonction ne fait qu'appeler le flood */
void flood_fill(int i, int j, int px, int py, int k, int o, int value, Board* board)
{
    bool* visited[SIZE][SIZE];

    for (int l = 0; l < SIZE; l++)
        for (int m = 0; m < SIZE; m++)
            visited[l][m] = false;

    flood(i, j, px, py, k, o, value, visited, board);
   // free(visited);
}

void draw_piece(Piece* p, Board* board)
{
    int i = p->pos_x; // On récupère les ...
    int j = p->pos_y; // ... coordonnées de la pièce

    int k = p->kind; // On récupère son type
    int o = p->orientation; // et sa rotation

    switch (k) // En fonction de son type
    {
    case I:
        p->color = GRAY; // On lui affecte la couleur appropriée
        break;
    case J:
        p->color = BLUE;
        break;
    case L:
        p->color = ORANGE;
        break;
    case O:
        p->color = YELLOW;
        break;
    case S:
        p->color = GREEN;
        break;
    case T:
        p->color = PURPLE;
        break;
    case Z:
        p->color = RED;
        break;
    default:
        break;
    }

    /* On fait le flood fill à partir du point de pivot de la pièce
     * et on remplit l'aire de jeu en fonction de la couleur de la pièce
     */
    flood_fill(i, j, PIVOT_X, PIVOT_Y, k, o, p->color, board);
}

void clear_piece(Piece* p, Board* board)
{
    int i = p->pos_x;
    int j = p->pos_y;

    int k = p->kind;
    int o = p->orientation;

    flood_fill(i, j, PIVOT_X, PIVOT_Y, k, o, FREE, board);
}

void new_piece(Piece* p, Board* board)
{
    board->piece_is_moving = true;
    p->pos_x = ORIGIN_X; // On donne à la pièce les coordonnées ...
    p->pos_y = ORIGIN_Y; // de l'origine
    board->current_piece = p; // On déclare cette pièce comme pièce courante de l'aire de jeu
    if(current_piece_can_move(ORIGIN_X,ORIGIN_Y,board)) draw_piece(p, board); // On la dessine
    board->piece_is_moving = false;
}

void clear(Board* board)
{
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
            board->area[i][j] = FREE;
    }
}

/* Peut on déplacer la pièce courante de sa position vers la position (x, y) ? */
bool current_piece_can_move(int x, int y, Board* board)
{
    bool movable = true; // On suppose au départ qu'on peut bouger la pièce

   /* On déclare et initialise le tableau visited pour le flood fill */
    bool* visited[SIZE][SIZE];

    for (int l = 0; l < SIZE; ++l)
        for (int m = 0; m < SIZE; ++m)
            visited[l][m] = false;

    int k = board->current_piece->kind; // On récupère le type ...
    int o = board->current_piece->orientation; // ... et l'orientation de la pièce

   /* On fait notre flood fill */
    flagged_flood(x, y, PIVOT_X, PIVOT_Y, k, o, &movable, visited, board);

    //draw_piece(board->current_piece, board); // On redessine notre pièce

    //free(&visited);
    return movable; // On renvoie le résultat
}

/* Peut on affecter l'orientation o à la pièce courante ? */
bool current_piece_can_rotate(int o, Board* board)
{
    //clear_piece(board->current_piece, board);

    bool rotable = true;

    bool* visited[SIZE][SIZE];

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            visited[i][j] = false;

    int k = board->current_piece->kind;

    flagged_flood(board->current_piece->pos_x, board->current_piece->pos_y, PIVOT_Y, PIVOT_X, k, o, &rotable, visited, board);

   // draw_piece(board->current_piece, board);

    return rotable;
}

/* Déplace la pièce d'une case vers le bas */
void move_current_piece_down(Board* board)
{
    if (board->current_piece == NULL || board->piece_is_moving) return;
    board->piece_is_moving = true;
    int x = board->current_piece->pos_x;
    int y = board->current_piece->pos_y;
    clear_piece(board->current_piece, board);
    if (current_piece_can_move(x, y+1, board)) // Si on peut bouger la pièce vers le bas
    {
        board->current_piece->pos_y++; // On incrémente son ordonnée  
    }
    draw_piece(board->current_piece, board); // On la redessine à la nouvelle position
    board->piece_is_moving = false;
}

/* Déplace la pièce d'une case vers la gauche */
void move_current_piece_left(Board* board)
{
    if (board->current_piece == NULL || board->piece_is_moving) return;
    board->piece_is_moving = true;
    int x = board->current_piece->pos_x;
    int y = board->current_piece->pos_y;
    clear_piece(board->current_piece, board);
    if (current_piece_can_move(x-1, y, board))
    {
        board->current_piece->pos_x--;
    }
    draw_piece(board->current_piece, board);
    board->piece_is_moving = false;
}

/* Déplace la pièce d'une case vers la droite */
void move_current_piece_right(Board* board)
{
    if (board->current_piece == NULL || board->piece_is_moving) return;
    board->piece_is_moving = true;
    int x = board->current_piece->pos_x;
    int y = board->current_piece->pos_y;
    clear_piece(board->current_piece, board);
    if (current_piece_can_move(x+1, y, board))
    {
        board->current_piece->pos_x++;
    }
    draw_piece(board->current_piece, board);
    board->piece_is_moving = false;
}

/* Tourne la pièce vers la gauche */
void rotate_current_piece_left(Board* board)
{
    if (board->current_piece == NULL || board->piece_is_moving) return;
    board->piece_is_moving = true;
    int o = board->current_piece->orientation; // On récupère l'orientation courante
    int new_o;
    if (o > 0) // Si on n'est pas sur la 1ère orientation
        new_o = o-1; // On peut décrémenter o
    else // Si non
        new_o =  NB_ROTATIONS - 1; // On passe à la dernière orientation

    clear_piece(board->current_piece, board); // On efface la pièce courante
    if (current_piece_can_rotate(o, board)) // Si on peut tourner la pièce
    {
        board->current_piece->orientation = new_o;
       // draw_piece(board->current_piece, board);
       // clear_piece(board->current_piece, board);
        if (!current_piece_can_move(board->current_piece->pos_x, board->current_piece->pos_y, board)) board->current_piece->orientation = o; //cas de figure où la rotation a produit une incohérence: retour en arrière
    }
    draw_piece(board->current_piece, board);
    board->piece_is_moving = false;
}

/* Tourne la pièce vers la droite */
void rotate_current_piece_right(Board* board)
{
    int o = board->current_piece->orientation;
    int new_o;
    if (o < NB_ROTATIONS - 1) // Si on n'est pas sur la dernière orientation
        new_o = o+1; // On peut incrémenter o
    else // Si non
        new_o = 0; // On passe à la 1ère orientation
    clear_piece(board->current_piece, board);
    if (current_piece_can_rotate(o,board))
    {
        board->current_piece->orientation = new_o;
        if (!current_piece_can_move(board->current_piece->pos_x, board->current_piece->pos_y, board)) board->current_piece->orientation = o; //cas de figure où la rotation a produit une incohérence: retour en arrière
    }
    draw_piece(board->current_piece, board);
}

void delete_line(int y, Board* board)
{
    clear_piece(board->current_piece, board); // On efface d'abord la pièce courante

        /* On déplace toutes les lignes à partir de y vers le haut
         * d'une case vers le bas
         */
    for (int j = y; j > 0; j--)
    {
        for (int i = 0; i < BOARD_WIDTH; i++)
            board->area[j][i] = board->area[j-1][i];
    }

    draw_piece(board->current_piece, board); // On la redessine
}

/* Renvoie le nombre de lignes supprimées */
int delete_possible_lines(Board* board)
{
    int deleted_lines = 0;

    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
        int i = 0;

        for (; i < BOARD_WIDTH && board->area[j][i] != FREE; ++i);

        if (i == BOARD_WIDTH) // On a trouvé une ligne pleine
        {
            deleted_lines++; // On incrémente le nombre de lignes supprimées
            delete_line(j,board); // On supprime la ligne
        }
    }

    return deleted_lines;
}

/* HARD-DROP */
void drop_current_piece(Board* board)
{
    int x = board->current_piece->pos_x;
    int y = board->current_piece->pos_y;

    
    while (!current_piece_fell(board)){ // Tant qu'on peut toujours bouger la pièce vers le bas
        clear_piece(board->current_piece, board);
        move_current_piece_down(board); // on le fait
        draw_piece(board->current_piece, board);
    }
}

/* Teste si la pièce courante est tombée donc ne peut plus bouger */
bool current_piece_fell(Board* board)
{
    int x = board->current_piece->pos_x;
    int y = board->current_piece->pos_y;

    clear_piece(board->current_piece, board);
    if (current_piece_can_move(x, y+1, board)) // Si on peut encore la bouger vers le bas
        return false; // on renvoie faux
    
    draw_piece(board->current_piece, board);
    return true; // si non on renvoie vrai
}

bool game_over(Board* board)
{
    clear_piece(board->current_piece, board); // On efface d'abord la pièce courante
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        if (board->area[0][i] != FREE) // Si il y a un bloc sur la première ligne de l'aire
            return true; // C'est que la partie est finie
    }
    draw_piece(board->current_piece, board); // On la redessine
    return false;
}

void take_extra_lines(int count, Board* board)
{
    clear_piece(board->current_piece, board); // On efface d'abord la pièce courante

        /* On déplace toutes les lignes 
         * d'une case vers le haut
         */
    for (int j = 0; j < BOARD_HEIGHT - count; j++)
    {
        for (int i = 0; i < BOARD_WIDTH; i++)
            board->area[j][i] = board->area[j + count][i];
    }

    srand(time(NULL));
    for (int j = BOARD_HEIGHT - count; j < BOARD_HEIGHT; j++) {
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (rand() % 2 == 1)
                board->area[BOARD_HEIGHT - 1][i] = GRAY;
            else board->area[j][i] = FREE;
        }
    }

    draw_piece(board->current_piece, board); // On la redessine
}
