#include "raylib.h"
#include "header.h"
int main() {
    const int screenWidth = 1100;
    const int screenHeight = 800;

    Color customColor = {27, 35, 23, 255};

    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "Quest for the Royal Key: A Knight's Puzzle Adventure");

    Texture2D background = LoadTexture("sources/menuWindow/2024-02-25 18.51.31.png");

    // Load music file
    Music backgroundMusic = LoadMusicStream("sources/menuWindow/musicMenu.wav");
    SetMusicVolume(backgroundMusic, 1.0f);
    PlayMusicStream(backgroundMusic);

    Rectangle playButton = {screenWidth / 2 - 100, 200, 200, 70};
    Rectangle howToPlayButton = {screenWidth / 2 - 100, 300, 200, 70};
    Rectangle exitButton = {screenWidth / 2 - 100, 400, 200, 70};
    Rectangle closeButtonTable = {screenWidth - 150, 110, 30, 40};
    Rectangle infoButton = {screenWidth - 80, 10, 40, 40};
    Rectangle soundButton = {screenWidth - 90 - 40, 10, 40, 40};

    // Flags to track button states
    bool playButtonClicked = false;
    bool howToPlayButtonClicked = false;
    bool exitButtonClicked = false;
    bool closeButtonTableClicked = false;
    bool howToPlayTableVisible = false;
    bool infoButtonClicked = false;
    bool infoTableVisible = false;

    bool soundButtonClicked = IsMusicStreamPlaying(backgroundMusic);

    // Load sound button textures
    Image soundOnImage = LoadImage("sources/menuWindow/sound-speaker-icon-on-white-background-free-vector.png");
    Image soundOffImage = LoadImage("sources/menuWindow/do-not-make-a-loud-noise-no-speaker-no-sound-icon-free-vector.png");

    // Scale the sound icons
    ImageResize(&soundOnImage, 40, 40);
    ImageResize(&soundOffImage, 40, 40);

    // Load the resized images as textures
    Texture2D soundOnTexture = LoadTextureFromImage(soundOnImage);
    Texture2D soundOffTexture = LoadTextureFromImage(soundOffImage);

    // Unload the images as they are no longer needed
    UnloadImage(soundOnImage);
    UnloadImage(soundOffImage);

    // Load info button textures
    Image infoImage = LoadImage("sources/menuWindow/information-icon-white-22.png");
    ImageResize(&infoImage, 40, 40);

    // Load the resized image as a texture
    Texture2D infoTexture = LoadTextureFromImage(infoImage);
    UnloadImage(infoImage);

    // Load a TTF font
    Font gameFont = LoadFont("sources/RINGM___.TTF"); 
    SetTextureFilter(gameFont.texture, TEXTURE_FILTER_POINT);  

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, playButton)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Open the new game window when 'Play' is clicked
                CloseWindow();
                InitGameWindow();
            }
        }
        else if (CheckCollisionPointRec(mousePoint, exitButton)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
            }
        }

        // Check button click events
        if (CheckCollisionPointRec(mousePoint, soundButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            soundButtonClicked = !soundButtonClicked;
            if (soundButtonClicked) {
                if (GetMusicTimePlayed(backgroundMusic) > 0) {
                    ResumeMusicStream(backgroundMusic);
                }
                else {
                    PlayMusicStream(backgroundMusic);
                }
            }
            else {
                StopMusicStream(backgroundMusic);
            }
        }

        // UpdateMusicStream should be called before checking collision with buttons
        UpdateMusicStream(backgroundMusic);

        // Check button click events for 'How to Play' and 'i' buttons
        if (CheckCollisionPointRec(mousePoint, howToPlayButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            howToPlayButtonClicked = IsMusicStreamPlaying(backgroundMusic);
            howToPlayButtonClicked = !howToPlayButtonClicked;
            howToPlayTableVisible = !howToPlayTableVisible;
        }

        if (CheckCollisionPointRec(mousePoint, infoButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            infoButtonClicked = !infoButtonClicked;
            infoTableVisible = !infoTableVisible;
        }

        // Check button click events
        if (CheckCollisionPointRec(mousePoint, playButton)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                playButtonClicked = !playButtonClicked;
            }
        }
        else if (CheckCollisionPointRec(mousePoint, exitButton)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
            }
        }
        else if (CheckCollisionPointRec(mousePoint, closeButtonTable) && (howToPlayTableVisible || infoTableVisible)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                closeButtonTableClicked = true;
            }
        }

        // Update table visibility
        if (closeButtonTableClicked) {
            howToPlayTableVisible = false;
            infoTableVisible = false;
            closeButtonTableClicked = false; 
            howToPlayButtonClicked = false; 
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw background
        DrawTexture(background, 0, 0, WHITE);

        // Draw title with the loaded font
        DrawTextEx(gameFont, "Quest for the Royal Key:", (Vector2){screenWidth / 3 - MeasureTextEx(gameFont, "Game", 20, 0).x / 2, 50},
                   40, 0, customColor);
        DrawTextEx(gameFont, "A Knight's Puzzle Adventure", (Vector2){screenWidth / 3 - MeasureTextEx(gameFont, "Game", 20, 0).x / 2, 100},
                   40, 0, customColor);


        // Draw buttons with hover and click effects
        DrawRectangleRounded(playButton, 0.2, 0, (playButtonClicked) ? GRAY : CheckCollisionPointRec(mousePoint, playButton) ? DARKGRAY : WHITE);
        DrawRectangleRounded(howToPlayButton, 0.2, 0, (howToPlayButtonClicked) ? GRAY : CheckCollisionPointRec(mousePoint, howToPlayButton) ? DARKGRAY : WHITE);
        DrawRectangleRounded(exitButton, 0.2, 0, (exitButtonClicked) ? GRAY : CheckCollisionPointRec(mousePoint, exitButton) ? DARKGRAY : WHITE);
        DrawRectangleRounded(infoButton, 0.2, 0, (infoButtonClicked) ? GRAY : CheckCollisionPointRec(mousePoint, infoButton) ? DARKGRAY : WHITE);
        DrawRectangleRounded(soundButton, 0.2, 0, (soundButtonClicked) ? GRAY : CheckCollisionPointRec(mousePoint, soundButton) ? DARKGRAY : WHITE);

        // Draw sound button texture without a rectangle
        DrawTexture((IsMusicStreamPlaying(backgroundMusic) ? soundOnTexture : soundOffTexture),
                     soundButton.x + (soundButton.width - soundOnTexture.width) / 2,
                     soundButton.y + (soundButton.height - soundOnTexture.height) / 2, WHITE);

        // Draw button labels
        DrawTextEx(gameFont, "Play", (Vector2){playButton.x + playButton.width / 2 - MeasureTextEx(gameFont, "Play", 20, 0).x / 2,
                                                playButton.y + playButton.height / 2 - 10},
                   20, 0, (playButtonClicked) ? WHITE : BLACK);
        DrawTextEx(gameFont, "How to Play", (Vector2){howToPlayButton.x + howToPlayButton.width / 2 -
                                                      MeasureTextEx(gameFont, "How to Play", 20, 0).x / 2,
                                                      howToPlayButton.y + howToPlayButton.height / 2 - 10},
                   20, 0, (howToPlayButtonClicked) ? WHITE : BLACK);
        DrawTextEx(gameFont, "Exit", (Vector2){exitButton.x + exitButton.width / 2 - MeasureTextEx(gameFont, "Exit", 20, 0).x / 2,
                                               exitButton.y + exitButton.height / 2 - 10},
                   20, 0, (exitButtonClicked) ? WHITE : BLACK);
        DrawTextEx(gameFont, "i", (Vector2){infoButton.x + infoButton.width / 2 - MeasureTextEx(gameFont, "i", 20, 0).x / 2,
                                            infoButton.y + infoButton.height / 2 - 10},
                   20, 0, (infoButtonClicked) ? WHITE : BLACK);

        // Draw info icon over the button
        DrawTexture(infoTexture, infoButton.x + (infoButton.width - infoTexture.width) / 2,
                    infoButton.y + (infoButton.height - infoTexture.height) / 2, WHITE);

        // Draw sound button icons
        if (IsMusicStreamPlaying(backgroundMusic)) {
            DrawTexture(soundOnTexture, soundButton.x + (soundButton.width - soundOnTexture.width) / 2, soundButton.y + (soundButton.height - soundOnTexture.height) / 2, WHITE);
        }
        else {
            DrawTexture(soundOffTexture, soundButton.x + (soundButton.width - soundOffTexture.width) / 2, soundButton.y + (soundButton.height - soundOffTexture.height) / 2, WHITE);
        }
        // Draw pop-up tables
        if (howToPlayTableVisible) {
            DrawRectangle(100, 100, screenWidth - 200, screenHeight - 170, customColor);
            DrawCloseButton(closeButtonTable, closeButtonTableClicked);

            // Draw the main text block
            const char *mainText = "A knight, driven by love and duty, sets out on a perilous quest to rescue a princess imprisoned by a wicked sorcerer. The sorcerer scatters fragments of a mystical key across the state, each guarded by cryptic riddles. The fate of the realm rests on the adventurer's shoulders as they unravel mysteries and answer the call to heroism.";
            DrawWrappedText(mainText, 120, 150, 20, screenWidth - 240, WHITE);

            // Draw 7 lines of text in the first column
            const char *textLines[] = {
            "== Movement Controls ==",
            "Key  W  : Move Forward",
            "Key  S  : Move Backward",
            "Key  A  : Move Left",
            "Key  D  : Move Right",
            "Key  F  : Interact with chests and the castle",
            "Explore the game world using these keys. Have a great adventure!"
            };

            int imageHeight = 20;
            int spacing = 40;
            int startXImages = 120;

            for (int i = 0; i < 7; i++) {
            // Calculate indentation for centering the first line
            int indentation = (i == 0) ? (screenWidth - 240 - MeasureText(textLines[0], 18)) / 2 : 0;
            DrawText(textLines[i], startXImages + indentation, 300 + (imageHeight + spacing) * i, 18, WHITE);
            }
        }   
        if (infoTableVisible) {
            DrawRectangle(100, 100, screenWidth - 200, screenHeight - 200, customColor);

            // Draw 'X' button inside the table
            DrawCloseButton(closeButtonTable, closeButtonTableClicked);

            // Draw title in the center with indentation
            const char *infoTitle = "Our Team";
            int titleWidth = MeasureText(infoTitle, 20);
            int titleX = 120 + (screenWidth - 200 - titleWidth) / 2;
            DrawText(infoTitle, titleX, 120, 20, WHITE);
            const char *infoLines[] = {
                "Lyubava Kharenko - 223a.e.",
                "Koliesnikova Marianna - 1223a",
                "Yuliia Oliinykova - 1223a",
                "Andrii Pidhornyi, - 923g",
            };
            int infoHeight = 20;
            int infoSpacing = 25;
            int startInfoY = 160;
            for (int i = 0; i < 4; i++) {
                DrawText(infoLines[i], 120, startInfoY + (infoHeight + infoSpacing) * i, 20, WHITE);
            }
        }
        EndDrawing();
    }
    // Unload sound button textures
    UnloadTexture(soundOnTexture);
    UnloadTexture(soundOffTexture);

    // Unload info texture
    UnloadTexture(infoTexture);

    // Unload the loaded font
    UnloadFont(gameFont);

    // De-Initialization
    UnloadMusicStream(backgroundMusic);
    UnloadTexture(background);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
