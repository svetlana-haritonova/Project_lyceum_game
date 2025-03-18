#pragma once
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

//const char UP = 72; //������� �� ���������� � �� ���
//const char DOWN = 80;
//const char BACKSPACE = 8;
//const char LEFT = 75;
//const char RIGHT = 77;
//const char ENTER = 13;
//const char ESCAPE = 27;

enum class Keyboard_Keys : char { //������� �� ���������� � �� ���
    UP = 72,
    DOWN = 80,
    BACKSPACE = 8,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13,
    ESCAPE = 27,
};


const vector<vector<string>> English_keyboard = {
        {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"},
        {" ", "a", "s", "d", "f", "g", "h", "j", "k", "l"},
        {" ", " ", "z", "x", "c", "v", "b", "n", "m", " "}
};



const vector<vector<string>> Russian_keyboard = {
    {"�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�"},
    {" ", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", " "},
    {" ", " ", "�", "�", "�", "�", "�", "�", "�", "�", "�", " ", " "}
};