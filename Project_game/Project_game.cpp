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
#include "Constants/Constants.h"
#include "Functions/Functions.h"

using std::vector;
using std::fstream;
using std::string;
using std::cout;
using std::endl;
using std::min;


int main() {
    SetConsoleTitle(L"Игра в слова");
    system("CLS");
    setlocale(0, "Rus");
    ConsoleCursorVisible(false, 100);
    vector<string> menu_of_languages = { "ENGLISH", "RUSSIAN" };
    int active_menu = 0;


    int x = 50, y = 10;
    GoToXY(x, y);
    cout << "WELCOME TO YOUR GAME";
    GoToXY(x, y + 1);
    cout << "CHOOSE YOUR LANGUAGE";


    string language = "";


    char ch;
    
    while (true) {
        int x = 56, y = 12;
        GoToXY(x, y);

        for (int i = 0; i < menu_of_languages.size(); ++i) {
            if (i == active_menu) {
                SetConsoleTextAttribute(hStdOut, 2); // зелёный цвет
            }
            else SetConsoleTextAttribute(hStdOut, 8); //серый цвет
            GoToXY(x, y++);
            cout << menu_of_languages[i] << endl;
        }

        ch = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(ch);
        switch (key) {
        case Keyboard_Keys::ESCAPE:
            exit(0);
        case Keyboard_Keys::UP:
            if (active_menu > 0) {
                --active_menu;
            }
            break;
        case Keyboard_Keys::DOWN:
            if (active_menu < menu_of_languages.size() - 1) {
                ++active_menu;
            }
            break;
        case Keyboard_Keys::ENTER:
            language = menu_of_languages[active_menu];
            system("CLS");
            break;
        default:
            break;
        }
        if (language != "") {
            break;
        }
    }
    
    x = 50, y = 10;
    GoToXY(x, y);
    SetConsoleTextAttribute(hStdOut, 1); //синий
    
    vector<int> menu_of_options = {5, 6, 7 };
    active_menu = 0;
    int option = 0;

    if (language == "RUSSIAN") {
        cout << "ВЫБЕРИТЕ РЕЖИМ ИГРЫ";
        while (true) {
            x = 59, y = 11;
            GoToXY(x, y);
            for (int i = 0; i < menu_of_options.size(); ++i) {
                if (i == active_menu) {
                    SetConsoleTextAttribute(hStdOut, 2);
                }
                else SetConsoleTextAttribute(hStdOut, 8);
                GoToXY(x, y++);
                cout << menu_of_options[i] << endl;
            }
            ch = _getch();
            Keyboard_Keys key = static_cast<Keyboard_Keys>(ch);
            switch (key) {
            case Keyboard_Keys::ESCAPE: //escape
                exit(0);
            case Keyboard_Keys::UP:
                if (active_menu > 0) {
                    --active_menu;
                }
                break;
            case Keyboard_Keys::DOWN:
                if (active_menu < menu_of_options.size() - 1) {
                    ++active_menu;
                }
                break;
            case Keyboard_Keys::ENTER:
                option = menu_of_options[active_menu];
                system("CLS");
                break;
            default:
                break;
            }
            if (option != 0) {
                break;
            }
        }
    }


    else if (language == "ENGLISH") {
        cout << "CHOOSE GAME OPTION";
        while (true) {
            int x = 59, y = 11;
            GoToXY(x, y);

            for (int i = 0; i < menu_of_options.size(); ++i) {
                if (i == active_menu) {
                    SetConsoleTextAttribute(hStdOut, 2);
                }
                else SetConsoleTextAttribute(hStdOut, 8);
                GoToXY(x, y++);
                cout << menu_of_options[i] << endl;
            }
            ch = _getch();
            Keyboard_Keys key = static_cast<Keyboard_Keys>(ch);
            switch (key) {
            case Keyboard_Keys::ESCAPE: //выход
                exit(0);
            case Keyboard_Keys::UP:
                if (active_menu > 0) {
                    --active_menu;
                }
                break;
            case Keyboard_Keys::DOWN:
                if (active_menu < menu_of_options.size() - 1) {
                    ++active_menu;
                }
                break;

            case Keyboard_Keys::ENTER:
                option = menu_of_options[active_menu];
                system("CLS");
                break;

            default:
                break;
            }
            if (option != 0) {
                break;
            }
        }
    }


    int row = 0;
    int column = 0;
    int field_row = 0;
    int field_column = 0;
    string hidden_word, entered_word;
    vector<vector<string>> field = CreateField(option, option);
    vector<bool> check_for_painting_line(option, false);

    if (language == "RUSSIAN") {
        switch (option) {
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
               
        while(true) {
            PrintField(50, 1, field, hidden_word, check_for_painting_line);
            if (entered_word == hidden_word || field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
                system("CLS");
                break;
            }
            PrintKeyboard(15, option * 2 + 1, Russian_keyboard, field, row, column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
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
        switch (option) {
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
                system("CLS");
                break;
            }
            PrintKeyboard(15, option * 2 + 1, English_keyboard, field, row, column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
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