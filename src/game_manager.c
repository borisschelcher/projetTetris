#include "game_manager.h"

#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf; if( !setjmp(ex_buf) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf, 1)

#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf; if( !setjmp(ex_buf) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf, 1)


void init_game() {
	//Player and Board One
	board_P1 = malloc(sizeof(Board));
	init_board(board_P1);

	player_P1 = malloc(sizeof(Player));
	init_player(player_P1);

	//Player and Board Two
	board_P2 = malloc(sizeof(Board));
	init_board(board_P2);

	next_piece_P1 = random_piece();
	next_piece_P2 = random_piece();
	new_piece(next_piece_P1, board_P1);
	new_piece(next_piece_P2, board_P2);
	next_piece_P1 = random_piece();
	next_piece_P2 = random_piece();
	player_P2 = malloc(sizeof(Player));
	init_player(player_P2);

	generate_new_pieces();
	refresh_next_pieces();
	
	SDL_Thread* thread = SDL_CreateThread(game_loop, "game_loop", (void*)NULL);

	//Tant que l'utilisateur n'a pas quitté
	while (quit == false) {
		//SDL_PumpEvents();
		SDL_Event event;
		const Uint8* state = SDL_GetKeyboardState(NULL);
		//Tant qu'il y a un événement
		while (SDL_PollEvent(&event) && piece_going_down == false)
		{

			if(piece_going_down == false) keyboard(state);
			quit |= state[SDL_SCANCODE_ESCAPE];

			//Si l'utilisateur a cliqu� sur le X de la fen�tre
			if (event.type == SDL_QUIT)
			{
				//On quitte the programme
				quit = true;
			}
		}
	}
}

void game_turn() {
	TRY{
		piece_going_down = true;
		//refresh_grid();
		generate_new_pieces();
	move_current_piece_down(board_P1);
	move_current_piece_down(board_P2);

	int deleted_lines_P1 = delete_possible_lines(board_P1);
	int deleted_lines_P2 = delete_possible_lines(board_P2);
	if (deleted_lines_P1 > 0) {
		take_extra_lines(deleted_lines_P1, board_P2);
		score_add(player_P1, deleted_lines_P1);
		refresh_grid();
	}
	if (deleted_lines_P2 > 0) {
		take_extra_lines(deleted_lines_P2, board_P1);
		score_add(player_P2, deleted_lines_P2);
		refresh_grid();
	}
	if (!game_over(board_P1) && !game_over(board_P2)) refresh_grid();

		
		move_current_piece_down(board_P1);
		move_current_piece_down(board_P2);
		if (!game_over(board_P1) && !game_over(board_P2)) refresh_grid();
		piece_going_down = false;
	}
		CATCH{
		printf("exception");
	}
	ETRY;
}

int game_loop(void* data) {
	while (!quit && !game_over(board_P1) && !game_over(board_P2))
	{
		game_turn();
		SDL_Delay(500);
	}
	return 0;
}

// fonction callbakc clavier 
// keys = tableau de bool  : touches enfonc�es ?
void keyboard(const Uint8* keys)
{
	if (board_P1->current_piece != NULL && !board_P1->piece_is_moving && piece_going_down == false) {
		if (keys[SDL_SCANCODE_LEFT] && board_P2->current_piece != NULL && !board_P2->piece_is_moving) {
			move_current_piece_left(board_P1);
		}
		else if (keys[SDL_SCANCODE_RIGHT] && board_P2->current_piece != NULL && !board_P2->piece_is_moving) {
			move_current_piece_right(board_P1);
		}
		else if (keys[SDL_SCANCODE_DOWN] && board_P2->current_piece != NULL && !board_P2->piece_is_moving) {
			drop_current_piece(board_P1);
		}
		else if (keys[SDL_SCANCODE_UP] && board_P2->current_piece != NULL && !board_P2->piece_is_moving) {
			rotate_current_piece_left(board_P1);
		}
	}

	if (board_P2->current_piece != NULL && !board_P2->piece_is_moving && piece_going_down == false) {
		if (keys[SDL_SCANCODE_A] && board_P2->current_piece != NULL && !board_P2->piece_is_moving) {
			move_current_piece_left(board_P2);
		}
		else if (keys[SDL_SCANCODE_D] && board_P2->current_piece != NULL && !board_P2->piece_is_moving) {
			move_current_piece_right(board_P2);
		}
		else if (keys[SDL_SCANCODE_S] && board_P2->current_piece != NULL && !board_P2->piece_is_moving) {
			drop_current_piece(board_P2);
		}
		else if (keys[SDL_SCANCODE_W] && board_P2->current_piece != NULL && !board_P2->piece_is_moving) {
			rotate_current_piece_left(board_P2);
		}
	}
	if (piece_going_down == false) refresh_grid();
}

