#include "Game.h"
#include "../Constants/Constants.h"
#include <windows.h>

Game::Game() {
    entered_word = "";
    hidden_word = "";
    language = "";
    field = {};
    check_for_painting_line = {};
    letters = 0;
}

void Game::Run() {
    while (true) {
        SetConsoleTitle(L"LE_WORD");
        system("CLS");
        setlocale(0, "Rus");
        ConsoleCursorVisible(false, CURSOR_SIZE);
        PrintIntrodaction();
        language = MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y), menu_of_languages);
        SetGameAttributes(language, hidden_word, field, check_for_painting_line, letters);
    }
}