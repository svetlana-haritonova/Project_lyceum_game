#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //получаем дескриптор консоли, чтобы работать с ней

string GetRandomWord(const string& filename); //функци€ дл€ генерации рандомного слова

void GoToXY(short x, short y); //перемещение курсора на позицию (x, y)

void ConsoleCursorVisible(bool show, short size); //изменение курсора на консоли

vector<vector<string>> CreateField(int height, int width); //создание пол€

void PrintField(int x, int y, vector<vector<std::string>> field, const string& hidden_word, vector<bool> check_for_paint_line); //функци€ дл€ отрисовки пол€ работает дл€ разного количества букв

void PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
    int& row, int& column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line);  //функци€ дл€ отрисовки клавиатуры + управлени€ клавиатурой и изменени€ пол€ со словами

