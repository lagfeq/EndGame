#include "raylib.h"
#include "header.h"
#include "raymath.h"

typedef struct {
    Vector2 position;
    Rectangle bounds;
    float speed;
    Color color;
} Character;

typedef struct {
    Vector2 position;
    Texture2D texture;
    bool active;
} Object;

typedef struct {
    Texture2D background;
    Object chest;
    Object object1;
    Object object2;
    Object object3;
    Object additionalObject;
} GameMap;

void InitGameWindow() {
    const int screenWidth = 1100;
    const int screenHeight = 800;

    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "Game");

    Texture2D chestTexture = LoadTexture("sources/closedChest.png");
    Texture2D fortressTexture = LoadTexture("sources/fortress.png");

    Texture2D objectTexture1 = LoadTexture("sources/bush.png");
    Texture2D objectTexture2 = LoadTexture("sources/tree2.png");
    Texture2D objectTexture3 = LoadTexture("sources/main_tree.png");
    Texture2D additionalObjectTexture = LoadTexture("sources/main_tree.png");

    float scale = 5.0f;
    objectTexture1.width *= scale;
    objectTexture1.height *= scale;
    objectTexture2.width *= scale;
    objectTexture2.height *= scale;
    objectTexture3.width *= scale;
    objectTexture3.height *= scale;
    additionalObjectTexture.width *= scale;
    additionalObjectTexture.height *= scale;

    // Define chests
    Object chests[4] = {
        {{100, 100}, chestTexture, true},
        {{screenWidth - 200, 100}, chestTexture, true},
        {{100, screenHeight - 200}, chestTexture, true},
        {{screenWidth - 200, screenHeight - 200}, chestTexture, true}};
    for (int i = 0; i < 4; i++) {

        chests[i].texture.width /= 3;
        chests[i].texture.height /= 3;
        chests[i].position.x += chests[i].texture.width;
        chests[i].position.y += chests[i].texture.height;
    }
    Object fortress = {{700, 20}, fortressTexture, true};
    fortress.texture.width *= 2.0f;
    fortress.texture.height *= 2.0f;
    fortress.position.x -= fortress.texture.width / 4;
    fortress.position.y -= fortress.texture.height / 4;

    // Load maps
    GameMap maps[4];
    maps[0].background = LoadTexture("sources/map1.png");
    maps[0].chest = chests[0];

    maps[1].background = LoadTexture("sources/map2.png");
    maps[1].chest = chests[1];

    maps[2].background = LoadTexture("sources/map3.png");
    maps[2].chest = chests[2];
    maps[2].chest.position.x = screenWidth - 300;
    maps[2].chest.position.y = 50;

    maps[3].background = LoadTexture("sources/map4.png");
    maps[3].chest = fortress;

    maps[0].chest.position.y += 20;
    maps[1].chest.position.x = screenWidth / 2 - maps[1].chest.texture.width / 2;

    // Define positions and sizes for additional objects in map 1
    maps[0].object1.position = (Vector2){600, 370};
    maps[0].object1.texture = objectTexture1;
    maps[0].object1.active = true;

    maps[0].object2.position = (Vector2){300, 900};
    maps[0].object2.texture = objectTexture2;
    maps[0].object2.active = true;

    maps[0].object3.position = (Vector2){1000, 850};
    maps[0].object3.texture = objectTexture3;
    maps[0].object3.active = true;

    maps[1].additionalObject.position = (Vector2){800, 400};
    maps[1].additionalObject.texture = additionalObjectTexture;
    maps[1].additionalObject.active = true;

    for (int i = 0; i < 3; i++) {
        // Adjust position to center
        maps[0].object1.position.x -= maps[0].object1.texture.width / 2;
        maps[0].object1.position.y -= maps[0].object1.texture.height / 2;
        maps[0].object2.position.x -= maps[0].object2.texture.width / 2;
        maps[0].object2.position.y -= maps[0].object2.texture.height / 2;
        maps[0].object3.position.x -= maps[0].object3.texture.width / 2;
        maps[0].object3.position.y -= maps[0].object3.texture.height / 2;
    }

    // Initialize character
    Character player;
    player.position = (Vector2){screenWidth / 2, screenHeight / 2};
    player.speed = 5.0f;
    player.color = GREEN;

    SetTargetFPS(60);

    int currentMapIndex = 0;

    // Main game loop
    while (!WindowShouldClose()) {
        player.bounds = (Rectangle){player.position.x, player.position.y, 40, 40};
        if (currentMapIndex == 0) {
            // Movement logic for map 0
            if (IsKeyDown(KEY_W) && player.position.y > 0) {
                player.position.y -= player.speed;
                if (player.position.y <= 0) {
                    currentMapIndex = 2;
                    player.position.y = screenHeight - 40;
                }
            }
            if (IsKeyDown(KEY_S) && player.position.y < screenHeight - 40) {
                player.position.y += player.speed;
            }
            if (IsKeyDown(KEY_A) && player.position.x > 0) {
                player.position.x -= player.speed;
            }
            if (IsKeyDown(KEY_D) && player.position.x < screenWidth - 40) {
                player.position.x += player.speed;
                if (player.position.x >= screenWidth - 40)
                {
                    currentMapIndex = 1;
                    player.position.x = 0;
                }
            }
        }
        else if (currentMapIndex == 1) {
            // Movement logic for map 1
            if (IsKeyDown(KEY_W) && player.position.y > 0) {
                player.position.y -= player.speed;
                if (player.position.y <= 0) {
                    currentMapIndex = 3;
                    player.position.y = screenHeight - 40;
                }
            }
            if (IsKeyDown(KEY_S) && player.position.y < screenHeight - 40) {
                player.position.y += player.speed;
            }
            if (IsKeyDown(KEY_A) && player.position.x > 0) {
                player.position.x -= player.speed;
                if (player.position.x <= 0) {
                    currentMapIndex = 0;
                    player.position.x = screenWidth - 40;
                }
            }
            if (IsKeyDown(KEY_D) && player.position.x < screenWidth - 40) {
                player.position.x += player.speed;
            }
        }
        else if (currentMapIndex == 2)
        {
            // Movement logic for map 2
            if (IsKeyDown(KEY_W) && player.position.y > 0) {
                player.position.y -= player.speed;
                if (player.position.y <= 0) {
                    player.position.y = 0;
                }
            }
            if (IsKeyDown(KEY_S) && player.position.y < screenHeight - 40) {
                player.position.y += player.speed;
                if (player.position.y >= screenHeight - 40) {
                    currentMapIndex = 0;
                    player.position.y = 0;
                }
            }
            if (IsKeyDown(KEY_A) && player.position.x > 0) {
                player.position.x -= player.speed;
                if (player.position.x <= 0) {
                    player.position.x = 0;
                }
            }
            if (IsKeyDown(KEY_D) && player.position.x < screenWidth - 40)
            {
                player.position.x += player.speed;
                if (player.position.x >= screenWidth - 40) {

                    currentMapIndex = 3;
                    player.position.x = 0;
                }
            }
        }
        else if (currentMapIndex == 3) {
            // Movement logic for map 3
            if (IsKeyDown(KEY_W) && player.position.y > 0) {
                player.position.y -= player.speed;
                if (player.position.y <= 0) {

                    player.position.y = 0;
                }
            }
            if (IsKeyDown(KEY_S) && player.position.y < screenHeight - 40) {
                player.position.y += player.speed;
                if (player.position.y >= screenHeight - 40) {

                    currentMapIndex = 1;
                    player.position.y = 0;
                }
            }
            if (IsKeyDown(KEY_A) && player.position.x > 0) {
                player.position.x -= player.speed;
                if (player.position.x <= 0) {

                    currentMapIndex = 2;
                    player.position.x = screenWidth - 40;
                }
            }
            if (IsKeyDown(KEY_D) && player.position.x < screenWidth - 40) {
                player.position.x += player.speed;
                if (player.position.x >= screenWidth - 40) {

                    player.position.x = screenWidth - 40;
                }
            }
            // Additional conditions for map 3
            if (player.position.y <= 0 && player.position.x >= screenWidth - 40) {

                player.position.y = 0;
                player.position.x = screenWidth - 40;
            }
        }
        for (int i = 0; i < 4; i++) {
            Rectangle chestBounds = {
                maps[currentMapIndex].chest.position.x,
                maps[currentMapIndex].chest.position.y,
                maps[currentMapIndex].chest.texture.width,
                maps[currentMapIndex].chest.texture.height};

            if (CheckCollisionRecs(player.bounds, chestBounds)) {
                if (player.position.x < maps[currentMapIndex].chest.position.x) {
                    player.position.x -= player.speed;
                }
                else {
                    player.position.x += player.speed;
                }

                if (player.position.y < maps[currentMapIndex].chest.position.y) {
                    player.position.y -= player.speed;
                }
                else {
                    player.position.y += player.speed;
                }
            }
        }
        Rectangle fortressBounds = {
            maps[currentMapIndex].chest.position.x,
            maps[currentMapIndex].chest.position.y,
            maps[currentMapIndex].chest.texture.width,
            maps[currentMapIndex].chest.texture.height};

        if (CheckCollisionRecs(player.bounds, fortressBounds)) {
            Vector2 vectorToFortress = Vector2Subtract(maps[currentMapIndex].chest.position, player.position);
            vectorToFortress = Vector2Normalize(vectorToFortress);
            player.position = Vector2Add(player.position, Vector2Scale(vectorToFortress, player.speed));
        }
        for (int i = 0; i < 3; i++) {
            Object currentObject;
            switch (i) {
            case 0:
                currentObject = maps[currentMapIndex].object1;
                break;
            case 1:
                currentObject = maps[currentMapIndex].object2;
                break;
            case 2:
                currentObject = maps[currentMapIndex].object3;
                break;
            default:
                break;
            }
            if (currentObject.active) {
                Rectangle objectBounds = {
                    currentObject.position.x,
                    currentObject.position.y,
                    currentObject.texture.width,
                    currentObject.texture.height};

                if (CheckCollisionRecs(player.bounds, objectBounds)) {
                    if (player.position.x < currentObject.position.x) {
                        player.position.x -= player.speed;
                    }
                    else {
                        player.position.x += player.speed;
                    }

                    if (player.position.y < currentObject.position.y) {
                        player.position.y -= player.speed;
                    }
                    else {
                        player.position.y += player.speed;
                    }
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw current map background
        DrawTexture(maps[currentMapIndex].background, 0, 0, WHITE);

        // Draw chests
        if (maps[currentMapIndex].chest.active) {
            DrawTexture(maps[currentMapIndex].chest.texture, maps[currentMapIndex].chest.position.x, maps[currentMapIndex].chest.position.y, WHITE);
        }
        if (maps[currentMapIndex].object1.active) {
            DrawTexture(maps[currentMapIndex].object1.texture, maps[currentMapIndex].object1.position.x, maps[currentMapIndex].object1.position.y, WHITE);
        }
        if (maps[currentMapIndex].object2.active) {
            DrawTexture(maps[currentMapIndex].object2.texture, maps[currentMapIndex].object2.position.x, maps[currentMapIndex].object2.position.y, WHITE);
        }
        if (maps[currentMapIndex].object3.active) {
            DrawTexture(maps[currentMapIndex].object3.texture, maps[currentMapIndex].object3.position.x, maps[currentMapIndex].object3.position.y, WHITE);
        }
        if (maps[currentMapIndex].additionalObject.active) {
            DrawTexture(maps[currentMapIndex].additionalObject.texture, maps[currentMapIndex].additionalObject.position.x, maps[currentMapIndex].additionalObject.position.y, WHITE);
        }

        // Draw character
        DrawRectangle(player.position.x, player.position.y, 40, 40, player.color);

        EndDrawing();
    }
    UnloadTexture(chestTexture);
    UnloadTexture(objectTexture1);
    UnloadTexture(objectTexture2);
    UnloadTexture(objectTexture3);
    UnloadTexture(additionalObjectTexture);
    for (int i = 0; i < 4; i++) {
        UnloadTexture(maps[i].background);
    }
    CloseAudioDevice();
    CloseWindow();
}