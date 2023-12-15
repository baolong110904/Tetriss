#ifndef MENU_H
#define MENU_H

#include <raylib.h>

class Menu {
public:
    Menu();
    Color getRandomColor();
    int showMenu();
    int showHelpScreen();
    void drawHelpScreen();
    Music music;
    Sound moveSound;

private:
    int selectedOption;
    Rectangle playEasyButton;
    Rectangle playHardButton;
    Rectangle helpButton;
    Rectangle backButton;
    Rectangle exitButton;

    void drawMenu();
};

#endif