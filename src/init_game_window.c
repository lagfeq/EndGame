#include "header.h"
#include "raylib.h"
#include "raymath.h"

void InitGameWindow()
{
    const int gameScreenWidth = 1100;
    const int gameScreenHeight = 800;

    InitWindow(gameScreenWidth, gameScreenHeight, "Game Window");
    const char *filename = "sources/menuWindow/right.jpg";
    Texture2D fighter = LoadTexture(filename);

    unsigned numFrames = 3;
    int frameWidth = fighter.width / numFrames;
    Rectangle frameRec = {0.0f, 0.0f, (float)frameWidth, (float)fighter.height};
    Vector2 fighterPosition = {gameScreenWidth / 2.0f, gameScreenHeight / 2.0f};
    Vector2 fighterVelocity = {0.0f, 0.0f}; 

    float fighterSpeed = 5.0f; 
    float scarfySpeed = 3.0f; 

    unsigned frameDelay = 5;
    unsigned frameDelayCounter = 0;
    unsigned frameIndex = 0;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if (IsKeyDown(KEY_D))
        {
            fighterVelocity.x = fighterSpeed; // Declare and initialize fighterSpeed
            if (frameRec.width < 0)
            {
                frameRec.width = -frameRec.width;
            }
        }
        else if (IsKeyDown(KEY_A))
        {
            fighterVelocity.x = -scarfySpeed; // Declare and initialize scarfySpeed
            if (frameRec.width > 0)
            {
                frameRec.width = -frameRec.width;
            }
        }
        else
        {
            fighterVelocity.x = 0;
        }

        bool fighterMoving = fighterVelocity.x != 0.0f || fighterVelocity.y != 0.0f;
        //----------------------------------------------------------------------------------
        fighterPosition = Vector2Add(fighterPosition, fighterVelocity);

        ++frameDelayCounter;
        if (frameDelayCounter > frameDelay)
        {
            frameDelayCounter = 0;

            if (fighterMoving) // Fix typo: 'fighteryMoving' to 'fighterMoving'
            {
                ++frameIndex;
                frameIndex %= numFrames;
                frameRec.x = (float)frameWidth * frameIndex;
            }
        }
        //----------------------------------------------------------------------------------
        // Additional game logic/rendering can be added here
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(fighter, frameRec, fighterPosition, WHITE);
        EndDrawing();
    }

    // De-Initialization for the game window can be done here...
    CloseWindow();
}