#ifndef Constants_h
#define Constants_h

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

#define STD_OUTPUT_HANDLE   ((DWORD)-11)  //constant for getting console descriptor

#define FOREGROUND_BLUE      0x0001 // text colors
#define FOREGROUND_GREEN     0x0002
#define FOREGROUND_RED       0x0004
#define FOREGROUND_INTENSITY 0x0008 // intensified text color
#define BACKGROUND_BLUE      0x0010 // background color
#define BACKGROUND_GREEN     0x0020
#define BACKGROUND_RED       0x0040
#define BACKGROUND_INTENSITY 0x0080 // intensified background color
#define FOREGROUND_BLACK       0
#define FOREGROUND_GREY        FOREGROUND_INTENSITY // mixed text and background colors 
#define FOREGROUND_PINK        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define FOREGROUND_PURPLE      FOREGROUND_RED | FOREGROUND_BLUE
#define FOREGROUND_WHITE       FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define BACKGROUND_WHITE       BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUND_PURPLE      BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUND_YELLOW      BACKGROUND_RED | BACKGROUND_GREEN
#define BACKGROUND_BLACK       0

const int CURSOR_SIZE = 100; //cursor size

enum class Coordinates : int { // coordinates game`s attributes
    STATUS_X = 50,
    STATUS_Y = 10,
    MENU_X = 56,
    MENU_Y = 12,
    FIELD_X = 50,
    FIELD_Y = 1,
    KEYBOARD_X = 10,
    KEYBOARD_Y = 10,
};

enum class Keyboard_Keys : int { //buttons on keyboard and its number
    UP = 72,
    DOWN = 80,
    BACKSPACE = 8,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13,
    ESCAPE = 27
};

enum class Letters : int { // enum of number of letters
    LETTERS_5 = 5,
    LETTERS_6 = 6,
    LETTERS_7 = 7,
};

//menu

const vector<string> menu_of_languages = { "ENGLISH", "RUSSIAN" };

const vector<string> menu_of_options_English = { "5 LETTERS", "6 LETTERS", "7 LETTERS" };

const vector<string> menu_of_options_Russian = { "5 БУКВ", "6 БУКВ", "7 БУКВ", };

const vector<string> ending_menu_Russian = { "НАЧАТЬ ЗАНОВО",  "    ВЫХОД    "};

const vector<string> ending_menu_English = { "START AGAIN",  "   EXIT    " };

//keyboards

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
