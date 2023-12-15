#include "menu.h"

float lastColorChangeTime = GetTime();
Color currentTextColor = WHITE;

Menu::Menu() {
    selectedOption = 0;
    playEasyButton = { 50, 200, 300, 50 };
    playHardButton = { 50, 300, 300, 50 };
    helpButton = { 50, 400, 300, 50 };
    backButton = { 50, 500, 300, 50 };
    exitButton = { 50, 600, 300, 50 };
    InitAudioDevice();
    moveSound = LoadSound("Music/Move.wav");
    music = LoadMusicStream("Music/MenuBackground.mp3");
    PlayMusicStream(music);
}

Color Menu::getRandomColor() {
    Color randomColor = { GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
    return randomColor;
}

void Menu::drawMenu() {
    BeginDrawing();
    ClearBackground({ 26, 31, 40, 255 });

    float currentTime = GetTime();
    if (currentTime - lastColorChangeTime >= 1.0f) {
        currentTextColor = getRandomColor();
        lastColorChangeTime = currentTime;
    }

    DrawText("T", 100, 50, 50, currentTextColor);
    DrawText("E", 160, 50, 50, currentTextColor);
    DrawText("T", 220, 50, 50, currentTextColor);
    DrawText("R", 280, 50, 50, currentTextColor);
    DrawText("I", 340, 50, 50, currentTextColor);
    DrawText("S", 400, 50, 50, currentTextColor);


    // Draw buttons
    DrawRectangleRec(playEasyButton, (selectedOption == 0) ? RED : GRAY);
    DrawRectangleRec(playHardButton, (selectedOption == 1) ? RED : GRAY);
    DrawRectangleRec(helpButton, (selectedOption == 2) ? RED : GRAY);
    DrawRectangleRec(backButton, (selectedOption == 3) ? RED : GRAY);
    DrawRectangleRec(exitButton, (selectedOption == 4) ? RED : GRAY);

    // Draw text
    DrawText("Play Easy", 100, 210, 30, WHITE);
    DrawText("Play Hard", 100, 310, 30, WHITE);
    DrawText("Help", 100, 410, 30, WHITE);
    DrawText("Back", 100, 510, 30, WHITE);
    DrawText("Exit", 100, 610, 30, WHITE);

    EndDrawing();
}
void Menu::drawHelpScreen() {
    BeginDrawing();
    ClearBackground({ 26, 31, 40, 255 });


    float currentTime = GetTime();
    if (currentTime - lastColorChangeTime >= 1.0f) {
        currentTextColor = getRandomColor();
        lastColorChangeTime = currentTime;
    }

    DrawText("T", 80, 50, 50, currentTextColor);
    DrawText("E", 140, 50, 50, currentTextColor);
    DrawText("T", 200, 50, 50, currentTextColor);
    DrawText("R", 260, 50, 50, currentTextColor);
    DrawText("I", 320, 50, 50, currentTextColor);
    DrawText("S", 380, 50, 50, currentTextColor);

    // Draw rectangles for sections
    DrawRectangle(80, 120, 340, 50, { 62, 73, 93, 255 });   // Rectangle for "Objective"
    DrawRectangle(80, 260, 340, 50, { 62, 73, 93, 255 });   // Rectangle for "Controls"
    DrawRectangle(80, 400, 340, 50, { 62, 73, 93, 255 });   // Rectangle for "Scoring"

    DrawText("Objective:", 100, 130, 25, WHITE);
    DrawText("Move and rotate falling blocks to", 100, 170, 20, WHITE);
    DrawText("create solid rows, which will", 100, 190, 20, WHITE);
    DrawText("disappear and earn points.", 100, 210, 20, WHITE);

    DrawText("Controls:", 100, 270, 25, WHITE);
    DrawText("LEFT/RIGHT arrows - Move", 100, 310, 20, WHITE);
    DrawText("DOWN arrow - Move down faster", 100, 330, 20, WHITE);
    DrawText("UP arrow - Rotate", 100, 350, 20, WHITE);
    DrawText("SPACE bar - Drop", 100, 370, 20, WHITE);

    DrawText("Scoring:", 100, 420, 25, WHITE);
    DrawText("Clear 1 line - 100 points", 100, 450, 20, WHITE);
    DrawText("Clear 2 lines - 300 points", 100, 470, 20, WHITE);
    DrawText("Clear 3 lines - 500 points", 100, 490, 20, WHITE);
    DrawText("Clear 4 lines (Tetris) - Bonus", 100, 510, 20, WHITE);

    // Draw "Turn Back" button
    DrawRectangle(80, 560, 340, 50, { 62, 73, 93, 255 });
    DrawText("Back", 170, 570, 25, WHITE);

    EndDrawing();
}
int Menu::showHelpScreen() {
    while (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !WindowShouldClose()) {
        drawHelpScreen();
        UpdateMusicStream(music);

        int key = GetKeyPressed();
        if (key == KEY_ESCAPE || key == KEY_ENTER || key == KEY_SPACE) {
            return -1;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), { 80, 560, 340, 50 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return 0;  // "Turn Back" button pressed
        }
    }
    return -1;
}
int Menu::showMenu() {
    
    while (!WindowShouldClose()) {
        drawMenu();
        UpdateMusicStream(music);

        int key = GetKeyPressed();
        if (key == KEY_UP) {
            selectedOption = (selectedOption - 1 + 5) % 5;
            PlaySound(moveSound);
        }
        else if (key == KEY_DOWN) {
            selectedOption = (selectedOption + 1) % 5;
            PlaySound(moveSound);
        }
        else if (key == KEY_ENTER || key == KEY_SPACE) {
            if (selectedOption == 2) {
                // Show help screen
                int result = showHelpScreen();
                if (result == 0) {
                    // Back button pressed in the help screen, return to main menu
                    continue;
                }
            }
            return selectedOption;
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            return 4;  // Exit if Esc is pressed
        }

        // Add delay to avoid high CPU usage
        // You may need to adjust this based on your game loop
        // For example, if your game loop runs at 60 FPS, delay for 16 milliseconds
        // Adjust as needed to achieve smooth performance
        // NOTE: This delay is added here just for the example; you may need to integrate it into your game loop
        // to avoid high CPU usage.

    }

    return -1;  // Return -1 if the window is closed
}

