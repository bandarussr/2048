#include "twenty-fourty-eight.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

// fmt Library
#define FMT_HEADER_ONLY
#include "../deps/fmt/format.h"

using namespace std;

TwentyFourtyEight::TwentyFourtyEight() {
    score = 0;
    over_flag = false;
    board.resize(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
}

// TODO: Make it so board can dynamically change size depending on number size and not look weird.
void TwentyFourtyEight::print_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "|";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << fmt::v9::format("{:^5}", board[i][j]);
            if (j != BOARD_SIZE - 1) cout << "|";
        }
        cout << "|" << endl;
    }
}

int TwentyFourtyEight::get_score() {
    return score;
}

bool TwentyFourtyEight::get_over_flag() {
    return over_flag;
}

void TwentyFourtyEight::random_placer() {
    int i, j, tile, counter;
    int rand_num[2] = {2, 4};
    bool placed = false;
    counter = 0;
    random_device rand_gen;

    while(!placed) {
        i = rand_gen() % 4;
        j = rand_gen() % 4;
        tile = rand_gen() % 2;
        if(board[i][j] == 0) {
            board[i][j] = rand_num[tile];
            counter++;
        }
        if(counter == 2) placed = true;
    }
}

bool TwentyFourtyEight::check_game_state() {
    return get_over_flag();
}

void TwentyFourtyEight::move_up() {
}

void TwentyFourtyEight::move_down() {}

void TwentyFourtyEight::move_left() {
    for(int column = BOARD_SIZE - 1; column >= 0; column--){
        for(int row = BOARD_SIZE - 1; row > 0; row--){
            if(board[column][row] == 0) continue;
            if(board[column][row] == board[column][row - 1] || board[column][row - 1] == 0){
                board[column][row - 1] += board[column][row];
                board[column][row] = 0;
                row = BOARD_SIZE;
            }
        }
    }
}

void TwentyFourtyEight::move_right() {}