#include "Game.h"
#include "../Constants/Constants.h"
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
using std::getline;
using std::stringstream;
using std::string;
using std::cout;
using std::endl;
using std::min;
using std::srand;
using std::rand;
using std::time;

string Game::GetRandomWord(const string& filename) { //функция для выбора рандомного слова
    srand(static_cast<unsigned int>(time(nullptr))); //инициализация выбора рандомного числа
    fstream file;
    file.open(filename);
    string sentence, word;
    vector<string> words;
    while (getline(file, sentence)) { //вставляем слова из файла в вектор
        stringstream text(sentence);
        while (text >> word) {
            words.push_back(word);
        }
    }
    file.close();
    int randomIndex = rand() % words.size(); //генерируем рандомное число в диапазоне
    return words[randomIndex]; //возвращаем рандомное слово из файла
}

void Game::GoToXY(int x, int y) { //перемещаем курсор на (x, y)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(x), static_cast<short>(y) }); //int в short, так как для SetConsoleCursorPosition нужен данный тип
}

void Game::ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO struct_cursor_info; //переменная для данных курсора
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //получение текущих данных курсора
    struct_cursor_info.bVisible = show; //изменить видимость курсора
    struct_cursor_info.dwSize = size; //изменить размер курсора
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //сделать изменения курсора
}



