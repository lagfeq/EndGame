#include "raylib.h"
#include "header.h"
char** TextWrap(const char* text, Font font, int fontSize, int maxWidth)
{
    Font defaultFont = GetFontDefault();

    // Check if the provided font is the default font and use the default font in that case
    if (&font == &defaultFont) {
        font = defaultFont;
    }
    // Allocate memory for an array of strings (lines)
    char** lines = (char**)malloc(MAX_LINES * sizeof(char*));

    // Initialize the array to NULL
    for (int i = 0; i < MAX_LINES; i++) {
        lines[i] = NULL;
    }

    // Copy the input text to a mutable buffer
    char buffer[MAX_LINE_LENGTH];
    strncpy(buffer, text, MAX_LINE_LENGTH);
    buffer[MAX_LINE_LENGTH - 1] = '\0'; // Ensure null-termination

    char* token = strtok(buffer, " \n"); // Tokenize the text

    int currentLine = 0;
    while (token != NULL)
    {
        // Allocate memory for the current line
        lines[currentLine] = (char*)malloc((strlen(token) + 1) * sizeof(char));

        // Copy the token to the current line
        strcpy(lines[currentLine], token);

        // Move to the next token
        token = strtok(NULL, " \n");

        // Check if the next token fits in the current line or start a new line
        while (token != NULL && MeasureText(lines[currentLine], fontSize) + MeasureText(" ", fontSize) + MeasureText(token, fontSize) <= maxWidth)
        {
            // Concatenate a space and the next token to the current line
            char* temp = (char*)realloc(lines[currentLine], (strlen(lines[currentLine]) + 2 + strlen(token)) * sizeof(char));
            if (temp != NULL)
            {
                lines[currentLine] = temp;
                strcat(lines[currentLine], " ");
                strcat(lines[currentLine], token);
            }

            // Move to the next token
            token = strtok(NULL, " \n");
        }

        currentLine++;

        // Break the loop if the maximum number of lines is reached
        if (currentLine >= MAX_LINES)
            break;
    }

    return lines;
}

