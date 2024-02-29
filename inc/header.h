#ifndef GAME_H
#define GAME_H

#define MAX_LINES 100
#define MAX_LINE_LENGTH 1024

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void InitGameWindow();
void DrawCloseButton(Rectangle closeButtonRect, bool closeButtonClicked);
char** TextWrap(const char* text, Font font, int fontSize, int maxWidth);
void DrawWrappedText(const char* text, int x, int y, int fontSize, int maxWidth, Color color);

#endif 

