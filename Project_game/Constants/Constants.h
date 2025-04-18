﻿#ifndef Constants_h
#define Constants_h

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

#define STD_OUTPUT_HANDLE   ((DWORD)-11)  //коснтанта для получения дескриптора консоли

#define FOREGROUND_BLUE      0x0001 // цвета текста
#define FOREGROUND_GREEN     0x0002
#define FOREGROUND_RED       0x0004
#define FOREGROUND_INTENSITY 0x0008 // делает цвет текста ярче
#define BACKGROUND_BLUE      0x0010 // цвета фона
#define BACKGROUND_GREEN     0x0020
#define BACKGROUND_RED       0x0040
#define BACKGROUND_INTENSITY 0x0080 // делает цвет фона ярче
#define FOREGROUND_BLACK       0
#define FOREGROUND_GREY        FOREGROUND_INTENSITY // смешанные цвета фона и текста
#define FOREGROUND_PINK        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define FOREGROUND_PURPLE      FOREGROUND_RED | FOREGROUND_BLUE
#define FOREGROUND_WHITE       FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define BACKGROUND_WHITE       BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUND_PURPLE      BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUND_YELLOW      BACKGROUND_RED | BACKGROUND_GREEN
#define BACKGROUND_BLACK       0

const int CURSOR_SIZE = 100; //размер курсора

enum class Coordinates : int { //координаты элементов игры
    STATUS_X = 50,
    STATUS_Y = 10,
    MENU_X = 56,
    MENU_Y = 12,
    FIELD_X = 50,
    FIELD_Y = 1,
    KEYBOARD_X = 10,
    KEYBOARD_Y = 10,
};

enum class Keyboard_Keys : int { //клавиши на клавиатуре и их код
    UP = 72,
    DOWN = 80,
    BACKSPACE = 8,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13,
    ESCAPE = 27
};

enum class Letters : int { //количество букв
    LETTERS_5 = 5,
    LETTERS_6 = 6,
    LETTERS_7 = 7,
};

//меню

const vector<string> menu_of_languages = { "ENGLISH", "RUSSIAN" };

const vector<string> menu_of_options_English = { "5 LETTERS", "6 LETTERS", "7 LETTERS" };

const vector<string> menu_of_options_Russian = { "5 БУКВ", "6 БУКВ", "7 БУКВ", };

const vector<string> ending_menu_Russian = { "НАЧАТЬ ЗАНОВО",  "    ВЫХОД    "};

const vector<string> ending_menu_English = { "START AGAIN",  "   EXIT    " };

//клавиатуры
//пробелы в векторе клавиатур для симметричности, обе клавиатуры в string потому что у русского пробема с char...

const vector<vector<string>> English_keyboard = {
        {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"},
        {" ", "a", "s", "d", "f", "g", "h", "j", "k", "l"},
        {" ", " ", "z", "x", "c", "v", "b", "n", "m", " "}
};

const vector<vector<string>> Russian_keyboard = {
    {"ё", "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х", "ъ"},
    {" ", "ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э", " "},
    {" ", " ", "я", "ч", "с", "м", "и", "т", "ь", "б", "ю", " ", " "}
};

#endif