void game_exit() {
	free(board_P1);
	free(board_P2);
	SDL_DestroyTexture(YELLOW_TEXTURE);
	SDL_DestroyTexture(BLUE_TEXTURE);
	SDL_DestroyTexture(ORANGE_TEXTURE);
	SDL_DestroyTexture(GREEN_TEXTURE);
	SDL_DestroyTexture(PURPLE_TEXTURE);
	SDL_DestroyTexture(RED_TEXTURE);
	SDL_DestroyTexture(GRAY_TEXTURE);
	free(player_P1);
	free(player_P2);
}

Piece* random_piece() {
	Piece* piece = malloc(sizeof(Piece));
	srand(time(NULL));
	piece->orientation = 0;
	int randInt = rand() % 7;
	enum kinds rand_kind = kinds + randInt;
	piece->kind = rand_kind;
}

void generate_new_pieces() {
	if (current_piece_fell(board_P1)) {
		new_piece(next_piece_P1, board_P1);
		next_piece_P1 = random_piece();
		refresh_next_pieces();
	}
	if (current_piece_fell(board_P2)) {
		new_piece(next_piece_P2, board_P2);
		next_piece_P2 = random_piece();
		refresh_next_pieces();
	}
	if (!game_over(board_P1) && !game_over(board_P2)) refresh_grid();
}


void refresh_grid() {
	prompt_tetric_grid_2P();
	refresh_next_pieces();
	//Player One
	print_score_in_game(print_score(player_P1), 1);
	print_level_in_game(print_level(player_P1), 1);

	//Player Two
	print_score_in_game(print_score(player_P2), 2);
	print_level_in_game(print_level(player_P2), 2);

	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++) {
			if (board_P1->area[y][x] != FREE) {
				print_case(x, y, colored_texture(board_P1->area[y][x]), 1);
			}
			if (board_P2->area[y][x] != FREE) {
				print_case(x, y, colored_texture(board_P2->area[y][x]), 2);
			}
		}
	}
}

void refresh_next_pieces() {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			int case_P1 = PIECES[next_piece_P1->kind][next_piece_P1->orientation][y][x];
			int case_P2 = PIECES[next_piece_P2->kind][next_piece_P1->orientation][y][x];
			if (case_P1 != FREE) {
				print_next_piece_case(x, y, colored_texture(GRAY),1);
			}
			if (case_P2 != FREE) {
				print_next_piece_case(x, y, colored_texture(GRAY), 2);
			}
		}
	}
}

SDL_Texture* colored_texture(int color) {
	switch (color) {
	case YELLOW:
		return YELLOW_TEXTURE;
		break;
	case BLUE:
		return BLUE_TEXTURE;
		break;
	case ORANGE:
		return ORANGE_TEXTURE;
		break;
	case GREEN:
		return GREEN_TEXTURE;
		break;
	case PURPLE:
		return PURPLE_TEXTURE;
		break;
	case RED:
		return RED_TEXTURE;
		break;
	case GRAY:
		return GRAY_TEXTURE;
		break;
	default:
		return NULL;
		break;
	}
}