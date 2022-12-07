#include "twenty-fourty-eight.h"
#include <iostream>

// fmt Library
// Equivalent to C++ 22's <format>, not supported in all compilers yet.
#define FMT_HEADER_ONLY
#include "../deps/fmt/format.h"

// Include <conio.h> only on Windows (not supported elsewhere).
// Provides support for entering commands without pressing [ENTER].
#ifdef _WIN32
    #include <conio.h>
#else
#endif

using namespace std;

int main() {
    char cmd;
    TwentyFourtyEight game;
    
    // TODO: might move into a class function to make dynamic
    // Welcome and Controls
    cout << fmt::v9::format("{:=^25}\n", "Welcome to 2048");

    #ifdef _WIN32
        cout << "Since you are on Windows, move by pressing the move keys." << endl;
        cout << "You do not have to press [ENTER] after each move key." << endl;
    #else
        cout << "Since you are not on Windows, move by pressing the move key and then [ENTER]." << endl;
    #endif

    cout << fmt::v9::format("{:=^25}\n", "Controls");
    cout << "Use w for up, s for down, a for left, and d for right." << endl;
    cout << "Use Q to quit the game early." << endl;
    cout << fmt::v9::format("{:=^25}\n", "") << endl;

    while (true) {
        game.print_board();

        cout << "> ";

        #ifdef _WIN32
            cmd = getch();
            cout << cmd << endl;
        #else
            cin >> cmd;
        #endif

        switch (cmd) {
            case 'w':
                game.move_up();
                break;
            
            case 's':
                game.move_down();
                break;
            
            case 'a':
                game.move_left();
                break;
            
            case 'd':
                game.move_right();
                break;
            
            case 'Q':
                return 0;
            
            default:
                cout << "Use the wasd keys to move. Use Q to quit." << endl;
        }

        if (game.check_game_state()) {
            cout << "Game over!" << endl;
            cout << "Final Score: " << game.get_score() << endl;
            break;
        }

        cout << fmt::v9::format("{:=^25}\n\n", "");
    }
}