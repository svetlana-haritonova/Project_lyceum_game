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

string Game::GetRandomWord(const string& filename) { //func for getting random word
    srand(static_cast<unsigned int>(std::time(nullptr))); //initialization generation of random numbers
    fstream file;
    file.open(filename);
    string sentence, word;
    vector<string> words;
    while (getline(file, sentence)) { //put words from file to vector
        stringstream text(sentence);
        while (text >> word) {
            words.push_back(word);
        }
    }
    file.close();
    int randomIndex = rand() % words.size(); // generate random number in range
    return words[randomIndex]; // return random word from file
}

void Game::GoToXY(int x, int y) { //moving cursore to (x, y)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(x), static_cast<short>(y) }); //int to short because SetConsoleCursorPosition needs this type
}

void Game::ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO struct_cursor_info; //a variable for cursor data
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //get current data of cursore
    struct_cursor_info.bVisible = show; // edit cursore visibility
    struct_cursor_info.dwSize = size; // edit cursore size
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //make changes for cursor
}



string Game::MenuChoice(int x, int y, const vector<string>& menu) { //get choosing option from menu
    int choice = 0; //varaible for moving on menu
    int button; //varaible for choosing button
    while (true) {
        PrintMenu(x, y, menu, choice); //print menu while we don`t choose option
        button = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(button);
        switch (key) {
        case Keyboard_Keys::ESCAPE:
            exit(0);
        case Keyboard_Keys::UP:
            if (choice > 0) { //some boards for not to go to end of vector
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
    vector<vector<string>> field(height, vector<string>(width, " ")); //creating field
    return field;
}

bool Game::EnterWord(int pos_keyboard_x, int pos_keyboard_y, int pos_field_x, int pos_field_y, const vector<vector<string>>& keyboard, vector<vector<string>>& field, const string& hidden_word, string& entered_word, vector<bool>& check_for_painting_line) {
    int keyboard_row = 0; //variables for moving on keyboard
    int keyboard_column = 0;
    int field_row = 0; //variables for moving on field
    int field_column = 0;
    int button;
    while (true) {
        PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line);
        PrintKeyboard(pos_keyboard_x, pos_keyboard_y, keyboard, field, keyboard_row, keyboard_column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
        button = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(button); //change type of getting sign to type Keyboard_Keys
        switch (key) {
        case Keyboard_Keys::UP: //arrows up 
            if (keyboard_row > 0 && keyboard[keyboard_row][keyboard_column] != " ") { //up boards of vector and check that it isn`t whitespace
                --keyboard_row;
            }
            break;
        case Keyboard_Keys::DOWN: //arrows down
            if (keyboard_row < keyboard.size() - 1) { //down boards
                ++keyboard_row;
                int min_distance = min(keyboard_column, keyboard[0].size() - keyboard_column); //min distance, we find on which part of keyboard we are
                //using this for avoiding get to whitespace and to the end of vector
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

        case Keyboard_Keys::LEFT: //arrows left
            if (keyboard_column > 0) { //left boards
                --keyboard_column;
                if (keyboard[keyboard_row][keyboard_column] == " ") { //check if it is whitespace go back
                    ++keyboard_column;
                }
            }
            break;
        case Keyboard_Keys::RIGHT: //arrows right
            if (keyboard_column < keyboard[0].size() - 1 && keyboard[keyboard_row][keyboard_column] != " ") { //right boards
                ++keyboard_column;
                if (keyboard[keyboard_row][keyboard_column] == " ") { //check if it is whitespace go back
                    --keyboard_column;
                }
            }
            break;
        case Keyboard_Keys::ENTER: //enter
            if (field[field_row][field_column] == " ") { //check that place is free
                field[field_row][field_column] = keyboard[keyboard_row][keyboard_column]; //add letters to field
                if (field_column != field[0].size() - 1) { //if it isn`t last letter go right
                    ++field_column;
                }
            }
            else if (field[field_row][field_column] != " " && field_column == field[0].size() - 1) { //if we enter all letters in row save it
                check_for_painting_line[field_row] = true; //change row status(means that we save word)
                entered_word = "";
                for (int i = 0; i < field[0].size(); ++i) {
                    entered_word += field[field_row][i]; //collect entered word from letters
                }
                if (entered_word == hidden_word) { //if we guess the word
                    PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line); //print field again for painting the last entered word
                    system("CLS");
                    return true; //return true because we guess the word
                }
                else if (field_row == field.size() - 1 && check_for_painting_line[field_row] == true) { //if we save the last word in field and not guess the word
                    PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line); //print field again for painting the last entered word
                    system("CLS");
                    return false; //return false because we don`t guess the word
                }
                if (field_row != field.size() - 1) { //if it isn`t our last attemot go down
                    ++field_row;
                    field_column = 0;
                }
            }
            break;
        case Keyboard_Keys::BACKSPACE: //backspace for erasing letters
            if (field_column != 0) { //check that we not on first 
                if (field[field_row][field_column] == " ") { //if we press it several times go left to clean pref cell
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
        cout << "ÂÛÁÅÐÈÒÅ ÐÅÆÈÌ ÈÃÐÛ";
        stringstream option(MenuChoice(static_cast<int>(Coordinates::MENU_X), static_cast<int>(Coordinates::MENU_Y) - 1, menu_of_options_Russian));
        //get option because option is string we need to get number of letters from this option use stringstream
        option >> letters; //get letters
        vector<vector<string>> field = CreateField(letters, letters); //create field
        vector<bool> check_for_painting_line(letters, false); //create bool vector when we save word, change word`s row in this vector as true
        switch (letters) { //get hidden_word
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
        if (EnterWord(static_cast<int>(Coordinates::KEYBOARD_X), letters * 2, static_cast<int>(Coordinates::FIELD_X), static_cast<int>(Coordinates::FIELD_Y), Russian_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
            PrintGameResult(language, true, hidden_word, ending_menu_Russian); //if we guess hidden word print game result with parametr win as true
        }
        else {
            PrintGameResult(language, false, hidden_word, ending_menu_Russian); //if we don`t guess the word print game result with parametr win as false
        }
    }
    else if (language == "ENGLISH") {
        cout << "CHOOSE GAME OPTION";
        stringstream option(MenuChoice(static_cast<int>(Coordinates::MENU_X) - 1, static_cast<int>(Coordinates::MENU_Y) - 1, menu_of_options_English));
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
        if (EnterWord(static_cast<int>(Coordinates::KEYBOARD_X), letters * 2, static_cast<int>(Coordinates::FIELD_X), static_cast<int>(Coordinates::FIELD_Y), English_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
            PrintGameResult(language, true, hidden_word, ending_menu_English);
        }
        else {
            PrintGameResult(language, false, hidden_word, ending_menu_English);
        }
    }
}