string Game::MenuChoice(int x, int y, const vector<string>& menu) { //выбрать опцию в меню
    int choice = 0; //переменная для перемещения между опциями
    char button; //переменная для выбора кнопки
    while (true) {
        PrintMenu(x, y, menu, choice); //показываем меню, пока не выбрана одна опция
        button = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(button);
        switch (key) {
        case Keyboard_Keys::ESCAPE:
            exit(0);
        case Keyboard_Keys::UP:
            if (choice > 0) { //границы, чтобы не выйти за пределы вектора
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
    vector<vector<string>> field(height, vector<string>(width, " ")); //создаём поле
    return field;
}

bool Game::EnterWord(int pos_keyboard_x, int pos_keyboard_y, int pos_field_x, int pos_field_y, const vector<vector<string>>& keyboard, vector<vector<string>>& field, const string& hidden_word, string& entered_word, vector<bool>& check_for_painting_line) {
    int keyboard_row = 0; //переменные для перемещения по клавиатуре
    int keyboard_column = 0;
    int field_row = 0; //переменные для перемещения по полю
    int field_column = 0;
    char button;
    while (true) {
        PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line);
        PrintKeyboard(pos_keyboard_x, pos_keyboard_y, keyboard, field, keyboard_row, keyboard_column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
        button = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(button); //измение типа получаемого знака на тип Keyboard_Keys
        switch (key) {
        case Keyboard_Keys::UP: //стрелка вверх 
            if (keyboard_row > 0 && keyboard[keyboard_row][keyboard_column] != " ") { //поднимаем границу вектора и проверяем, что это не пробел
                --keyboard_row;
            }
            break;
        case Keyboard_Keys::DOWN: //стрелка вниз
            if (keyboard_row < keyboard.size() - 1) { //нижняя граница
                ++keyboard_row;
                int min_distance = min(keyboard_column, keyboard[0].size() - keyboard_column); //минимальная дистанция. находим, на какой части клавиатуры мы находимся
                //используем чтобы избежать перехода к пробелам и к концу вектора
                if (keyboard[keyboard_row][keyboard_column] == " ") {
                    if (min_distance == keyboard_column) {
                        while (keyboard[keyboard_row][keyboard_column] == " " && keyboard_column < keyboard[0].size() - 1) {
                            ++keyboard_column;
                        }
                    }
                    else if (min_distance == keyboard[0].size() - keyboard_column) {
                        while (keyboard[keyboard_row][keyboard_column] == " " && keyboard_column > 0) {
                            --keyboard_column;
                        }
                    }
                }
            }
            break;

        case Keyboard_Keys::LEFT: //стрелка влево
            if (keyboard_column > 0) { //левая граница
                --keyboard_column;
                if (keyboard[keyboard_row][keyboard_column] == " ") { //если пробел, то возвращаемся назад
                    ++keyboard_column;
                }
            }
            break;
        case Keyboard_Keys::RIGHT: //правая стрелка
            if (keyboard_column < keyboard[0].size() - 1 && keyboard[keyboard_row][keyboard_column] != " ") { //правая граница
                ++keyboard_column;
                if (keyboard[keyboard_row][keyboard_column] == " ") { //если пробел, то возвращаемся назад
                    --keyboard_column;
                }
            }
            break;
        case Keyboard_Keys::ENTER: //enter
            if (field[field_row][field_column] == " ") { //проверяем, что место на поле свободно
                field[field_row][field_column] = keyboard[keyboard_row][keyboard_column]; //добавляем букву в поле
                if (field_column != field[0].size() - 1) { //если это не последняя буква, идём вправо
                    ++field_column;
                }
            }
            else if (field[field_row][field_column] != " " && field_column == field[0].size() - 1) { //если добавили все буквы в ряд, то сохраняем их
                check_for_painting_line[field_row] = true; //изменяем статус ряда(сохраняем слово)
                entered_word = "";
                for (int i = 0; i < field[0].size(); ++i) {
                    entered_word += field[field_row][i]; //собираем сохранённое слова из букв
                }
                if (entered_word == hidden_word) { //если угадали слово
                    PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line); //печатаем поле еще раз, чтобы покрасить последнее введенное слово
                    system("CLS");
                    return true; //возвращаем true, так как угадали слово
                }
                else if (field_row == field.size() - 1 && check_for_painting_line[field_row] == true) { //если сохранили последнее слово в поле и не угадали слово
                    PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line); //печатаем поле еще раз, чтобы покрасить последнее введенное слово
                    system("CLS");
                    return false; //возвращаем false, так как не угадали слово
                }
                if (field_row != field.size() - 1) { //если это не последняя попытка, то спускаемся вниз
                    ++field_row;
                    field_column = 0;
                }
            }
            break;
        case Keyboard_Keys::BACKSPACE: //backspace для удаления букв
            if (field_column != 0) { //проверяем, что мы не на первой букве
                if (field[field_row][field_column] == " ") { //если нажмем несколько раз, то двигаемся влево, чтобы очистить предыдущую ячейку
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
        //поскольку параметр является строкой, то нужно получить количество букв из этого параметра, используя stringstream
        option >> letters; //получить буквы
        vector<vector<string>> field = CreateField(letters, letters); //создать поле
        vector<bool> check_for_painting_line(letters, false); //создаем вектор bool. когда сохраняем слово, изменяем строку word в этом векторе на true
        switch (letters) { //получить hidden_word
        case static_cast<int>(Letters::LETTERS_5):
            hidden_word = GetRandomWord("Dictionaries/Russian_5.txt");
            break;
        case static_cast<int>(Letters::LETTERS_6):
            hidden_word = GetRandomWord("Dictionaries/Russian_6.txt");
            break;
        case static_cast<int>(Letters::LETTERS_7):
            hidden_word = GetRandomWord("Dictionaries/Russian_7.txt");
            break;
        default:
            break;
        }
        //используем функцию enterword для отрисовки клавиатуры и поля и для угадывания слова
        if (EnterWord(static_cast<int>(Coordinates::KEYBOARD_X), static_cast<int>(Coordinates::KEYBOARD_Y), static_cast<int>(Coordinates::FIELD_X), static_cast<int>(Coordinates::FIELD_Y), Russian_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
            PrintGameResult(language, true, hidden_word, ending_menu_Russian); //если угадали слово, то выводим финальное меню с результатом, где победа == true
        }
        else {
            PrintGameResult(language, false, hidden_word, ending_menu_Russian); //если не угадали слово, то выводим финальное меню с результатом, где победа == false
        }
    }
    else if (language == "ENGLISH") {
        cout << "CHOOSE GAME OPTION";
        stringstream option(MenuChoice(static_cast<int>(Coordinates::MENU_X) - 1, static_cast<int>(Coordinates::MENU_Y) - 1, menu_of_options_English));
        option >> letters;
        vector<vector<string>> field = CreateField(letters, letters);
        vector<bool> check_for_painting_line(letters, false);
        switch (letters) {
        case static_cast<int>(Letters::LETTERS_5):
            hidden_word = GetRandomWord("Dictionaries/English_5.txt");
            break;
        case static_cast<int>(Letters::LETTERS_6):
            hidden_word = GetRandomWord("Dictionaries/English_6.txt");
            break;
        case static_cast<int>(Letters::LETTERS_7):
            hidden_word = GetRandomWord("Dictionaries/English_7.txt");
            break;
        default:
            break;
        }
        if (EnterWord(static_cast<int>(Coordinates::KEYBOARD_X), static_cast<int>(Coordinates::KEYBOARD_Y), static_cast<int>(Coordinates::FIELD_X), static_cast<int>(Coordinates::FIELD_Y), English_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
            PrintGameResult(language, true, hidden_word, ending_menu_English);
        }
        else {
            PrintGameResult(language, false, hidden_word, ending_menu_English);
        }
    }
}