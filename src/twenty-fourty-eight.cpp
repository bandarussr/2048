#include "twenty-fourty-eight.h"
#include <iostream>

TwentyFourtyEight::TwentyFourtyEight() {
    score = 0;
    over_flag = false;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
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