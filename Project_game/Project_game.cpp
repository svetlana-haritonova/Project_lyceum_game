#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include <random>
#include <stdexcept>

using std::vector;
using std::fstream;
using std::string;
using std::cout;
using std::endl;
using std::min;

const char UP = 72; //клавишы на клавиатуре и их код
const char DOWN = 80;
const char BACKSPACE = 8;
const char LEFT = 75;
const char RIGHT = 77;
const char ENTER = 13;
const char ESCAPE = 27;



int randint(int range) { //функция для выбора рандомной цифры в диапазоне
    return rand() % range;
}

string get_random_word(string filename) {
    fstream file;
    file.open(filename);
    string sentence, word;
    vector<string> words;
    while (std::getline(file, sentence)) { //записывание в вектор слов пока не достигнут конец файла
        std::stringstream text(sentence);
        while (text >> word) {
            words.push_back(word);
        }
    }
    file.close();
    int i = randint(words.size() - 1); //выбор рандомного индекса в векторе и возвращения слова под этим индексом
    return words[i];
}

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //получаем дескриптор консоли, чтобы работать с ней

void GoToXY(short x, short y) { //перемещение курсора на позицию (x, y)
    SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO struct_cursor_info; //перенная для данных о курсоре
    GetConsoleCursorInfo(hStdOut, &struct_cursor_info); //получаем текущие данные о курсоре
    struct_cursor_info.bVisible = show; // редактирование видимости курсора
    struct_cursor_info.dwSize = size; // редактирование размер курсора
    SetConsoleCursorInfo(hStdOut, &struct_cursor_info); //применяем изменения к курсору
}

vector<vector<string>> create_field(int height, int width) {
    vector<vector<string>> field(height, vector<string>(width, " ")); //создание поля
    return field;
}


