#include "window_manager.h"

SDL_Window* pWindow = NULL;
SDL_Renderer* pRenderer = NULL;
SDL_Surface* win_surf = NULL;

SDL_Rect master_grid;
SDL_Rect grid_rect_P1;
SDL_Rect grid_rect_P2;
SDL_Rect grid_score_P1;
SDL_Rect grid_score_P2;
SDL_Rect grid_level_P1;
SDL_Rect grid_level_P2;
SDL_Rect next_piece_P1_rect;
SDL_Rect next_piece_P2_rect;

const int WIDTH = 1600;
const int HEIGHT = 1000;
const int POSX_WIN = 450;
const int POSY_WIN = 10;

//Player 1
//Score
const int X_POSITION_SCORE_PLAYER_ONE = 670;
const int Y_POSITION_SCORE_PLAYER_ONE = 360;
//Level
const int X_POSITION_LEVEL_PLAYER_ONE = 625;
const int Y_POSITION_LEVEL_PLAYER_ONE = 500;

//Player 2
//Score
const int X_POSITION_SCORE_PLAYER_TWO = 850;
const int Y_POSITION_SCORE_PLAYER_TWO = 360;
//Level
const int X_POSITION_LEVEL_PLAYER_TWO = 850;
const int Y_POSITION_LEVEL_PLAYER_TWO = 500;

SDL_Texture* load_texture(char* filename) {
	SDL_Texture* texture = 0;
	SDL_Surface* loadedImage = 0;
	loadedImage = SDL_LoadBMP(filename);
	if (!loadedImage)
	{
		fprintf(stderr, "Erreur chargement image : %s\n", SDL_GetError());
		return 0;
	}

	texture = SDL_CreateTextureFromSurface(pRenderer, loadedImage);
	SDL_FreeSurface(loadedImage);
	if (texture == 0)
	{
		fprintf(stderr, "Erreur creation texture : %s\n", SDL_GetError());
		return 0;
	}
	return texture;
}



void prompt_menu() {
	SDL_Texture* menu = load_texture("./MenuV1.bmp");
	SDL_Rect dst;

	if (!menu) return;

	// R�cup�ration de la taille de la texture 
	SDL_QueryTexture(menu, NULL, NULL, &dst.w, &dst.h);

	// Centrage
	dst.x = (WIDTH - dst.w) / 2;
	dst.y = (HEIGHT - dst.h) / 2;

	SDL_RenderClear(pRenderer);
	SDL_RenderCopy(pRenderer, menu, NULL, &dst);
	SDL_RenderPresent(pRenderer);
	//SDL_UpdateWindowSurface(pWindow); // Mise � jour de la fen�tre pour prendre en compte la copie du sprite
	SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fen�tre */
}

void prompt_tetric_grid_2P() {
	SDL_RenderClear(pRenderer);
	SDL_RenderCopy(pRenderer, grid, NULL, &master_grid);
	SDL_RenderPresent(pRenderer);
}

void print_case(int i, int j, SDL_Texture* texture, int player) {
	SDL_Rect colored_case;
	colored_case.w = 40;
	colored_case.h = 40;
	if (player == 1) {
		colored_case.x = 40 * i + grid_rect_P1.x;
		colored_case.y = 40 * j + grid_rect_P1.y;
	}
	else {
		colored_case.x = 40 * i + grid_rect_P2.x;
		colored_case.y = 40 * j + grid_rect_P2.y;
	}

	SDL_RenderCopy(pRenderer, texture, NULL, &colored_case);
	SDL_RenderPresent(pRenderer);
}

void print_next_piece_case(int i, int j, SDL_Texture* texture, int player) {
	SDL_Rect colored_case;
	colored_case.w = 40;
	colored_case.h = 40;
	if (player == 1) {
		colored_case.x = 40 * i + next_piece_P1_rect.x;
		colored_case.y = 40 * j + next_piece_P1_rect.y;
	}
	else {
		colored_case.x = 40 * i + next_piece_P2_rect.x;
		colored_case.y = 40 * j + next_piece_P2_rect.y;
	}

	SDL_RenderCopy(pRenderer, texture, NULL, &colored_case);
	SDL_RenderPresent(pRenderer);
}

