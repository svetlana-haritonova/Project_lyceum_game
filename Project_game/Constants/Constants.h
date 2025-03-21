#ifndef Constants_h
#define Constants_h

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.

enum class Keyboard_Keys : char { //клавишы на клавиатуре и их код
    UP = 72,
    DOWN = 80,
    BACKSPACE = 8,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13,
    ESCAPE = 27
};

const vector<string> menu_of_languages = { "ENGLISH", "RUSSIAN" };

const vector<string> menu_of_options_English = { "5 letters", "6 letters", "7 letters", };

const vector<string> menu_of_options_Russian = { "5 букв", "6 букв", "7 букв", };

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