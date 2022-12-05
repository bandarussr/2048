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
    board.resize(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

    // Sets up game by placing 2 tiles at random.
    random_placer();
    random_placer();
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

/*
 * searches for any two side-by-side tiles that are equal to each other on both vertical and horizontal
 * directions. If there is, then the game can still continue and returns false; else then the game cannot
 * be continued and the game ends.
 */
bool TwentyFourtyEight::check_game_state() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                random_placer();
                return false;
            };
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE - 1; j++){
            if(board[i][j] == board[i][j + 1]) {
                random_placer();
                return false;
            };
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE - 1; j++){
            if(board[j][i] == board[j + 1][i]) {
                random_placer();
                return false;
            };
        }
    }

    return true;
}

/*
 * finds a random tile that and places either and tile with the value of 2 or 4 randomly.
 */
void TwentyFourtyEight::random_placer() {
    int i, j, tile;
    int rand_num[2] = {2, 4};
    bool placed = false;
    random_device rand_gen;

    while(!placed) {
        i = rand_gen() % 4;
        j = rand_gen() % 4;
        tile = rand_gen() % 2;
        if (board[i][j] == 0) {
            board[i][j] = rand_num[tile];
            placed = true;
        }
    }
}

void TwentyFourtyEight::move_up() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int column = BOARD_SIZE - 1; column > 0; column--) {
                if (board[column][row] == 0) continue;
                if (board[column - 1][row] == 0 && board[column][row] != 0) {
                    board[column - 1][row] = board[column][row];
                    board[column][row] = 0;
                    column = BOARD_SIZE - 1;
                }
            }
        }
    }
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int column = 0; column < BOARD_SIZE - 1; column++){
            if(board[column][row] == 0) continue;
            if(board[column + 1][row] == board[column][row]){
                board[column][row] += board[column + 1][row];
                board[column + 1][row] = 0;
                score += board[column][row];
            }
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int column = BOARD_SIZE - 1; column > 0; column--) {
                if (board[column][row] == 0) continue;
                if (board[column - 1][row] == 0 && board[column][row] != 0) {
                    board[column - 1][row] = board[column][row];
                    board[column][row] = 0;
                    column = BOARD_SIZE - 1;
                }
            }
        }
    }
}

void TwentyFourtyEight::move_down() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int column = 0; column < BOARD_SIZE - 1; column++) {
                if (board[column][row] == 0) continue;
                if (board[column + 1][row] == 0 && board[column][row] != 0) {
                    board[column + 1][row] = board[column][row];
                    board[column][row] = 0;
                    column = 0;
                }
            }
        }
    }
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int column = BOARD_SIZE - 1; column > 0; column--){
            if(board[column][row] == 0) continue;
            if(board[column - 1][row] == board[column][row]){
                board[column][row] += board[column - 1][row];
                board[column - 1][row] = 0;
                score += board[column][row];
            }
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int column = 0; column < BOARD_SIZE - 1; column++) {
                if (board[column][row] == 0) continue;
                if (board[column + 1][row] == 0 && board[column][row] != 0) {
                    board[column + 1][row] = board[column][row];
                    board[column][row] = 0;
                    column = 0;
                }
            }
        }
    }
}

void TwentyFourtyEight::move_left() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int column = BOARD_SIZE - 1; column >= 0; column--) {
            for (int row = BOARD_SIZE - 1; row > 0; row--) {
                if (board[column][row] == 0) continue;
                if (board[column][row - 1] == 0 && board[column][row] != 0) {
                    board[column][row - 1] = board[column][row];
                    board[column][row] = 0;
                    row = BOARD_SIZE - 1;
                }
            }
        }
    }
    for(int column = BOARD_SIZE - 1; column >= 0; column--){
        for(int row = 0; row < BOARD_SIZE - 1; row++){
            if(board[column][row] == 0) continue;
            if(board[column][row] == board[column][row + 1]){
                board[column][row] += board[column][row + 1];
                board[column][row + 1] = 0;
                score += board[column][row];
            }
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int column = BOARD_SIZE - 1; column >= 0; column--) {
            for (int row = BOARD_SIZE - 1; row > 0; row--) {
                if (board[column][row] == 0) continue;
                if (board[column][row - 1] == 0 && board[column][row] != 0) {
                    board[column][row - 1] = board[column][row];
                    board[column][row] = 0;
                    row = BOARD_SIZE - 1;
                }
            }
        }
    }
}

void TwentyFourtyEight::move_right() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            for (int row = 0; row < BOARD_SIZE - 1; row++) {
                if (board[column][row] == 0) continue;
                if (board[column][row + 1] == 0) {
                    board[column][row + 1] = board[column][row];
                    board[column][row] = 0;
                    row = 0;
                }
            }
        }
    }

    for(int column = 0; column < BOARD_SIZE; column++) {
        for (int row = BOARD_SIZE - 1; row > 0; row --) {
            if (board[column][row] == 0) continue;
            if (board[column][row] == board[column][row - 1]) {
                board[column][row] += board[column][row - 1];
                board[column][row - 1] = 0;
                score += board[column][row];
            }
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            for (int row = 0; row < BOARD_SIZE - 1; row++) {
                if (board[column][row] == 0) continue;
                if (board[column][row + 1] == 0) {
                    board[column][row + 1] = board[column][row];
                    board[column][row] = 0;
                    row = 0;
                }
            }
        }
    }
}