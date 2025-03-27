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
#include "..\Functions\Functions.h"
#include "..\Constants\Constants.h"

using std::vector;
using std::fstream;
using std::stringstream;
using std::string;
using std::cout;
using std::endl;
using std::min;
using std::srand;

string GetRandomWord(const string& filename) { //������� ��� ��������� ���������� �����
    srand(static_cast<unsigned int>(std::time(nullptr))); // ������������� ���������� ��������� �����
    fstream file;
    file.open(filename);
    string sentence, word;
    vector<string> words;
    while (std::getline(file, sentence)) { //����������� � ������ ���� ���� �� ��������� ����� �����
        stringstream text(sentence);
        while (text >> word) {
            words.push_back(word);
        }
    }
    file.close();
    int randomIndex = std::rand() % words.size(); // ��������� ���������� �������
    return words[randomIndex]; // ���������� ��������� �����
}

void GoToXY(short x, short y) { //����������� ������� �� ������� (x, y)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}

void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO struct_cursor_info; //���������� ��� ������ � �������
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //�������� ������� ������ � �������
    struct_cursor_info.bVisible = show; // �������������� ��������� �������
    struct_cursor_info.dwSize = size; // �������������� ������ �������
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &struct_cursor_info); //��������� ��������� � �������
}

void PrintMenu(int x, int y,const vector<string>& menu, int choice) {
    GoToXY(x, y);
    for (int i = 0; i < menu.size(); ++i) {
        GoToXY(x, y + i);
        if (i == choice) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLACK | BACKGROUND_WHITE);
        }
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
        cout << menu[i] << endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_BLACK);
}

string MenuChoice(int x, int y,const std::vector<string>& menu) {
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

vector<vector<string>> CreateField(int height, int width) {
    vector<vector<string>> field(height, vector<string>(width, " ")); //�������� ����
    return field;
}


void PrintField(int x, int y, const vector<vector<std::string>>& field,const string &hidden_word,const vector<bool>& check_for_paint_line) { //������� ��� ��������� ���� �������� ��� ������� ���������� ����
    int const_x = x, const_y = y;
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY);
            GoToXY(x, y);
            cout << "_______";
            ++y;
            if (check_for_paint_line[i]) {
                if (std::find(hidden_word.begin(), hidden_word.end(), field[i][j][0]) != hidden_word.end()) {
                    if (field[i][j][0] == hidden_word[j]) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) | BACKGROUND_GREEN);
                    }
                    else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) | (BACKGROUND_RED | BACKGROUND_GREEN));
                    }
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) | BACKGROUND_RED);
                }
            }
            GoToXY(x, y);
            cout << "|     |";
            ++y;
            GoToXY(x, y);
            cout << "|  " << field[i][j] << "  |";
            ++y;
            GoToXY(x, y);
            cout << "|_____|";
            x += 7;
            y = const_y;
        }
        y = y + 4;
        const_y = y;
        x = const_x;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREY);
}

void PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
    int& row, int& column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line) { //������� ��� ��������� ���������� + ���������� ����������� � ��������� ���� �� �������
    for (int i = 0; i < keyboard.size(); ++i) {
        for (int j = 0; j < keyboard[i].size(); ++j) {
            GoToXY(x + j * 3, y + i * 2); //j * 3 ����� ���� ���������� ��� ����� � ������, i * 2 ���������� ����
            if (keyboard[i][j] != " ") { //��������� ��� �� �� ������� �������
                if (i == row && j == column) { //������� ����������, ���� �� �������� �� �����-�� ����� �� �������, ������������ �
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                    cout << "[" << keyboard[i][j] << "]";
                }
                else { //��������� �������� ������ �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    cout << "[" << keyboard[i][j] << "]";
                }
            }
        }
        cout << endl;
    }
}

