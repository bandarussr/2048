#ifndef TWENTY_FOURTY_EIGHT_H
#define TWENTY_FOURTY_EIGHT_H

#include <vector>

const int BOARD_SIZE = 4;

class TwentyFourtyEight {
    private:
        std::vector<std::vector<int> > board;
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