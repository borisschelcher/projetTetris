/* player.h */
#ifndef PLAYER_H
#define PLAYER_H
#include "piece.h"
#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>



typedef struct Player Player;
struct Player {
    int score_player; //Score player
    int level_player; //Level Player
    int line_clear; //line clear by player
};

void init_player(Player* Player);
void score_add(Player* Player,int line_clear_in_game);
void next_level(Player* Player);

//print
int print_level(Player* Player);
int print_score(Player* Player);

#endif