void init_window()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return;
	}
	grid_score_P1.x = master_grid.x + X_POSITION_SCORE_PLAYER_ONE;
	grid_score_P1.y = master_grid.y + Y_POSITION_SCORE_PLAYER_ONE;
	grid_score_P1.h = 100;
	grid_score_P1.w = 100;

	grid_score_P2.x = master_grid.x + X_POSITION_SCORE_PLAYER_TWO;
	grid_score_P2.y = master_grid.y + Y_POSITION_SCORE_PLAYER_TWO;
	grid_score_P2.h = 100;
	grid_score_P2.w = 100;

	grid_level_P1.x = master_grid.x + X_POSITION_LEVEL_PLAYER_ONE;
	grid_level_P1.y = master_grid.y + Y_POSITION_LEVEL_PLAYER_ONE;
	grid_level_P1.h = 100;
	grid_level_P1.w = 100;
	
	grid_level_P2.x = master_grid.x + X_POSITION_LEVEL_PLAYER_TWO;
	grid_level_P2.y = master_grid.y + Y_POSITION_LEVEL_PLAYER_TWO;
	grid_level_P2.h = 100;
	grid_level_P2.w = 100;

	pWindow = SDL_CreateWindow("Tetric", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

	win_surf = SDL_GetWindowSurface(pWindow);

	if (!pWindow || !pRenderer)
	{
		fprintf(stderr, "Erreur � la cr�ation des fen�tres\n");
		SDL_Quit();
		return;
	}

	grid = load_texture("grille2P.bmp", pRenderer);
	if (!grid) return;

	// Récupération de la taille de la texture 
	SDL_QueryTexture(grid, NULL, NULL, &master_grid.w, &master_grid.h);

	// Centrage
	master_grid.x = (WIDTH - master_grid.w) / 2;
	master_grid.y = (HEIGHT - master_grid.h) / 2;

	grid_rect_P1.x = master_grid.x + 96;
	grid_rect_P1.y = master_grid.y + 113;
	grid_rect_P1.h = 800;
	grid_rect_P1.w = 400;

	grid_rect_P2.x = master_grid.x + 911;
	grid_rect_P2.y = master_grid.y + 113;
	grid_rect_P2.h = 800;
	grid_rect_P2.w = 400;

	next_piece_P1_rect.x = master_grid.x + 503;
	next_piece_P1_rect.y = master_grid.y + 130;
	next_piece_P1_rect.h = 245;
	next_piece_P1_rect.w = 176;

	next_piece_P2_rect.x = master_grid.x + 728;
	next_piece_P2_rect.y = master_grid.y + 130;
	next_piece_P2_rect.h = 245;
	next_piece_P2_rect.w = 176;

	YELLOW_TEXTURE = load_texture("spriteCarreJaune.bmp");
	BLUE_TEXTURE = load_texture("spriteCarreBleu.bmp");
	ORANGE_TEXTURE = load_texture("spriteCarreOrange.bmp");
	GREEN_TEXTURE = load_texture("spriteCarreVert.bmp");
	PURPLE_TEXTURE = load_texture("spriteCarreViolet.bmp");
	RED_TEXTURE = load_texture("spriteCarreRouge.bmp");
	GRAY_TEXTURE = load_texture("spriteCarreGris.bmp");
	init_printer();
}

void exit_window() {
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

void print_score_in_game(int score, int player) {
	int x, y;
	if (player == 1) {
		x = grid_score_P1.x; //+ grid_score_P1.w / 2;
		y = grid_score_P1.y + grid_score_P1.h / 2;
		displayInt(score, x, y, pRenderer, true);
	}
	else if(player == 2) {
		x = grid_score_P2.x + grid_score_P2.w / 2;
		y = grid_score_P2.y + grid_score_P2.h / 2;
		displayInt(score, x, y, pRenderer, true);
	}
	//SDL_RenderPresent(pRenderer);
}
void print_level_in_game(int level, int player) {
	if (player == 1) {
		displayInt(level, grid_level_P1.x + grid_level_P1.w/2, grid_level_P1.y + grid_level_P1.h/2, pRenderer,true);
	}
	else if (player == 2) {
		displayInt(level, grid_level_P2.x + grid_level_P2.w / 2, grid_level_P2.y + grid_level_P2.h / 2, pRenderer,true);
	}
}