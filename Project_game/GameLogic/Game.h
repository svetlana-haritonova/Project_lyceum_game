#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

using std::string;
using std::vector;

class Game {
public:

	Game(); //constructor
	void Run();

private:

	//attributes

	string language;
	string entered_word;
	string hidden_word;
	vector<vector<string>> field;
	vector<bool> check_for_painting_line; //bool vector which fixsiruet when we save word
	int letters;

	//methods, private because use when only in class

	string GetRandomWord(const string& filename); //func for generate randon word

	void GoToXY(int x, int y); //move cursor to (x, y)

	void ConsoleCursorVisible(bool show, short size); //cursor`s changing

	void PrintMenu(int x, int y, const vector<string>& menu, int choice);

	string MenuChoice(int x, int y, const vector<string>& menu);

	vector<vector<string>> CreateField(int height, int width);

	void PrintField(int x, int y, const vector<vector<std::string>>& field, const string& hidden_word, const vector<bool>& check_for_paint_line);

	void PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
		int& row, int& column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line);

	bool EnterWord(int pos_keyboard_x, int pos_keyboard_y, int pos_field_x, int pos_field_y, const vector<vector<string>>& keyboard, vector<vector<string>>& field, const string& hidden_word, string& entered_word, vector<bool>& check_for_painting_line);

	void PrintIntrodaction();

	void SetGameAttributes(const string& language, string& hidden_word, vector<vector<string>>& field, vector<bool>& check_for_painting_line, int& letters);

	void PrintGameResult(const string& language, bool win, const string& hidden_word, const vector<string>& ending_menu);
};

#endif