#include "raylib.h"
#include "header.h"
void DrawCloseButton(Rectangle closeButtonRect, bool closeButtonClicked) {
    DrawText("X", closeButtonRect.x + 10, closeButtonRect.y + 8, 20, (closeButtonClicked) ? RED : MAROON);
}
