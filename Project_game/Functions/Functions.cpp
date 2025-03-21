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
#include "../Constants/Constants.cpp"

using std::vector;
using std::fstream;
using std::string;
using std::cout;
using std::endl;
using std::min;

string GetRandomWord(const string& filename) { //������� ��� ��������� ���������� �����
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // ������������� ���������� ��������� �����

    std::fstream file;
    file.open(filename);

    if (!file.is_open()) { // �������� �� �������� �������� �����
        cout << "Error, file is not opened." << endl;
        return ""; // ���������� ������ ������ ��� ����� ���������� ������ �����
    }

    std::string sentence, word;
    std::vector<std::string> words;

    while (std::getline(file, sentence)) { // ������ ����� �� �����
        std::stringstream text(sentence);
        while (text >> word) {
            words.push_back(word); // ���������� ���� � ������
        }
    }

    file.close();

    if (words.empty()) { // �������� �� ������ ������
        cout << "Error. File do not have words." << endl;
        return ""; // ���������� ������ ������ ��� ����� ���������� ������ �����
    }

    int randomIndex = std::rand() % words.size(); // ��������� ���������� �������
    return words[randomIndex]; // ���������� ��������� �����
}

//int randint(int range) { //������� ��� ������ ��������� ����� � ���������
//    return rand() % range;
//}
//
//string Get_Random_Word(string filename) {
//    fstream file;
//    file.open(filename);
//    string sentence, word;
//    vector<string> words;
//    while (std::getline(file, sentence)) { //����������� � ������ ���� ���� �� ��������� ����� �����
//        std::stringstream text(sentence);
//        while (text >> word) {
//            words.push_back(word);
//        }
//    }
//    file.close();
//    int i = randint(words.size() - 1); //����� ���������� ������� � ������� � ����������� ����� ��� ���� ��������
//    return words[i];
//}

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ���������� �������, ����� �������� � ���

void GoToXY(short x, short y) { //����������� ������� �� ������� (x, y)
    SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO struct_cursor_info; //���������� ��� ������ � �������
    GetConsoleCursorInfo(hStdOut, &struct_cursor_info); //�������� ������� ������ � �������
    struct_cursor_info.bVisible = show; // �������������� ��������� �������
    struct_cursor_info.dwSize = size; // �������������� ������ �������
    SetConsoleCursorInfo(hStdOut, &struct_cursor_info); //��������� ��������� � �������
}

vector<vector<string>> CreateField(int height, int width) {
    vector<vector<string>> field(height, vector<string>(width, " ")); //�������� ����
    return field;
}


void PrintField(int x, int y, vector<vector<std::string>> field, const string& hidden_word, vector<bool> check_for_paint_line) { //������� ��� ��������� ���� �������� ��� ������� ���������� ����
    int const_x = x, const_y = y;
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            GoToXY(x, y);
            cout << "_______";
            ++y;
            if (check_for_paint_line[i] == true) {
                if (std::find(hidden_word.begin(), hidden_word.end(), field[i][j][0]) != hidden_word.end()) {
                    if (field[i][j][0] == hidden_word[j]) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_GREEN);
                    }
                    else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_RED | BACKGROUND_GREEN);
                    }
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
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
            x = x + 7;
            ++y;
            y = const_y;
        }
        const_y = y + 4;
        y = const_y;
        x = const_x;
    }
}

<<<<<<< HEAD
void Print_Keyboard(int x, int y,const vector<vector<string>> keyboard, vector<vector<string>>& field,
=======
void PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
>>>>>>> c11a1c9ab0438d7883c0c73eb78d17ca057415d6
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
    int ch = _getch();
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