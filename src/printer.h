/* printer.h */
#ifndef PRINTER_H
#define PRINTER_H
#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>

void init_printer();
void displayText(char* text, const int xOffset, const int yOffset,SDL_Renderer* win_rend);
void displayInt(int value, const int xOffset, const int yOffset, SDL_Renderer* win_rend, bool firstUse);

#endif