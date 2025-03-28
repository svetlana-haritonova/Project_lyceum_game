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

string Game::GetRandomWord(const string& filename) { //функция получение рандомного слова из файла
    srand(static_cast<unsigned int>(time(nullptr))); //инициализация генератора рандомного числа
    fstream file;
    file.open(filename);
    string sentence, word;
    vector<string> words;
    while (getline(file, sentence)) { //добавляем слова из файла в вектор
        stringstream text(sentence);
        while (text >> word) {
            words.push_back(word);
        }
    }
    file.close();
    int randomIndex = rand() % words.size(); //генерируем рандомное число в диапазоне
    return words[randomIndex]; //возвращаем слов под данным индексом
}

void Game::GoToXY(int x, int y) { //перермещение курсора на позицию (x, y)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(x), static_cast<short>(y) }); //переводим int в short потому что SetConsoleCursorPosition использует этот тип данных
}

void Game::ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO struct_cursor_info; //данные о курсоре
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //получаем текущие данные о курсоре
    struct_cursor_info.bVisible = show; //редактируем видимость курсора
    struct_cursor_info.dwSize = size; //редактируем размер курсора
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //применяем изменения к курсору
}



string Game::MenuChoice(int x, int y, const vector<string>& menu) { //функция для получения выбранной опции из меню
    int choice = 0; //переменная отвечающая за движения по меню
    char button; //переменная для получения символа с консоли
    while (true) {
        PrintMenu(x, y, menu, choice); //рисуем меню пока мы не выбрали опцию
        button = _getch(); //считываем символ с консоли
        Keyboard_Keys key = static_cast<Keyboard_Keys>(button); //переводим полученное значения в тип данных Keyboard_Keys(enum)
        switch (key) {
        case Keyboard_Keys::ESCAPE:
            exit(0);
        case Keyboard_Keys::UP:
            if (choice > 0) { //ограничения чтобы не выходить за границы вектора
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
            return menu[choice]; //если нажали enter возвращаем выбранную опцию 
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
    int keyboard_row = 0; //переменные отвечающие за перемещение по клавиатуре
    int keyboard_column = 0;
    int field_row = 0; //переменные отвечающие за перемещение по полю
    int field_column = 0;
    char button;
    while (true) {
        PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line); //отрисовываем поле
        PrintKeyboard(pos_keyboard_x, pos_keyboard_y, keyboard, field, keyboard_row, keyboard_column, field_row, field_column, hidden_word, entered_word, check_for_painting_line); //отрисовываем клавиатуру
        button = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(button); //переводим полученный символ в тип данных Keyboard_Keys(enum)
        switch (key) {
        case Keyboard_Keys::UP: //стрелочки вверх
            if (keyboard_row > 0 && keyboard[keyboard_row][keyboard_column] != " ") { //верхние границы вектора и проверяем что это не пробел на клавиатуре
                --keyboard_row;
            }
            break;
        case Keyboard_Keys::DOWN: //стрелочки вниз
            if (keyboard_row < keyboard.size() - 1) { //нижние границы
                ++keyboard_row;
                int min_distance = min(keyboard_column, keyboard[0].size() - keyboard_column); //минимальная дистанция. находим, на какой части клавиатуры мы находимся (правой или левой)
                //используем чтобы избежать перехода к пробелам в векторе, также проверяем что мы не выходим за край вектора
                if (keyboard[keyboard_row][keyboard_column] == " ") { //если мы ближе к правой границе
                    if (min_distance == keyboard_column) {
                        while (keyboard[keyboard_row][keyboard_column] == " " && keyboard_column < keyboard[0].size() - 1) {
                            ++keyboard_column;
                        }
                    }
                    else if (min_distance == keyboard[0].size() - keyboard_column) { //если мы ближе к правой границу
                        while (keyboard[keyboard_row][keyboard_column] == " " && keyboard_column > 0) {
                            --keyboard_column;
                        }
                    }
                }
            }
            break;

        case Keyboard_Keys::LEFT: //стрелочки влево
            if (keyboard_column > 0) { //левая граница
                --keyboard_column;
                if (keyboard[keyboard_row][keyboard_column] == " ") { //если мы наткнулись на пробел возвращаемя обратно
                    ++keyboard_column;
                }
            }
            break;
        case Keyboard_Keys::RIGHT: //стрелочки вправо
            if (keyboard_column < keyboard[0].size() - 1 && keyboard[keyboard_row][keyboard_column] != " ") { 
                //правая граница, так же проверяем что мы находимся не на пробеле
                ++keyboard_column;
                if (keyboard[keyboard_row][keyboard_column] == " ") { //если мы попали на пробел возвращаемся обратно
                    --keyboard_column;
                }
            }
            break;
        case Keyboard_Keys::ENTER: //enter
            if (field[field_row][field_column] == " ") { //проверяем что ячейка свободная
                field[field_row][field_column] = keyboard[keyboard_row][keyboard_column]; //добавляем в поле выбранную букву
                if (field_column != field[0].size() - 1) { //если это не последняя буква в строке сдвигаемся вправо
                    ++field_column;
                }
            }
            else if (field[field_row][field_column] != " " && field_column == field[0].size() - 1) { //если мы ввели все буквы в строке
                check_for_painting_line[field_row] = true; //сохраняем слово (изменяя статус строки)
                entered_word = "";
                for (int i = 0; i < field[0].size(); ++i) {
                    entered_word += field[field_row][i]; //собираем введенное слво по буквам
                }
                if (entered_word == hidden_word) { //если мы угадали слово
                    PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line); //снова печатаем поле чтобы окрасилась последняя введенная строка
                    system("CLS");
                    return true; //возвращаем true потому что мы угадали слово
                }
                else if (field_row == field.size() - 1 && check_for_painting_line[field_row] == true) { //если мы не угадали слово и дошли до конца поля
                    PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line); //снова печатаем поле чтобы окрасилась последняя введенная строка
                    system("CLS");
                    return false; //возвращаем false потому что мы не угадали слово
                }
                if (field_row != field.size() - 1) { //если это не последняя наша попытка опускаемся вниз
                    ++field_row;
                    field_column = 0;
                }
            }
            break;
        case Keyboard_Keys::BACKSPACE: //backspace для стирание букв
            if (field_column != 0) { //проверяем что мы не стираем первую букву в строке (если field_column == 0, это означает что ячейка и так пустая)
                if (field[field_row][field_column] == " ") { //если мы стерли одну букву и хотим ещё стереть буквы
                    --field_column;
                    field[field_row][field_column] = " ";
                }
                else {
                    field[field_row][field_column] = " "; //если нет просто стираем одну букву
                }
            }
            break;
        case Keyboard_Keys::ESCAPE: //escape
            exit(0); //выход из программы
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
        option >> letters; //получаем количество букв
        vector<vector<string>> field = CreateField(letters, letters); //создаем поле
        vector<bool> check_for_painting_line(letters, false); //создаем вектор bool когда сохраняем слово, изменяем строку слова в этом векторе на true
        switch (letters) { //получаем загаданное слово
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
            PrintGameResult(language, true, hidden_word, ending_menu_Russian); //если угадали слово, то выводим финальное меню с результатом, где переменная win == true
        }
        else {
            PrintGameResult(language, false, hidden_word, ending_menu_Russian); //если не угадали слово, то выводим финальное меню с результатом, где переменная win == false
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