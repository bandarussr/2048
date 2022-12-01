#include "twenty-fourty-eight.h"
#include <iostream>
using namespace std;

int main() {
    char cmd;
    TwentyFourtyEight game;

    cout << "  2048  " << endl;
    game.random_placer();
    game.print_board();

    while (cin >> cmd) {
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
        game.random_placer();
        game.print_board();

        if (game.get_over_flag() == true) {
            cout << "Game over!" << endl;
            cout << "Final Score: " << game.get_score() << endl;
            break;
        }
    }
}