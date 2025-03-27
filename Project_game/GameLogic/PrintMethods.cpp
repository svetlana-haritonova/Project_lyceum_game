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

void Game::PrintField(int x, int y, const vector<vector<std::string>>& field, const string& hidden_word, const vector<bool>& check_for_paint_line) { //a function for rendering a field. Works for a different number of letters
    int const_x = x, const_y = y;
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY);
            GoToXY(x, y);
            cout << "_______";
            ++y;
            if (check_for_paint_line[i]) {
                if (std::find(hidden_word.begin(), hidden_word.end(), field[i][j][0]) != hidden_word.end()) {
                    if (field[i][j][0] == hidden_word[j]) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) | BACKGROUND_GREEN);
                    }
                    else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) | (BACKGROUND_RED | BACKGROUND_GREEN));
                    }
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) | BACKGROUND_RED);
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
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY);
}

void Game::PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
    int& row, int& column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line) { //a function for rendering the keyboard + keyboard controlling and changing the word fields
    for (int i = 0; i < keyboard.size(); ++i) {
        for (int j = 0; j < keyboard[i].size(); ++j) {
            GoToXY(x + j * 3, y + i * 2); //j * 3 a distance for the letter and the bracket, i * 2 go down
            if (keyboard[i][j] != " ") { //check that we are not displaying spaces
                if (i == row && j == column) { //display the keyboard. If we point to a letter on the console, we highlight it.
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                    cout << "[" << keyboard[i][j] << "]";
                }
                else { //print others in grey
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
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
    cout << "WELCOME TO  'LE_WORD'";
    GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
    cout << "CHOOSE YOUR LANGUAGE";
}

void Game::PrintGameResult(const string& language, bool win, const string& hidden_word, const vector<string>& ending_menu) {
    if (win) {
        if (language == "RUSSIAN") {
            while (true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
                cout << "      œŒ«ƒ–¿¬Àﬂ≈Ã!";
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
                cout << "    ¬€ ”√¿ƒ¿À» —ÀŒ¬Œ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 2);
                cout << "«¿√¿ƒÕÕŒ≈ —ÀŒ¬Œ: ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << hidden_word;
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y) + 1, ending_menu_Russian) == "¬€…“»") {
                    exit(0);
                }
                else {
                    break;
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
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 2);
                cout << " HIDDEN WORD : ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << hidden_word;
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 3);
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y) + 1, ending_menu_English) == "EXIT") {
                    exit(0);
                }
                else {
                    break;
                }
            }
        }
    }
    else {
        if (language == "RUSSIAN") {
            while (true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
                cout << "      ¬€ œ–Œ»√–¿À» ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
                cout << "«¿√¿ƒÕÕŒ≈ —ÀŒ¬Œ: ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << hidden_word;
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y), ending_menu_Russian) == "Õ¿◊¿“‹ «¿ÕŒ¬Œ") {
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
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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