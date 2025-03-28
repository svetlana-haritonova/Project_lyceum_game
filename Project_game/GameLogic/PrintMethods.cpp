﻿#include "Game.h"
#include "../Constants/Constants.h"
#include <windows.h>
#include <iostream>
#include <conio.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;

void Game::PrintMenu(int x, int y, const vector<string>&menu, int choice) { //функция для отрисовки разного меню
    GoToXY(x, y);
    for (int i = 0; i < menu.size(); ++i) {
        GoToXY(x, y + i);
        if (i == choice) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLACK | BACKGROUND_WHITE); //если курсор на какой-то опции, то выделяем её
        }
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        cout << menu[i] << endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_BLACK); //возвращаем обычные параметры текста
}

void Game::PrintField(int x, int y, const vector<vector<std::string>>& field, const string& hidden_word, const vector<bool>& check_for_paint_line) { //функция для отрисовки поля
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            GoToXY(x + j * 7, i * 4 + y); //невероятные математические рассчёт чтобы поле красиво печаталось со всеми отступами и без лишних переменных
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY);
            cout << "_______";
            if (check_for_paint_line[i]) { //если слово сохранено, то окрашиваем его
                if (std::find(hidden_word.begin(), hidden_word.end(), field[i][j][0]) != hidden_word.end()) {
                    if (field[i][j][0] == hidden_word[j]) { //используем [0], потому что поле из вектора строк
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_GREEN); //если угадали положение и букву красим её зеленым
                    }
                    else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_YELLOW); //если угадали букву но не угадали её положение красим желтым
                    }
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_RED); //если не угадали букву красим красным
                }
            }
            GoToXY(x + j * 7, i * 4 + y + 1);
            cout << "|     |";
            GoToXY(x + j * 7, i * 4 + y + 2);
            cout << "|  " << field[i][j] << "  |";
            GoToXY(x + j * 7, i * 4 + y + 3);
            cout << "|_____|";
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY); //после отрисовки возвращаем простые параметры для курсора
}

void Game::PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
    int& keyboard_row, int& keyboard_column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line) { //функция для отображения клавиатуры + управление клавиатурой и изменение полей слова
    for (int i = 0; i < keyboard.size(); ++i) {
        for (int j = 0; j < keyboard[i].size(); ++j) {
            GoToXY(x + j * 3, y + i * 2); //ещё одни невероятные математические рассчёты, j * 3 расстояние между буквой от другой буквы, i * 2 опуститься вниз с пробелом
            if (keyboard[i][j] != " ") { //убедитесь, что мы не выводим пробелы
                if (i == keyboard_row && j == keyboard_column) { //отображение клавиатуры, если курсор на букве в консоли, то выделяем ее
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    cout << "[" << keyboard[i][j] << "]";
                }
                else { //если курсор не на букве печатаем серым
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY);
                    cout << "[" << keyboard[i][j] << "]";
                }
            }
        }
        cout << endl;
    }
}


void Game::PrintIntrodaction() { //функция отображения приветствия
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PINK);
    GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
    cout << "WELCOME TO 'LE_WORD'";
    GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y) + 1);
    cout << "CHOOSE YOUR LANGUAGE";
}

void Game::PrintGameResult(const string& language, bool win, const string& hidden_word, const vector<string>& ending_menu) {
    if (win) { //если win == true значит, что отгадали слово
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
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y) + 1, ending_menu_Russian) == "НАЧАТЬ ЗАНОВО") {
                    break;
                }
                else { //если мы нажали на выход выходим из программы
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
                if (MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y), ending_menu_Russian) == "НАЧАТЬ ЗАНОВО") {
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
