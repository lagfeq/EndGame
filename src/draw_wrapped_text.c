#include "raylib.h"
#include "header.h"
void DrawWrappedText(const char* text, int x, int y, int fontSize, int maxWidth, Color color)
{
    char** textLines = TextWrap(text, GetFontDefault(), fontSize, maxWidth);

    for (int i = 0; textLines[i] != NULL; i++)
    {
        DrawText(textLines[i], x, y + i * fontSize, fontSize, color);
        free(textLines[i]);
    }

    free(textLines);
}