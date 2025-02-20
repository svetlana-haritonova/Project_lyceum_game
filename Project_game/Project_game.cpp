#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

void reading_files() {

}

void start() {

}

void create_field(int height, int width) {
    vector<vector<char>> field(height, vector<char>(width));
}


void print_field(vector<vector<char>> field) {

}

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y) {
    SetConsoleCursorPosition(hStdOut, {x, y});
}

void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; // изменяем видимость курсора
    structCursorInfo.dwSize = size; // изменяем размер курсора
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
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
            if (i == active_menu)
                SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN |
                    FOREGROUND_INTENSITY);

            else SetConsoleTextAttribute(hStdOut,

                FOREGROUND_GREEN);
            GoToXY(x, y++);
            cout << menu_of_languages[i] << endl;
        }
        ch = _getch();
        if (ch == -32) {
            ch = _getch(); // Отлавливаем стрелочки // -32 если мы попали на стрелочку
        }
        switch (ch) {
        case 27: //escape
            exit(0);
        case 72:
            if (active_menu > 0) {
                --active_menu;
            }
            break;
        case 80:
            if (active_menu < menu_of_languages.size() - 1) {
                ++active_menu;
            }
            break;
        case 75:
            cout << "Left, Код" << (int)ch << endl;
            break;
        case 77:
            cout << "Right, Код" << (int)ch << endl;
            break;

        case 13:
            switch (active_menu)
            {
            case 0:
            case 1:
                //system("CLS");
               // GoToXY(x, y);
               // SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                //cout << "Пользователь выбрал \"" << menu_of_languages[active_menu] << "\"";
                language = menu_of_languages[active_menu];
                //_getch();
                system("CLS");
                break;
            case 2:
                exit(0);
            }
            break;

        default:
            cout << "Код " << (int)ch << endl;
        }
        if (language != "") {
            break;
        }
    }
    
    x = 50, y = 10;
    GoToXY(x, y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    
    vector<int> menu_of_options = {5, 6, 7 };
    active_menu = 0;
    int option = 0;

    if (language == "RUSSIAN") {
        cout << "ВЫБЕРИТЕ РЕЖИМ ИГРЫ";
        while (true) {
            int x = 59, y = 11;
            GoToXY(x, y);
            for (int i = 0; i < menu_of_options.size(); ++i) {
                if (i == active_menu)
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN |
                        FOREGROUND_INTENSITY);

                else SetConsoleTextAttribute(hStdOut,

                    FOREGROUND_GREEN);
                GoToXY(x, y++);
                cout << menu_of_options[i] << endl;
            }
            ch = _getch();

            if (ch == -32) {
                ch = _getch(); // Отлавливаем стрелочки // -32 если мы попали на стрелочку
            }
            switch (ch) {
            case 27: //escape
                exit(0);
            case 72:
                if (active_menu > 0) {
                    --active_menu;
                }
                break;
            case 80:
                if (active_menu < menu_of_options.size() - 1) {
                    ++active_menu;
                }
                break;
            case 75:
                cout << "Left, Код" << (int)ch << endl;
                break;
            case 77:
                cout << "Right, Код" << (int)ch << endl;
                break;

            case 13:
                switch (active_menu)
                {
                case 0:
                case 1:
                case 2:
                    //system("CLS");
                   // GoToXY(x, y);
                   // SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    //cout << "Пользователь выбрал \"" << menu_of_languages[active_menu] << "\"";
                    option = menu_of_options[active_menu];
                    //_getch();
                    system("CLS");
                    break;
                case 3:
                    exit(0);
                }
                break;

            default:
                cout << "Код " << (int)ch << endl;
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
                if (i == active_menu)
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN |
                        FOREGROUND_INTENSITY);

                else SetConsoleTextAttribute(hStdOut,

                    FOREGROUND_GREEN);
                GoToXY(x, y++);
                cout << menu_of_options[i] << endl;
            }
            ch = _getch();

            if (ch == -32) {
                ch = _getch(); // Отлавливаем стрелочки // -32 если мы попали на стрелочку
            }
            switch (ch) {
            case 27: //escape
                exit(0);
            case 72:
                if (active_menu > 0) {
                    --active_menu;
                }
                break;
            case 80:
                if (active_menu < menu_of_options.size() - 1) {
                    ++active_menu;
                }
                break;
            case 75:
                cout << "Left, Код" << (int)ch << endl;
                break;
            case 77:
                cout << "Right, Код" << (int)ch << endl;
                break;

            case 13:
                switch (active_menu)
                {
                case 0:
                case 1:
                case 2:
                    //system("CLS");
                   // GoToXY(x, y);
                   // SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    //cout << "Пользователь выбрал \"" << menu_of_languages[active_menu] << "\"";
                    option = menu_of_options[active_menu];
                    //_getch();
                    system("CLS");
                    break;
                case 3:
                    exit(0);
                }
                break;

            default:
                cout << "Код " << (int)ch << endl;
            }
            if (option != 0) {
                break;
            }
        }
    }





        /* int height, width;
         vector<vector<char>> field(height, vector<char>(width));
         string answer;
         std::cout << "choose game language: russian/english" << std::endl << "write choosen language";
         std::cin >> answer;
         char letters;
         if (answer == "russian") {
             std::cout << "выберите режим игры: слова из 5/6/7 букв" << std::endl << "введите число";
             std::cin >> letters;
             switch (letters) {
             case '5': width = 5;
                 break;
             case '6': width = 6;
                 break;
             case '7': width = 7;
                 break;
             default:
                 std::cout << "нет такого режима, выберите другой";
             }
         }
         else if (answer == "english") {
             std::cout << "выберите режим игры: слова из 5/6/7 букв" << std::endl << "введите число";
             std::cin >> letters;
             switch (letters) {
             case '5': width = 5;
                 break;
             case '6': width = 6;
                 break;
             case '7': width = 7;
                 break;
             }
         }
         else {

         }*/
    }