#include "raylib.h"
#include "header.h"
#include "raymath.h"
void DrawExitButton(Rectangle exitButton, bool exitButtonClicked) {
    DrawRectangleRounded(exitButton, 0.2, 0, (exitButtonClicked) ? BLACK : WHITE);
    DrawText("Exit", exitButton.x + exitButton.width / 2 - MeasureText("Exit", 20) / 2,
             exitButton.y + exitButton.height / 2 - 10, 20, BLACK);
}