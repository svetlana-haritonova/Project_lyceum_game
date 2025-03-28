﻿#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

using std::string;
using std::vector;

class Game {
public:

	Game(); //конструктор
	void Run();

private:

	//поля

	string language;
	string entered_word;
	string hidden_word;
	vector<vector<string>> field;
	vector<bool> check_for_painting_line; //bool вектор, фиксирующий сохранение слова
	int letters;

	//метода, приватные так как используем только находясь в классе

	string GetRandomWord(const string& filename); //функция для генерации рандомного слова

	void GoToXY(int x, int y); //перемещаем курсор на (x, y)

	void ConsoleCursorVisible(bool show, short size); //изменения кусора

	void PrintMenu(int x, int y, const vector<string>& menu, int choice); //вывод меню

	string MenuChoice(int x, int y, const vector<string>& menu); //выбор опции в меню

	vector<vector<string>> CreateField(int height, int width); //создание поля

	void PrintField(int x, int y, const vector<vector<std::string>>& field, const string& hidden_word, const vector<bool>& check_for_paint_line); //отрисовка поля

	void PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
		int& row, int& column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line); //отображение клавиатуры + управление клавиатурой и изменение полей слова

	bool EnterWord(int pos_keyboard_x, int pos_keyboard_y, int pos_field_x, int pos_field_y, const vector<vector<string>>& keyboard, vector<vector<string>>& field, const string& hidden_word, string& entered_word, vector<bool>& check_for_painting_line); //перемещение по клавиатуре и перемещение по полю

	void PrintIntrodaction(); //приветственное окно

	void SetGameAttributes(const string& language, string& hidden_word, vector<vector<string>>& field, vector<bool>& check_for_painting_line, int& letters); //выбор режима игры 5/6/7 букв

	void PrintGameResult(const string& language, bool win, const string& hidden_word, const vector<string>& ending_menu); //вывод результатов игры
};

#endif