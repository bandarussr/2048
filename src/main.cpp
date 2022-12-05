#include "twenty-fourty-eight.h"
#include <iostream>

// fmt Library
#define FMT_HEADER_ONLY
#include "../deps/fmt/format.h"

using namespace std;

int main() {
    char cmd;
    TwentyFourtyEight game;
    cout << fmt::v9::format("{:^25}\n", 2048);

    while (true) {
        game.print_board();

        cin >> cmd;
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
            
            case 'q':
                return 0;
            
            default:
                cout << "Use the wasd keys to move. Use q to quit." << endl;
        }

        if (game.check_game_state()) {
            cout << "Game over!" << endl;
            cout << "Final Score: " << game.get_score() << endl;
            break;
        }
    }
}