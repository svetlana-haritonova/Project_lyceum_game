#ifndef Functions_h
#define Functions_h

#include <string>
#include <vector>

using std::string;
using std::vector;

string GetRandomWord(const string& filename); //функция для генерации рандомного слова

void GoToXY(short x, short y); //перемещение курсора на позицию (x, y)

void ConsoleCursorVisible(bool show, short size); //изменение курсора на консоли

void PrintMenu(int x, int y, vector<string> menu, int choice);

string MenuChoice(int x, int y, vector<string> menu);

vector<vector<string>> CreateField(int height, int width); //создание поля

void PrintField(int x, int y, vector<vector<string>> field, const string& hidden_word, vector<bool> check_for_paint_line); //функция для отрисовки поля работает для разного количества букв

void PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
    int& row, int& column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line);  //функция для отрисовки клавиатуры + управления клавиатурой и изменения поля со словами

void AppAttempt(vector<vector<string>>& field);
#endif