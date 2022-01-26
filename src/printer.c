/* printer.c */
#include "printer.h"



SDL_Surface* spritesASCII = NULL;

const int DEFAULT_SIZE = 32;
const int CHAR_WIDTH = 18;

void init_printer()
{
    //....
    spritesASCII = SDL_LoadBMP("Tetris_ascii.bmp");

    SDL_SetColorKey(spritesASCII, true, 0);  // 0: 00/00/00 noir -> transparent
//....
}

void displayText(char* text, const int xOffset, const int yOffset, SDL_Renderer* win_rend) {

    for (int i = 0; i < strlen(text); i++)
    {
        SDL_Rect dest = {0,0,0,0};

        dest.x = (text[i] - ' ') % 16;
        dest.y = (text[i] - ' ') / 16;
        dest.w = 32;
        dest.h = 32;

        SDL_Rect srcLetter = { dest.x * DEFAULT_SIZE, dest.y * DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE };

        dest.x = xOffset + i * CHAR_WIDTH;
        dest.y = yOffset;

        SDL_RenderCopy(win_rend, SDL_CreateTextureFromSurface(win_rend,spritesASCII), &srcLetter, &dest);
        SDL_RenderPresent(win_rend);
    }

}

void displayInt(int value, const int xOffset, const int yOffset, SDL_Renderer* win_rend, bool firstUse) {
    if (!firstUse && value == 0)
    {
        return;
    }

    if (value > 0)
    {
        displayInt(value / 10, xOffset, yOffset, win_rend, false);
    }

    char valueToDisplay = (value % 10) + '0';
    int xPosition = 0;

    if (value) {
        xPosition = (int)floor(log10(abs(value)));
    }

    displayText(&valueToDisplay, xOffset + xPosition * CHAR_WIDTH, yOffset, win_rend);
}