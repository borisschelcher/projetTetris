/* player.c */
#include "player.h"

void init_player(Player* Player) {
	Player->score_player = 0;
	Player->level_player = 0;
	Player->line_clear = 0;
}

void score_add(Player* Player, int line_clear_in_game) {
	next_level(Player);
	switch (line_clear_in_game)
	{
	case 1: Player->score_player += (Player->level_player + 1) * 40 ; break;
	case 2: Player->score_player += (Player->level_player + 1) * 100; break;
	case 3: Player->score_player += (Player->level_player + 1) * 300; break;
	case 4: Player->score_player += (Player->level_player + 1) * 1200; break;
	}
	Player->level_player += line_clear_in_game;
}

void next_level(Player* Player) {
	if (((Player->level_player*10) +10)< Player->line_clear)
		Player->level_player = (Player->line_clear-10)/10;
}

int print_level(Player* Player) {
	return Player->level_player;
}

int print_score(Player* Player) {
	return Player->score_player;
}