void print_field(int x, int y, vector<vector<std::string>> field, const string& hidden_word, vector<bool> check_for_paint_line) { //функция для отрисовки поля работает для разного количества букв
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

void print_keyboard(int x, int y, vector<vector<string>> keyboard, vector<vector<string>> &field, 
    int &row, int &column, int &field_row, int &field_column, string hidden_word, string &entered_word, vector<bool> &check_for_painting_line) { //функция для отрисовки клавиатуры + управления клавиатурой и изменения поля со словами
    for (int i = 0; i < keyboard.size(); ++i) {
        for (int j = 0; j < keyboard[i].size(); ++j) {
            GoToXY(x + j * 3, y + i * 2); //j * 3 чтобы было расстояние для буквы и скобки, i * 2 опускаемся вниз
            if (keyboard[i][j] != " ") { //проверяем что мы не выводим пробелы
                if (i == row && j == column) { //выводим клавиатуру, если мы указывем на какую-то букву на консоли, подсвечиваем её
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                    cout << "[" << keyboard[i][j] << "]";
                }
                else { //остальные просто серым печатаем
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    cout << "[" << keyboard[i][j] << "]";
                }
            }
        }
        cout << endl;
    }
    int ch = _getch();

    switch (ch) {
    case UP: //стрелочка вверх 
        if (row > 0 && keyboard[row][column] != " ") { //ограничение что мы не можем выйти за пределы клавиатуры вверх
            --row;
        }
        break;
    case DOWN: //стрелочка вниз
        if (row < keyboard.size() - 1) { //ограничение что мы не можем выйти за пределы клавиатуры вниз
            ++row;
            int min = min(column, keyboard[0].size() - column); //минимальное рассояние, смотрим в каком конце клавиатуры находимся
            //нужно чтобы мы не выходили именно за пределы напечатанной клавиатуры(не попадали на пробел), т.к. в самом векторе клавиатуры есть пробелы
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

    case LEFT: //стрелочка влево
        if (column > 0) { //ограничение что мы не можем выйти за пределы клавиатуры влево
            --column;
            if (keyboard[row][column] == " ") { //проверяем, что если мы попали на пробел
                ++column;
            }
        }
        break;
    case RIGHT: //стрелочка право
        if (column < keyboard[0].size() - 1 && keyboard[row][column] != " ") { //ограничение что мы не можем выйти за пределы клавиатуры вправо
            ++column;
            if (keyboard[row][column] == " ") { //проверяем, что если мы попали на пробел
                --column;
            }
        }
        break;
    case ENTER: //enter
        if (field[field_row][field_column] == " ") { //проверяем что ячейка пустая
            field[field_row][field_column] = keyboard[row][column]; //добавляем буквы в поле
            if (field_column != field[0].size() - 1) { //если не последняя буква
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
    case BACKSPACE: //backspace для стирания букв
        if (field_column != 0) {
            if (field[field_row][field_column] == " ") { //если мы нажади на неё несколько раз
                --field_column;
                field[field_row][field_column] = " ";
            }
            else {
                field[field_row][field_column] = " ";
            }
        }
        break;
    case ESCAPE: //escape
        exit(0);
    default:
        break;
    }
}




int main() {
    SetConsoleTitle(L"Игра в слова");
    system("CLS");
    setlocale(0, "Rus");
    ConsoleCursorVisible(false, 100);
    vector<string> menu_of_languages = { "ENGLISH", "RUSSIAN" };
    int active_menu = 0;


    int x = 50, y = 10;
    GoToXY(x, y);
    cout << "WELCOME TO YOUR GAME";
    GoToXY(x, y + 1);
    cout << "CHOOSE YOUR LANGUAGE";


    string language = "";


    char ch;
    
    while (true) {
        int x = 56, y = 12;
        GoToXY(x, y);

        for (int i = 0; i < menu_of_languages.size(); ++i) {
            if (i == active_menu) {
                SetConsoleTextAttribute(hStdOut, 2); // зелёный цвет
            }
            else SetConsoleTextAttribute(hStdOut, 8); //серый цвет
            GoToXY(x, y++);
            cout << menu_of_languages[i] << endl;
        }

        ch = _getch();
        switch (ch) {
        case ESCAPE:
            exit(0);
        case UP:
            if (active_menu > 0) {
                --active_menu;
            }
            break;
        case DOWN:
            if (active_menu < menu_of_languages.size() - 1) {
                ++active_menu;
            }
            break;
        case ENTER:
            language = menu_of_languages[active_menu];
            system("CLS");
            break;
        default:
            break;
        }
        if (language != "") {
            break;
        }
    }
    
    x = 50, y = 10;
    GoToXY(x, y);
    SetConsoleTextAttribute(hStdOut, 1); //синий
    
    vector<int> menu_of_options = {5, 6, 7 };
    active_menu = 0;
    int option = 0;

    if (language == "RUSSIAN") {
        cout << "ВЫБЕРИТЕ РЕЖИМ ИГРЫ";
        while (true) {
            x = 59, y = 11;
            GoToXY(x, y);
            for (int i = 0; i < menu_of_options.size(); ++i) {
                if (i == active_menu) {
                    SetConsoleTextAttribute(hStdOut, 2);
                }
                else SetConsoleTextAttribute(hStdOut, 8);
                GoToXY(x, y++);
                cout << menu_of_options[i] << endl;
            }
            ch = _getch();
            switch (ch) {
            case ESCAPE: //escape
                exit(0);
            case UP:
                if (active_menu > 0) {
                    --active_menu;
                }
                break;
            case DOWN:
                if (active_menu < menu_of_options.size() - 1) {
                    ++active_menu;
                }
                break;
            case ENTER:
                option = menu_of_options[active_menu];
                system("CLS");
                break;
            default:
                break;
            }
            if (option != 0) {
                break;
            }
        }
    }


    else if (language == "ENGLISH") {
        cout << "CHOOSE GAME OPTION";
        while (true) {
            int x = 59, y = 11;
            GoToXY(x, y);

            for (int i = 0; i < menu_of_options.size(); ++i) {
                if (i == active_menu) {
                    SetConsoleTextAttribute(hStdOut, 2);
                }
                else SetConsoleTextAttribute(hStdOut, 8);
                GoToXY(x, y++);
                cout << menu_of_options[i] << endl;
            }
            ch = _getch();

            switch (ch) {
            case ESCAPE: //escape
                exit(0);
            case UP:
                if (active_menu > 0) {
                    --active_menu;
                }
                break;
            case DOWN:
                if (active_menu < menu_of_options.size() - 1) {
                    ++active_menu;
                }
                break;

            case ENTER:
                option = menu_of_options[active_menu];
                system("CLS");
                break;

            default:
                break;
            }
            if (option != 0) {
                break;
            }
        }
    }

    const vector<vector<string>> English_keyboard = {
        {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"},
        {" ", "a", "s", "d", "f", "g", "h", "j", "k", "l"},
        {" ", " ", "z", "x", "c", "v", "b", "n", "m", " "}
    };



    const vector<vector<string>> Russian_keyboard = {
        {"ё", "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х", "ъ"},
        {" ", "ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э", " "},
        {" ", " ", "я", "ч", "с", "м", "и", "т", "ь", "б", "ю", " ", " "}
    };


   

    int row = 0;
    int column = 0;
    int field_row = 0;
    int field_column = 0;
    string hidden_word, entered_word;
    vector<vector<string>> field = create_field(option, option);
    vector<bool> check_for_painting_line(option, false);

    if (language == "RUSSIAN") {
        switch (option) {
        case 5:
            hidden_word = get_random_word("Russian_5.txt");
            break;
        case 6:
            hidden_word = get_random_word("Russian_6.txt");
            break;
        case 7:
            hidden_word = get_random_word("Russian_7.txt");
            break;
        default:
            break;
        }
               
        while(true) {
            print_field(50, 1, field, hidden_word, check_for_painting_line);
            if (entered_word == hidden_word || field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
                system("CLS");
                break;
            }
            print_keyboard(15, option * 2 + 1, Russian_keyboard, field, row, column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
        }
        if (entered_word == hidden_word) {
            while (true) {
                SetConsoleTextAttribute(hStdOut, 8 | 8);
                GoToXY(50, 10);
                cout << "ПОЗДРАВЛЯЕМ!";
                GoToXY(48, 11);
                cout << "ВЫ УГАДАЛИ СЛОВО";
                GoToXY(47, 12);
                cout << "ЗАГАДННОЕ СЛОВО: " << hidden_word;
            }
        }
        else if (field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
            while (true) {
                SetConsoleTextAttribute(hStdOut, 8 | 8);
                GoToXY(50, 10);
                cout << "ВЫ ПРОИГРАЛИ";
                GoToXY(47, 11);
                cout << "ЗАГАДННОЕ СЛОВО: " << hidden_word;
            }
        }
    } else if (language == "ENGLISH") {
        switch (option) {
        case 5:
            hidden_word = get_random_word("English_5.txt");
            break;
        case 6:
            hidden_word = get_random_word("English_6.txt");
            break;
        case 7:
            hidden_word = get_random_word("English_7.txt");
            break;
        default:
            break;
        }
        while (true) {
            print_field(50, 1, field, hidden_word, check_for_painting_line);
            if (entered_word == hidden_word || field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
                system("CLS");
                break;
            }
            print_keyboard(15, option * 2 + 1, English_keyboard, field, row, column, field_row, field_column, hidden_word, entered_word, check_for_painting_line);
        }
        if (entered_word == hidden_word) {
            while (true) {
                GoToXY(50, 10);
                SetConsoleTextAttribute(hStdOut, 8 | 8);
                cout << "CONGRATULATIONS!";
                GoToXY(48, 11);
                cout << "YOU GUESSED THE WORD";
                GoToXY(49, 12);
                cout << "HIDDEN WORD: " << hidden_word;
            }
        }
        else if (field_row == field.size() - 1 && check_for_painting_line[field_row] == true) {
            while (true) {
                SetConsoleTextAttribute(hStdOut, 8 | 8); //поправить фон
                GoToXY(50, 10);
                cout << "YOU LOST";
                GoToXY(47, 11);
                cout << "HIDDEN WORD: " << hidden_word;
            }
        }
    }
}