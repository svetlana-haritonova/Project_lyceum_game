#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ���������� �������, ����� �������� � ���

string GetRandomWord(const string& filename); //������� ��� ��������� ���������� �����

void GoToXY(short x, short y); //����������� ������� �� ������� (x, y)

void ConsoleCursorVisible(bool show, short size); //��������� ������� �� �������

vector<vector<string>> CreateField(int height, int width); //�������� ����

void PrintField(int x, int y, vector<vector<std::string>> field, const string& hidden_word, vector<bool> check_for_paint_line); //������� ��� ��������� ���� �������� ��� ������� ���������� ����

void PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
    int& row, int& column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line);  //������� ��� ��������� ���������� + ���������� ����������� � ��������� ���� �� �������

