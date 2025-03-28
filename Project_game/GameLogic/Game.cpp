#include "Game.h"
#include "../Constants/Constants.h"
#include <windows.h>

Game::Game() { //инициализация конструктора класса 
    language = ""; //инициализация полей класса
    letters = 0;
    entered_word = "";
    hidden_word = "";
    field = {};
    check_for_painting_line = {};
}

void Game::Run() {
    while (true) {
        SetConsoleTitle(L"LE_WORD"); //установка тайтла игры
        system("CLS");
        setlocale(0, "Rus"); //установка русской локали
        ConsoleCursorVisible(false, CURSOR_SIZE);
        PrintIntrodaction();
        language = MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y), menu_of_languages);
        SetGameAttributes(language, hidden_word, field, check_for_painting_line, letters);
    }
}