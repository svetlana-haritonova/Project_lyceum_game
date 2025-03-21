#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <stdexcept>
#include "Constants\Constants.h"
#include "Functions\Functions.h"

using std::vector;
using std::fstream;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::min;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //получаем дескриптор консоли, чтобы работать с ней

int main() {
    SetConsoleTitle(L"Игра в слова");
    system("CLS");
    setlocale(0, "Rus");
    ConsoleCursorVisible(false, 100);


    GoToXY(50, 10);
    cout << "WELCOME TO YOUR GAME";
    GoToXY(50, 11);
    cout << "CHOOSE YOUR LANGUAGE";


    string language = MenuChoice(56, 12, menu_of_languages);
    GoToXY(50, 10);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE); //синий


    int letters = 0;

    int row = 0;
    int column = 0;
    int field_row = 0;
    int field_column = 0;
    string hidden_word, entered_word;

    if (language == "RUSSIAN") {
        cout << "ВЫБЕРИТЕ РЕЖИМ ИГРЫ";
        stringstream option(MenuChoice(50, 11, menu_of_options_Russian));
        option >> letters;
        vector<vector<string>> field = CreateField(letters, letters);
        vector<bool> check_for_painting_line(letters, false);
        switch (letters) {
        case 5:
            hidden_word = GetRandomWord("Dictionaries/Russian_5.txt");
            break;
        case 6:
            hidden_word = GetRandomWord("Dictionaries/Russian_6.txt");
            break;
        case 7:
            hidden_word = GetRandomWord("Dictionaries/Russian_7.txt");
            break;
        default:
            break;
        }
        while (true) {
            PrintField(50, 1, field, hidden_word, check_for_painting_line);
            if (entered_word == hidden_word || field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
                system("CLS");
                break;
            }
            PrintKeyboard(15, letters * 2 + 1, Russian_keyboard, field, row, column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
        }
        if (entered_word == hidden_word) {
            while (true) {
                SetConsoleTextAttribute(hStdOut, 8 | 8);
                GoToXY(50, 10);
                cout << "ПОЗДРАВЛЯЕМ!";
                GoToXY(48, 11);
                cout << "ВЫ УГАДАЛИ СЛОВО";
                GoToXY(47, 12);
                cout << "ЗАГАДННОЕ СЛОВО: " << hidden_word;
            }
        }
        else if (field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
            while (true) {
                SetConsoleTextAttribute(hStdOut, 8 | 8);
                GoToXY(50, 10);
                cout << "ВЫ ПРОИГРАЛИ";
                GoToXY(47, 11);
                cout << "ЗАГАДННОЕ СЛОВО: " << hidden_word;
            }
        }
    } else if (language == "ENGLISH") {
        cout << "CHOOSE GAME OPTION";
        stringstream option(MenuChoice(50, 11, menu_of_options_English));
        option >> letters;
        vector<vector<string>> field = CreateField(letters, letters);
        vector<bool> check_for_painting_line(letters, false);
        switch (letters) {
        case 5:
            hidden_word = GetRandomWord("Dictionaries/English_5.txt");
            break;
        case 6:
            hidden_word = GetRandomWord("Dictionaries/English_6.txt");
            break;
        case 7:
            hidden_word = GetRandomWord("Dictionaries/English_7.txt");
            break;
        default:
            break;
        }
        while (true) {
            PrintField(50, 1, field, hidden_word, check_for_painting_line);
            if (entered_word == hidden_word || field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
                SetConsoleTextAttribute(hStdOut, 8 | 8);
                system("CLS");
                break;
            }
            PrintKeyboard(15, letters * 2 + 1, English_keyboard, field, row, column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
        }
        if (entered_word == hidden_word) {
            while (true) {
                GoToXY(50, 10);
                SetConsoleTextAttribute(hStdOut, 8 | 8);
                cout << "CONGRATULATIONS!";
                GoToXY(48, 11);
                cout << "YOU GUESSED THE WORD";
                GoToXY(49, 12);
                cout << "HIDDEN WORD: " << hidden_word;
            }
        }
        else if (field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
            while (true) {
                SetConsoleTextAttribute(hStdOut, 8 | 8); //поправить фон
                GoToXY(50, 10);
                cout << "YOU'VE LOST";
                GoToXY(47, 11);
                cout << "HIDDEN WORD: " << hidden_word;
            }
        }
    }
 }