bool EnterWord(int pos_keyboard_x, int pos_keyboard_y, int pos_field_x, int pos_field_y,const vector<vector<string>>& keyboard, vector<vector<string>> &field,const string& hidden_word, string& entered_word, vector<bool>& check_for_painting_line) {
    int row = 0;
    int column = 0;
    int field_row = 0;
    int field_column = 0;
    int ch;
    while (true) {
        PrintField(pos_field_x, pos_field_y, field, hidden_word, check_for_painting_line);
        PrintKeyboard(pos_keyboard_x, pos_keyboard_y, keyboard, field, row, column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
        ch = _getch();
        Keyboard_Keys key = static_cast<Keyboard_Keys>(ch); // ����������� �������� ch � Keyboard_Keys

        switch (key) {
        case Keyboard_Keys::UP: //��������� ����� 
            if (row > 0 && keyboard[row][column] != " ") { //����������� ��� �� �� ����� ����� �� ������� ���������� �����
                --row;
            }
            break;
        case Keyboard_Keys::DOWN: //��������� ����
            if (row < keyboard.size() - 1) { //����������� ��� �� �� ����� ����� �� ������� ���������� ����
                ++row;
                int min = min(column, keyboard[0].size() - column); //����������� ���������, ������� � ����� ����� ���������� ���������
                //����� ����� �� �� �������� ������ �� ������� ������������ ����������(�� �������� �� ������), �.�. � ����� ������� ���������� ���� �������
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

        case Keyboard_Keys::LEFT: //��������� �����
            if (column > 0) { //����������� ��� �� �� ����� ����� �� ������� ���������� �����
                --column;
                if (keyboard[row][column] == " ") { //���������, ��� ���� �� ������ �� ������
                    ++column;
                }
            }
            break;
        case Keyboard_Keys::RIGHT: //��������� �����
            if (column < keyboard[0].size() - 1 && keyboard[row][column] != " ") { //����������� ��� �� �� ����� ����� �� ������� ���������� ������
                ++column;
                if (keyboard[row][column] == " ") { //���������, ��� ���� �� ������ �� ������
                    --column;
                }
            }
            break;
        case Keyboard_Keys::ENTER: //enter
            if (field[field_row][field_column] == " ") { //��������� ��� ������ ������
                field[field_row][field_column] = keyboard[row][column]; //��������� ����� � ����
                if (field_column != field[0].size() - 1) { //���� �� ��������� �����
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
        case Keyboard_Keys::BACKSPACE: //backspace ��� �������� ����
            if (field_column != 0) {
                if (field[field_row][field_column] == " ") { //���� �� ������ �� �� ��������� ���
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

void PrintIntrodaction() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PINK);
    GoToXY(50, 10);
    cout << "WELCOME TO YOUR GAME";
    GoToXY(50, 11);
    cout << "CHOOSE YOUR LANGUAGE";
}



void SetGameAttributes(const string& language, string& hidden_word, vector<vector<string>>& field, vector<bool>& check_for_painting_line, int& letters) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PURPLE);
    GoToXY(50, 10);
    if (language == "RUSSIAN") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PURPLE);
        cout << "�������� ����� ����";
        stringstream option(MenuChoice(56, 11, menu_of_options_Russian));
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
        if (EnterWord(10, letters * 2 + 1, 50, 1, Russian_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
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
        if (EnterWord(10, letters * 2 + 1, 50, 1, English_keyboard, field, hidden_word, entered_word, check_for_painting_line)) {
            PrintGameResult(language, true, hidden_word, ending_menu_English);
        }
        else {
            PrintGameResult(language, false, hidden_word, ending_menu_English);
        }
    }
}


void PrintGameResult(const string& language, bool win, const string& hidden_word, const vector<string>& ending_menu) {
    if (win) {
        if (language == "RUSSIAN") {
            while (true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                GoToXY(50, 10);
                cout << "�����������!";
                GoToXY(48, 11);
                cout << "�� ������� �����";
                GoToXY(47, 12);
                cout << "��������� �����: " << hidden_word;
                if (MenuChoice(48, 13, ending_menu_Russian) == "�����") {
                    exit(0);
                }
                else {
                    break;
                }
            }
        }
        else {
            while (true) {
                GoToXY(50, 10);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "CONGRATULATIONS!";
                GoToXY(48, 11);
                cout << "YOU GUESSED THE WORD";
                GoToXY(49, 12);
                cout << "HIDDEN WORD: " << hidden_word;
                GoToXY(49, 12);
                if (MenuChoice(48, 13, ending_menu_English) == "EXIT") {
                    exit(0);
                }
                else {
                    break;
                }
            }
        }
    }
    else {
        if (language == "RUSSIAN") {
            while (true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                GoToXY(50, 10);
                cout << "�� ���������";
                GoToXY(47, 11);
                cout << "��������� �����: " << hidden_word;
                if (MenuChoice(48, 12, ending_menu_Russian) == "�����") {
                    exit(0);
                }
                else {
                    break;
                }
            }
        }
        else {
            while (true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                GoToXY(50, 10);
                cout << "YOU'VE LOST";
                GoToXY(47, 11);
                cout << "HIDDEN WORD: " << hidden_word;
                if (MenuChoice(48, 12, ending_menu_English) == "EXIT") {
                    exit(0);
                }
                else {
                    break;
                }
            }
        }
    }
}