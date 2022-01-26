/* window_manager.h */
#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include "printer.h"
#include <SDL.h>

SDL_Texture* grid;

SDL_Texture* YELLOW_TEXTURE;
SDL_Texture* BLUE_TEXTURE;
SDL_Texture* ORANGE_TEXTURE;
SDL_Texture* GREEN_TEXTURE;
SDL_Texture* PURPLE_TEXTURE;
SDL_Texture* RED_TEXTURE;
SDL_Texture* GRAY_TEXTURE;

SDL_Texture* YELLOW_TEXTURE;
SDL_Texture* BLUE_TEXTURE;
SDL_Texture* ORANGE_TEXTURE;
SDL_Texture* GREEN_TEXTURE;
SDL_Texture* PURPLE_TEXTURE;
SDL_Texture* RED_TEXTURE;
SDL_Texture* GRAY_TEXTURE;


SDL_Texture* load_texture(char* filename);
void prompt_menu(); 
void prompt_tetric_grid_2P();
void print_case(int i, int j, SDL_Texture* texture, int player);
void print_score_in_game(int score, int player);
void print_level_in_game(int level, int player);
void print_next_piece_case(int i, int j, SDL_Texture* texture, int player);
void init_window();
void exit_window();


#endif