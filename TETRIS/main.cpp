#include <iostream>
#include <raylib.h>
#include "game.h"
#include "menu.h"
using namespace std;

int main() {
    InitWindow(500, 800, "Tetris");
    SetTargetFPS(60);
    srand(time(0));

    
    while (!WindowShouldClose()) {
        Game game;
        Menu mainMenu;
        int menuChoice = mainMenu.showMenu();
        
        while (menuChoice != 4) {
            Game game;
            switch (menuChoice) {
            case 0:
                game.setTick(0.2);
                game.run();
                break;
            case 1:
                game.setTick(0.1);
                game.run();
                break;
            case 2:
                mainMenu.showHelpScreen();
                break;
            case 3:
                menuChoice = mainMenu.showMenu();
                continue;
            default:
                break;
            }

            

            // Show menu again after the game ends
            menuChoice = mainMenu.showMenu();
        }
    }

    CloseWindow();

    return 0;
}