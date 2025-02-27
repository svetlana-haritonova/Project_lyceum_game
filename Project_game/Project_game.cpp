#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>


using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::min;

void reading_files() {

}

void start() {

}



void print_field(vector<vector<char>> field) {

}

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y) {
    SetConsoleCursorPosition(hStdOut, {x, y});
}

void create_field(int height, int width, int x, int y) {
    vector<vector<char>> field(height, vector<char>(width));
    GoToXY(x, y);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << "_______________________________";
            GoToXY(x, y);
            cout << "|     |     |     |     |     |";
            GoToXY(x, y);
            cout << "|  " << field[i][j]; "  ";
        }
        cout << "|";
    }
}


void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; // убираем видимость курсора
    structCursorInfo.dwSize = size; // редактирование размер курсора
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
            if (i == active_menu) {
                SetConsoleTextAttribute(hStdOut, 2); // зелёный цвет
            }
            else SetConsoleTextAttribute(hStdOut, 8); //серый цвет
            GoToXY(x, y++);
            cout << menu_of_languages[i] << endl;
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
       
        case 13:
            switch (active_menu)
            {
            case 0:
            case 1:
                language = menu_of_languages[active_menu];
                system("CLS");
                break;
            case 2:
                exit(0);
            }
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
                if (i == active_menu)
                    SetConsoleTextAttribute(hStdOut, 2);

                else SetConsoleTextAttribute(hStdOut,

                    FOREGROUND_GREEN);
                GoToXY(x, y++);
                cout << menu_of_options[i] << endl;
            }
            ch = _getch();

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

            case 13:
                switch (active_menu)
                {
                case 0:
                case 1:
                case 2:
                    option = menu_of_options[active_menu];
                    system("CLS");
                    break;
                case 3:
                    exit(0);
                }
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
                if (i == active_menu)
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN |
                        FOREGROUND_INTENSITY);

                else SetConsoleTextAttribute(hStdOut,

                    FOREGROUND_GREEN);
                GoToXY(x, y++);
                cout << menu_of_options[i] << endl;
            }
            ch = _getch();

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

            case 13:
                switch (active_menu)
                {
                case 0:
                case 1:
                case 2:
                    option = menu_of_options[active_menu];
                    system("CLS");
                    break;
                case 3:
                    exit(0);
                }
                break;
            }

            if (option != 0) {
                break;
            }
        }
    }

    vector<vector<string>> English_keyboard = {
        {" ", "q", "w", "e", "r", "t", " ", "y", "u", "i", "o", "p", " "},
        {" ", " ", "a", "s", "d", "f", "g", "h", "j", "k", "l", " "},
        {" ", " ", " ", "z", "x", "c", "v", "b", "n", "m", " ", " "}
    };



    vector<vector<string>> Russian_keyboard = {
        {"ё", "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х", "ъ"},
        {" ", "ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э", " "},
        {" ", " ", "я", "ч", "с", "м", "и", "т", "ь", "б", "ю", " ", " "}
    };


   

    int row = 0;
    int column = 0;
    string letter = " ";


        if (language == "RUSSIAN") {
            
            while(true) {
                    system("CLS");
                    for (int i = 0; i < Russian_keyboard.size(); ++i) {
                        for (int j = 0; j < Russian_keyboard[i].size(); ++j) {
                            GoToXY(40 + j * 3, 20 + i * 2); //j * 3 чтобы было расстояние для буквы и скобки, i * 2 опускаемся вниз
                            if (Russian_keyboard[i][j] != " ") {
                                if (i == row && j == column) {
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                                    cout << "[";
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                                    cout << Russian_keyboard[i][j];
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                                    cout << "]";
                                }
                                else {
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                                    cout << "[" << Russian_keyboard[i][j] << "]";
                                }
                            }
                            else {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                                cout << Russian_keyboard[i][j];
                            }
                        }
                        cout << endl;
                    }
                    GoToXY(0, Russian_keyboard.size() * 2 + 1);
                    //cout << "Выбрана буква: " << letter << endl;
                   // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    int ch = _getch();

                    switch (ch) {
                    case 72: // Up arrow
                        if (row > 0 && Russian_keyboard[row][column] != " ") {
                            --row;
                        }
                        break;
                    case 80: // Down arrow
                        if (row < Russian_keyboard.size() - 1) {
                            ++row;
                            int min = min(column, Russian_keyboard[0].size() - column); //минимальное рассояние; смотрим в каком конце клавиатуры находимся
                            if (Russian_keyboard[row][column] == " ") {
                                if (min == column) {
                                    while (Russian_keyboard[row][column] == " " && column < Russian_keyboard[0].size() - 1) {
                                        ++column;
                                    }
                                }
                                else if (min == Russian_keyboard[0].size() - column) {
                                    while (Russian_keyboard[row][column] == " " && column > 0) {
                                        --column;
                                    }
                                }
                            }
                        }


                        break;
                    case 75: // лево
                        if (column > 0) {
                            --column;
                            if (Russian_keyboard[row][column] == " ") {
                                ++column;
                            }
                        }
                        break;
                    case 77: // право
                        if (column < Russian_keyboard[0].size() - 1 && Russian_keyboard[row][column] != " ") {
                            ++column;
                            if (Russian_keyboard[row][column] == " ") {
                                --column;
                            }
                        }
                        break;
                    case 13: // Enter
                        //  letter =  [row][column];
                        break;
                    case 27: // Escape
                        return 0;
                    }
                }
               






            
        }
        else if (language == "ENGLISH") { 
            while (true) {
                system("CLS");
                for (int i = 0; i < English_keyboard.size(); ++i) {
                    for (int j = 0; j < English_keyboard[i].size(); ++j) {
                        GoToXY(40 + j * 3, 20 + i * 2); //j * 3 чтобы было расстояние для буквы и скобки, i * 2 опускаемся вниз
                        if (English_keyboard[i][j] != " ") {
                            if (i == row && j == column) {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                                cout << "[";
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                                cout << English_keyboard[i][j];
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                                cout << "]";
                            }
                            else {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                                cout << "[" << English_keyboard[i][j] << "]";
                            }
                        }
                        else {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                            cout << English_keyboard[i][j];
                        }
                    }
                    cout << endl;
                }
                GoToXY(0, English_keyboard.size() * 2 + 1);
                //cout << "Выбрана буква: " << letter << endl;
               // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                int ch = _getch();

                switch (ch) {
                case 72: // Up arrow
                    if (row > 0 && English_keyboard[row][column] != " ") {
                        --row;
                    }
                    break;
                case 80: // Down arrow
                    if (row < English_keyboard.size() - 1) {
                        ++row;
                        int min = min(column, English_keyboard[0].size() - column); //минимальное рассояние; смотрим в каком конце клавиатуры находимся
                        if (English_keyboard[row][column] == " ") {
                            if (min == column) {
                                while (English_keyboard[row][column] == " " && column < English_keyboard[0].size() - 1) {
                                    ++column;
                                }
                            }
                            else if (min == English_keyboard[0].size() - column) {
                                while (English_keyboard[row][column] == " " && column > 0) {
                                    --column;
                                }
                            }
                        }
                    }


                    break;
                case 75: // лево
                    if (column > 0) {
                        --column;
                        if (English_keyboard[row][column] == " ") {
                            ++column;
                        }
                    }
                    break;
                case 77: // право
                    if (column < English_keyboard[0].size() - 1 && English_keyboard[row][column] != " ") {
                        ++column;
                        if (English_keyboard[row][column] == " ") {
                            --column;
                        }
                    }
                    break;
                case 13: // Enter
                    //  letter = English_keyboard[row][column];
                    break;
                case 27: // Escape
                    return 0;
                }
            }

        }
    


    }