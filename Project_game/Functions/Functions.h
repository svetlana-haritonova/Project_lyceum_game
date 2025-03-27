#ifndef Functions_h
#define Functions_h

using std::string;
using std::vector;

string GetRandomWord(const string& filename); //функция для генерации рандомного слова

void GoToXY(short x, short y); //перемещение курсора на позицию (x, y)

void ConsoleCursorVisible(bool show, short size); //изменение курсора на консоли

void PrintMenu(int x, int y, const vector<string>& menu, int choice);

string MenuChoice(int x, int y,const vector<string>& menu);

vector<vector<string>> CreateField(int height, int width); //создание поля

void PrintField(int x, int y, const vector<vector<std::string>>& field, const string& hidden_word, const vector<bool>& check_for_paint_line); //функция для отрисовки поля работает для разного количества букв

void PrintKeyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>>& field,
    int& row, int& column, int& field_row, int& field_column, string hidden_word, string& entered_word, vector<bool>& check_for_painting_line);  //функция для отрисовки клавиатуры + управления клавиатурой и изменения поля со словами

bool EnterWord(int pos_keyboard_x, int pos_keyboard_y, int pos_field_x, int pos_field_y, const vector<vector<string>>& keyboard, vector<vector<string>>& field, const string& hidden_word, string& entered_word, vector<bool>& check_for_painting_line);

void PrintIntrodaction();

void SetGameAttributes(const string& language, string& hidden_word, vector<vector<string>>& field, vector<bool>& check_for_painting_line, int& letters);

void PrintGameResult(const string& language, bool win, const string& hidden_word, const vector<string>& ending_menu);
#endif