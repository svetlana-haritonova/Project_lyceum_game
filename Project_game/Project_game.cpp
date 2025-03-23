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
    while (true) {
        SetConsoleTitle(L"LE_WORD");
        system("CLS");
        setlocale(0, "Rus");
        ConsoleCursorVisible(false, 100);

        GoToXY(50, 10);
        cout << "WELCOME TO YOUR GAME";
        GoToXY(50, 11);
        cout << "CHOOSE YOUR LANGUAGE";


        string language = MenuChoice(56, 12, menu_of_languages);
        GoToXY(50, 10);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        int letters = 0;
        string hidden_word, entered_word;

        if (language == "RUSSIAN") {
            cout << "ВЫБЕРИТЕ РЕЖИМ ИГРЫ";
            stringstream option(MenuChoice(56, 11, menu_of_options_Russian));
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
            if (EnterWord(10, letters * 2 + 1, 50, 1, Russian_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
                while (true) {
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    GoToXY(50, 10);
                    cout << "ПОЗДРАВЛЯЕМ!";
                    GoToXY(48, 11);
                    cout << "ВЫ УГАДАЛИ СЛОВО";
                    GoToXY(47, 12);
                    cout << "ЗАГАДННОЕ СЛОВО: " << hidden_word;
                    if (MenuChoice(48, 13, ending_menu_Russian) == "ВЫЙТИ") {
                        return 0;
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                while (true) {
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    GoToXY(50, 10);
                    cout << "ВЫ ПРОИГРАЛИ";
                    GoToXY(47, 11);
                    cout << "ЗАГАДННОЕ СЛОВО: " << hidden_word;
                    if (MenuChoice(48, 12, ending_menu_Russian) == "ВЫЙТИ") {
                        return 0;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        else if (language == "ENGLISH") {
            cout << "CHOOSE GAME OPTION";
            stringstream option(MenuChoice(55, 11, menu_of_options_English));
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
            if (EnterWord(10, letters * 2 + 1, 50, 1, English_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
                while (true) {
                    GoToXY(50, 10);
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cout << "CONGRATULATIONS!";
                    GoToXY(48, 11);
                    cout << "YOU GUESSED THE WORD";
                    GoToXY(49, 12);
                    cout << "HIDDEN WORD: " << hidden_word;
                    GoToXY(49, 12);
                    if (MenuChoice(48, 13, ending_menu_English) == "EXIT") {
                        return 0;
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                while (true) {
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    GoToXY(50, 10);
                    cout << "YOU'VE LOST";
                    GoToXY(47, 11);
                    cout << "HIDDEN WORD: " << hidden_word;
                    if (MenuChoice(48, 12, ending_menu_English) == "EXIT") {
                        return 0;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
 }