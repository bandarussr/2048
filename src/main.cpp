/*  main.cpp
    Shashank Bandaru and Jason Choi
    Driver code for the game.
*/
#include "twenty-fourty-eight.h"
#include <iostream>

// fmt Library
// Equivalent to C++ 20's <format>, not supported in all compilers yet.
#define FMT_HEADER_ONLY
#include "../deps/fmt/format.h"
#include "../deps/fmt/color.h"

// Include <conio.h> only on Windows (since it's Windows only).
// Provides support for entering commands without pressing [ENTER].
#ifdef _WIN32
    #include <conio.h>
#else
#endif

using namespace std;

int main() {
    char cmd;
    TwentyFourtyEight game;
    
    // Welcome and Information
    fmt::print("{:=^25}\n", "Welcome to 2048");

    // Notifies user of OS-specific controls.
    #ifdef _WIN32
        fmt::print("Since you are on Windows, move by pressing the move keys.\n");
        fmt::print("You do not have to press [ENTER] after each move key.\n");
    #else
        fmt::print("Since you are not on Windows, move by pressing the move key and then [ENTER].\n");
    #endif
    
    // Information about controls
    fmt::print("{:=^25}\n", "Controls");
    fmt::print("Use w for up, s for down, a for left, and d for right.\n");
    fmt::print("Use Q to quit the game early.\n");
    fmt::print("{:=^25}\n", "");

    // Main game loop
    while (true) {
        game.print_board();

        // Checks if the game is over (true) and prints score.
        if (game.check_game_state()) {
            fmt::print("Game over!\n");
            fmt::print("Final Score: {}\n", fmt::group_digits(game.get_score())); // Formats score using the thousand's sign (,).
            break;
        }

        fmt::print("> ");

        // If on windows, allows user to enter move commands without pressing enter.
        // If on a different OS, user has to enter commands and press enter.
        #ifdef _WIN32
            cmd = getch();
            fmt::print("{}", cmd);
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
                // Error message if the user inputs invalid command.
                fmt::print("{:=^25}\n\n", "");
                fmt::print(fmt::fg(fmt::color::red), "Use the wasd keys to move. Use Q to quit.\n");
                continue;
        }
        
        // Places a random tile (if allowed) at end of move.
        game.random_placer();
        fmt::print("{:=^25}\n\n", "");
    }
}