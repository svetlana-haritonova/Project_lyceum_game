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
using std::stringstream;
using std::cout;
using std::endl;
using std::min;


int main() {
    while (true) {
        SetConsoleTitle(L"LE_WORD");
        system("CLS");
        setlocale(0, "Rus");
        ConsoleCursorVisible(false, 100);


        PrintIntrodaction();


        string language = MenuChoice(56, 12, menu_of_languages);


        string entered_word;


        string hidden_word;
        vector<vector<string>> field;
        vector<bool> check_for_painting_line;
        int letters;

        SetGameAttributes(language, hidden_word, field, check_for_painting_line, letters);


    }
 }