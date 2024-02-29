#include "raylib.h"
#include "header.h"
#include "raymath.h"
typedef void (*MenuCallback)();
void DrawMenuButton(int screenWidth, int *currentMapIndex)
{
    // Draw a menu button
    Rectangle menuButton = {screenWidth - 150, 50, 100, 40};
    DrawRectangleRounded(menuButton, 0.2, 0, WHITE);
    DrawText("Menu", menuButton.x + menuButton.width / 2 - MeasureText("Menu", 20) / 2,
             menuButton.y + menuButton.height / 2 - 10, 20, BLACK);

    // Check for button click
    if (CheckCollisionPointRec(GetMousePosition(), menuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Go back to the main menu
        *currentMapIndex = -1;
    }
}
