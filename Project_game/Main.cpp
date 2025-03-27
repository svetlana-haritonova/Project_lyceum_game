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
#include "GameLogic/Game.h"
#include "Constants/Constants.h"

using std::vector;
using std::fstream;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::min;


int main() {
    Game game;
    game.Run();
    return 0;
 }