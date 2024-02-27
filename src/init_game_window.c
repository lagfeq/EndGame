#include "raylib.h"
#include "header.h"
void InitGameWindow()
{
    const int gameScreenWidth = 1100;
    const int gameScreenHeight = 800;

    InitWindow(gameScreenWidth, gameScreenHeight, "Game Window");

    // Additional game initialization can be done here...

    // Main game loop
    while (!WindowShouldClose())
    {
        // Game logic and rendering go here...

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Additional game rendering goes here...

        EndDrawing();
    }

    // De-Initialization for the game window can be done here...

    CloseWindow();
}