#include "twenty-fourty-eight.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

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

void TwentyFourtyEight::random_placer() {
    int randI;
    int randJ;
    int randTile;
    int rand_num[2] = {2, 4};
    bool placed = false;
    while(!placed) {
        srand(time(NULL));
        randI = rand() % 4 + 1;
        randJ = rand() % 4 + 1;
        randTile = rand() % 2 + 1;
        if(board[randI][randJ] == 0){
            board[randI][randJ] = rand_num[randTile];
            placed = true;
        }
    }
}

bool TwentyFourtyEight::check_game_state() {}

void TwentyFourtyEight::move_up() {}

void TwentyFourtyEight::move_down() {}

void TwentyFourtyEight::move_left() {}

void TwentyFourtyEight::move_right() {}