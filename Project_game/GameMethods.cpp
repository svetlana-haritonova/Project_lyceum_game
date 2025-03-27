#include "Game.h"
#include "Constants/Constants.h"
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

using std::vector;
using std::fstream;
using std::stringstream;
using std::string;
using std::cout;
using std::endl;
using std::min;
using std::srand;

string Game::GetRandomWord(const string& filename) { //функция для генерации рандомного слова
    srand(static_cast<unsigned int>(std::time(nullptr))); // Инициализация генератора случайных чисел
    fstream file;
    file.open(filename);
    string sentence, word;
    vector<string> words;
    while (std::getline(file, sentence)) { //записывание в вектор слов пока не достигнут конец файла
        stringstream text(sentence);
        while (text >> word) {
            words.push_back(word);
        }
    }
    file.close();
    int randomIndex = std::rand() % words.size(); // Генерация случайного индекса
    return words[randomIndex]; // Возвращаем случайное слово
}

void Game::GoToXY(int x, int y) { //перемещение курсора на позицию (x, y)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(x), static_cast<short>(y) });
}

void Game::ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO struct_cursor_info; //переменная для данных о курсоре
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //получаем текущие данные о курсоре
    struct_cursor_info.bVisible = show; // редактирование видимости курсора
    struct_cursor_info.dwSize = size; // редактирование размер курсора
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //применяем изменения к курсору
}



string Game::MenuChoice(int x, int y, const std::vector<string>& menu) {
    int choice = 0;
    int ch;
    while (true) {
        PrintMenu(x, y, menu, choice);
        ch = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(ch);
        switch (key) {
        case Keyboard_Keys::ESCAPE:
            exit(0);
        case Keyboard_Keys::UP:
            if (choice > 0) {
                --choice;
            }
            break;
        case Keyboard_Keys::DOWN:
            if (choice < menu.size() - 1) {
                ++choice;
            }
            break;
        case Keyboard_Keys::ENTER:
            system("CLS");
            return menu[choice];
        default:
            break;
        }
    }
}

vector<vector<string>> Game::CreateField(int height, int width) {
    vector<vector<string>> field(height, vector<string>(width, " ")); //создание поля
    return field;
}





bool Game::EnterWord(int pos_keyboard_x, int pos_keyboard_y, int pos_field_x, int pos_field_y, const vector<vector<string>>& keyboard, vector<vector<string>>& field, const string& hidden_word, string& entered_word, vector<bool>& check_for_painting_line) {
    int row = 0;
    int column = 0;
    int field_row = 0;
    int field_column = 0;
    int ch;
    while (true) {
        PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line);
        PrintKeyboard(pos_keyboard_x, pos_keyboard_y, keyboard, field, row, column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
        ch = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(ch); // Преобразуем значение ch в Keyboard_Keys

        switch (key) {
        case Keyboard_Keys::UP: //стрелочка вверх 
            if (row > 0 && keyboard[row][column] != " ") { //ограничение что мы не можем выйти за пределы клавиатуры вверх
                --row;
            }
            break;
        case Keyboard_Keys::DOWN: //стрелочка вниз
            if (row < keyboard.size() - 1) { //ограничение что мы не можем выйти за пределы клавиатуры вниз
                ++row;
                int min = min(column, keyboard[0].size() - column); //минимальное рассояние, смотрим в каком конце клавиатуры находимся
                //нужно чтобы мы не выходили именно за пределы напечатанной клавиатуры(не попадали на пробел), т.к. в самом векторе клавиатуры есть пробелы
                if (keyboard[row][column] == " ") {
                    if (min == column) {
                        while (keyboard[row][column] == " " && column < keyboard[0].size() - 1) {
                            ++column;
                        }
                    }
                    else if (min == keyboard[0].size() - column) {
                        while (keyboard[row][column] == " " && column > 0) {
                            --column;
                        }
                    }
                }
            }
            break;

        case Keyboard_Keys::LEFT: //стрелочка влево
            if (column > 0) { //ограничение что мы не можем выйти за пределы клавиатуры влево
                --column;
                if (keyboard[row][column] == " ") { //проверяем, что если мы попали на пробел
                    ++column;
                }
            }
            break;
        case Keyboard_Keys::RIGHT: //стрелочка право
            if (column < keyboard[0].size() - 1 && keyboard[row][column] != " ") { //ограничение что мы не можем выйти за пределы клавиатуры вправо
                ++column;
                if (keyboard[row][column] == " ") { //проверяем, что если мы попали на пробел
                    --column;
                }
            }
            break;
        case Keyboard_Keys::ENTER: //enter
            if (field[field_row][field_column] == " ") { //проверяем что ячейка пустая
                field[field_row][field_column] = keyboard[row][column]; //добавляем буквы в поле
                if (field_column != field[0].size() - 1) { //если не последняя буква
                    ++field_column;
                }
            }
            else if (field[field_row][field_column] != " " && field_column == field[0].size() - 1) {
                check_for_painting_line[field_row] = true;
                entered_word = "";
                for (int i = 0; i < field[0].size(); ++i) {
                    entered_word += field[field_row][i];
                }
                if (entered_word == hidden_word) {
                    PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line);
                    system("CLS");
                    return true;
                }
                else if (field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
                    PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line);
                    system("CLS");
                    return false;
                }
                if (field_row != field.size() - 1) {
                    ++field_row;
                    field_column = 0;
                }
            }
            break;
        case Keyboard_Keys::BACKSPACE: //backspace для стирания букв
            if (field_column != 0) {
                if (field[field_row][field_column] == " ") { //если мы нажади на неё несколько раз
                    --field_column;
                    field[field_row][field_column] = " ";
                }
                else {
                    field[field_row][field_column] = " ";
                }
            }
            break;
        case Keyboard_Keys::ESCAPE: //escape
            exit(0);
        default:
            break;
        }
    }
}



void Game::SetGameAttributes(const string& language, string& hidden_word, vector<vector<string>>& field, vector<bool>& check_for_painting_line, int& letters) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PURPLE);
    GoToXY(static_cast<int>(Coordinates::STATUS_X), static_cast<int>(Coordinates::STATUS_Y));
    if (language == "RUSSIAN") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PURPLE);
        cout << "ВЫБЕРИТЕ РЕЖИМ ИГРЫ";
        stringstream option(MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y) - 1, menu_of_options_Russian));
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
        string entered_word;
        if (EnterWord(static_cast<int>(Coordinates::KEYBOARD_X), letters * 2, static_cast<int>(Coordinates::FIELD_X), static_cast<int>(Coordinates::FIELD_Y), Russian_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
            PrintGameResult(language, true, hidden_word, ending_menu_Russian);
        }
        else {
            PrintGameResult(language, false, hidden_word, ending_menu_Russian);
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
        string entered_word;
        if (EnterWord(static_cast<int>(Coordinates::KEYBOARD_X), letters * 2, static_cast<int>(Coordinates::FIELD_X), static_cast<int>(Coordinates::FIELD_Y), English_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
            PrintGameResult(language, true, hidden_word, ending_menu_English);
        }
        else {
            PrintGameResult(language, false, hidden_word, ending_menu_English);
        }
    }
}