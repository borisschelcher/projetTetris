/* game_manager.h */
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "board.h"
#include "player.h"
#include "printer.h"
#include "window_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_thread.h>

Board* board_P1;
Board* board_P2;
Piece* next_piece_P1;
Piece* next_piece_P2;



Player* player_P1;
Player* player_P2;
bool quit;
bool piece_going_down;



void init_game();
void game_turn();
void keyboard(const Uint8* keys);
int game_loop(void* data);
void game_exit();
Piece* random_piece();
void generate_new_pieces();
void refresh_grid();
void refresh_next_pieces();
SDL_Texture* colored_texture(int color);

#endif