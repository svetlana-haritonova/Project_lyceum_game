#ifndef Constants_h
#define Constants_h

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

#define STD_OUTPUT_HANDLE   ((DWORD)-11)

#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.
#define FOREGROUND_BLACK       0
#define FOREGROUND_GREY        FOREGROUND_INTENSITY
#define FOREGROUND_PINK        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define FOREGROUND_PURPLE        FOREGROUND_RED | FOREGROUND_BLUE
#define FOREGROUND_WHITE            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define BACKGROUND_WHITE            BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUND_PURPLE           BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUND_BLACK            0

const int CURSOR_SIZE = 100;

enum class Coordinates : int {
    STATUS_X = 50,
    STATUS_Y = 10,
    MENU_X = 56,
    MENU_Y = 12,
    FIELD_X = 50,
    FIELD_Y = 1,
    KEYBOARD_X = 10,
    KEYBOARD_Y = 1
};

enum class Keyboard_Keys : int { //клавишы на клавиатуре и их код
    UP = 72,
    DOWN = 80,
    BACKSPACE = 8,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13,
    ESCAPE = 27
};

const vector<string> menu_of_languages = { "ENGLISH", "RUSSIAN" };

const vector<string> menu_of_options_English = { "5 LETTERS", "6 LETTERS", "7 LETTERS" };

const vector<string> menu_of_options_Russian = { "5 Ѕ” ¬", "6 Ѕ” ¬", "7 Ѕ” ¬", };

const vector<string> ending_menu_Russian = { "Ќј„ј“№ «јЌќ¬ќ",  "    ¬џ…“»    "};

const vector<string> ending_menu_English = { "START AGAIN",  "   EXIT    " };

const vector<vector<string>> English_keyboard = {
        {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"},
        {" ", "a", "s", "d", "f", "g", "h", "j", "k", "l"},
        {" ", " ", "z", "x", "c", "v", "b", "n", "m", " "}
};

const vector<vector<string>> Russian_keyboard = {
    {"Є", "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х", "ъ"},
    {" ", "ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э", " "},
    {" ", " ", "€", "ч", "с", "м", "и", "т", "ь", "б", "ю", " ", " "}
};

#endif