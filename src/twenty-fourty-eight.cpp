#include "twenty-fourty-eight.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

// fmt Library
#define FMT_HEADER_ONLY
#include "../deps/fmt/format.h"
#include "../deps/fmt/color.h"

using namespace std;

TwentyFourtyEight::TwentyFourtyEight() {
    score = 0;
    board.resize(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

    // Sets up game by placing 2 tiles at random.
    random_placer();
    random_placer();
}

void TwentyFourtyEight::print_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "|";
        for (int j = 0; j < BOARD_SIZE; j++) {
            auto bg_color = fmt::v9::color::black;
            auto fg_color = fmt::v9::color::white;

            // Changes color based on number.
            if (board[i][j] == 0) fg_color = fmt::v9::color::black;
            else if (board[i][j] == 2) bg_color = fmt::v9::color::light_blue;
            else if (board[i][j] == 4) bg_color = fmt::v9::color::blue;
            else if (board[i][j] == 8) bg_color = fmt::v9::color::light_yellow;
            else if (board[i][j] == 16) bg_color = fmt::v9::color::yellow;
            else if (board[i][j] > 16 && board[i][j] <= 256) bg_color = fmt::v9::color::orange;
            else if (board[i][j] > 256 && board[i][j] <= 1024) bg_color = fmt::v9::color::orange_red;
            else if (board[i][j] >= 2048) bg_color = fmt::v9::color::red;

            cout << fmt::v9::format(fmt::v9::bg(bg_color) | fmt::v9::fg(fg_color), "{:^5}", board[i][j]);
            if (j != BOARD_SIZE - 1) cout << "|";
        }
        cout << "|" << endl;
    }
}

// returns score
int TwentyFourtyEight::get_score() {
    return score;
}

/*
 * first checks for any open spaces within the board then randomly places a tile in the board since an
 * open space will mean that the game is not yet finished
 *
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
 * checks the board if there is an open slot on the board where a random number can be placed
 * finds a random tile that and places either and tile with the value of 2 or 4 randomly.
 * if the tile cannot be placed then it'll finds a new tile to place it in.
 */
void TwentyFourtyEight::random_placer() {
    int i, j, tile;
    int rand_num[2] = {2, 4};
    bool placed = false;
    int placedTile = 0;
    random_device rand_gen;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j] != 0) placedTile++;
        }
    }
    if(placedTile == BOARD_SIZE*BOARD_SIZE) return;

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
/*
 * first pushes all the numbers on to one side of the board
 * then adds similar tiles that are next to each other in the horizontal or vertical replacing
 * the sum into one tile and replacing the other tile to 0
 * then pushes all the numbers on to one side of the board once again
 *
 * the sum of the tiles that are merged are also added to the total score of the game
 */
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