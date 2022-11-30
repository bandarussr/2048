#include "twenty-fourty-eight.h"
#include <iostream>
#include <vector>

using namespace std;

TwentyFourtyEight::TwentyFourtyEight() {
    //resize board to 4x4
    score = 0;
    over_flag = false;
}

void TwentyFourtyEight::print_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << '|';
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j];
        }
        std::cout << '|' << std::endl;
    }
}

int TwentyFourtyEight::get_score() {
    return score;
}

bool TwentyFourtyEight::get_over_flag() {
    return over_flag;
}

void TwentyFourtyEight::random_placer() {}

bool TwentyFourtyEight::check_game_state() {}

void TwentyFourtyEight::move_up() {}

void TwentyFourtyEight::move_down() {}

void TwentyFourtyEight::move_left() {}

void TwentyFourtyEight::move_right() {}