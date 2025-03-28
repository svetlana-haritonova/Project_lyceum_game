#include "Game.h"
#include "../Constants/Constants.h"
#include <windows.h>
#include <iostream>
#include <conio.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;

void Game::PrintMenu(int x, int y, const vector<string>&menu, int choice) { //func for drawing different menu
    GoToXY(x, y);
    for (int i = 0; i < menu.size(); ++i) {
        GoToXY(x, y + i);
        if (i == choice) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLACK | BACKGROUND_WHITE); //if we take cursor on option we highlight it
        }
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        cout << menu[i] << endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_BLACK); //return simple drawing parameters
}

void Game::PrintField(int x, int y, const vector<vector<std::string>>& field, const string& hidden_word, const vector<bool>& check_for_paint_line) { //a function for drawing a field
    int begin_x = x, begin_y = y; //varaibles for correct drawing field which fix last cursor position
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            GoToXY(x, y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY);
            cout << "_______";
            ++y;
            if (check_for_paint_line[i]) { //if we save word paint it
                if (std::find(hidden_word.begin(), hidden_word.end(), field[i][j][0]) != hidden_word.end()) {
                    if (field[i][j][0] == hidden_word[j]) { //take [0] because field string vector
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_GREEN);
                    }
                    else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_YELLOW);
                    }
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_RED);
                }
            }
            GoToXY(x, y);
            cout << "|     |";
            ++y;
            GoToXY(x, y);
            cout << "|  " << field[i][j] << "  |";
            ++y;
            GoToXY(x, y);
            cout << "|_____|";
            x += 7;
            y = begin_y;
        }
        y = y + 4;
        begin_y = y;
        x = begin_x;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY); //after drawing return simple parametrs for cursore
}

void Game::PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
    int& keyboard_row, int& keyboard_column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line) { //a function for rendering the keyboard + keyboard controlling and changing the word fields
    for (int i = 0; i < keyboard.size(); ++i) {
        for (int j = 0; j < keyboard[i].size(); ++j) {
            GoToXY(x + j * 3, y + i * 2); //j * 3 a distance for the letter and the bracket, i * 2 go down
            if (keyboard[i][j] != " ") { //check that we are not display whitespaces
                if (i == keyboard_row && j == keyboard_column) { //display the keyboard. If we point to a letter on the console, we highlight it.
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    cout << "[" << keyboard[i][j] << "]";
                }
                else { //print others in grey
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY);
                    cout << "[" << keyboard[i][j] << "]";
                }
            }
        }
        cout << endl;
    }
}


void Game::PrintIntrodaction() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PINK);
    GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
    cout << "WELCOME TO 'LE_WORD'";
    GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
    cout << "CHOOSE YOUR LANGUAGE";
}

void Game::PrintGameResult(const string& language, bool win, const string& hidden_word, const vector<string>& ending_menu) {
    setlocale(0, "Rus");
    if (win) { //if win == true means we guess the word
        if (language == "RUSSIAN") {
            while (true) {
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                 GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
                 cout << "      ПОЗДРАВЛЯЕМ!";
                 GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
                 cout << "    ВЫ УГАДАЛИ СЛОВО";
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                 GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 2);
                 cout << "ЗАГАДННОЕ СЛОВО: ";
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                 cout << hidden_word;
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y) + 1, ending_menu_Russian) == "ÍÀ×ÀÒÜ ÇÀÍÎÂÎ") {
                    break;
                }
                else {
                    exit(0);
                }
            }
        }
        else {
            while (true) {
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                cout << "   CONGRATULATIONS!";
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
                cout << " YOU GUESSED THE WORD";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 2);
                cout << " HIDDEN WORD : ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << hidden_word;
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 3);
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y) + 1, ending_menu_English) == "START AGAIN") {
                    break;
                }
                else {
                    exit(0);
                }
            }
        }
    }
    else {
        if (language == "RUSSIAN") {
            while (true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
                cout << "      ВЫ ПРОИГРАЛИ ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
                cout << "ЗАГАДННОЕ СЛОВО: ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << hidden_word;
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y), ending_menu_Russian) == "ÍÀ×ÀÒÜ ÇÀÍÎÂÎ") {
                    break;
                }
                else {
                    exit(0);
                }
            }
        }
        else {
            while (true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
                cout << "      YOU'VE LOST";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
                cout << "   HIDDEN WORD: ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << hidden_word;
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y), ending_menu_English) == "START AGAIN") {
                    break;
                }
                else {
                    exit(0);
                }
            }
        }
    }
}
