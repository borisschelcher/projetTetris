#include "game_manager.h"

void init() {
	init_window();
	init_game();
}

int main(int argc, char** argv)
{
	init();
	game_exit();
	exit_window();
	return 0;
}