/*  twenty-fourty-eight.h
    Shashank Bandaru and Jason Choi
    Function and member declarations for the TwentyFourtyEight class.
*/
#ifndef TWENTY_FOURTY_EIGHT_H
#define TWENTY_FOURTY_EIGHT_H

#include <vector>

// Constant for the board size, allows us to change board size and have program update dynamically.
const int BOARD_SIZE = 4;

class TwentyFourtyEight {
    private:
        std::vector<std::vector<int> > board;
        std::vector<std::vector<int> > board_copy;
        int score;

    public:
        TwentyFourtyEight();

        void print_board();
        int get_score();

        void random_placer();
        bool check_game_state();
        void move_up();
        void move_down();
        void move_left();
        void move_right();
};

#endif