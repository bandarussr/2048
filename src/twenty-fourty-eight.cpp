/*  twenty-fourty-eight.cpp
    Shashank Bandaru and Jason Choi
    Implementation of the TwentyFourtyEight class, which has functions and members necessary for the game 2048.
*/
#include "twenty-fourty-eight.h"
#include <iostream>
#include <random>

// fmt Library
// Equivalent to C++ 20's <format>, not supported in all compilers yet.
#define FMT_HEADER_ONLY
#include "../deps/fmt/format.h"
#include "../deps/fmt/color.h"

using namespace std;

TwentyFourtyEight::TwentyFourtyEight() {
    score = 0;

    // Initializes board to BOARD_SIZE x BOARD_SIZE and all tiles to 0.
    board.resize(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

    // Sets up game by placing 2 tiles at random.
    random_placer();
    random_placer();
}

// Prints board dynamically based on BOARD_SIZE using Unicode box-drawing characters.
// Prints tiles with color depending on value using the fmt library.
void TwentyFourtyEight::print_board() {
    // Top half of board
    fmt::print("┌");
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (i == BOARD_SIZE - 1) fmt::print("─────┐\n");
                else fmt::print("─────┬");
            }

    for (int i = 0; i < BOARD_SIZE; i++) {
        // Rows
        fmt::print("│");
        for (int j = 0; j < BOARD_SIZE; j++) {
            auto bg_color = fmt::color::black;
            auto fg_color = fmt::color::gray;

            // Changes color based on number.
            if (board[i][j] == 0) fg_color = fmt::color::black;
            else if (board[i][j] == 2) bg_color = fmt::color::light_blue;
            else if (board[i][j] == 4) bg_color = fmt::color::blue;
            else if (board[i][j] == 8) bg_color = fmt::color::light_yellow;
            else if (board[i][j] == 16) bg_color = fmt::color::yellow;
            else if (board[i][j] > 16 && board[i][j] <= 256) bg_color = fmt::color::orange;
            else if (board[i][j] > 256 && board[i][j] <= 1024) bg_color = fmt::color::orange_red;
            else if (board[i][j] >= 2048) bg_color = fmt::color::red;

            // Sets background and foreground (text) colors for tile.
            // Prints the tile with the number centered in a 5 width space.
            fmt::print(fmt::bg(bg_color) | fmt::fg(fg_color), "{:^5}", board[i][j]);
            if (j != BOARD_SIZE - 1) fmt::print("│");
        }
        fmt::print("│\n");

        // Row separator
        if (i != BOARD_SIZE - 1) {
            fmt::print("├");
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (i == BOARD_SIZE - 1) fmt::print("─────┤\n");
                else fmt::print("─────┼");
            }
        }
    }
    
    // Bottom half of board
    fmt::print("└");
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (i == BOARD_SIZE - 1) fmt::print("─────┘\n");
                else fmt::print("─────┴");
            }
}

// Accessor for the score.
int TwentyFourtyEight::get_score() {
    return score;
}

// Checks the current game state.
// Returns TRUE if the game is over and FALSE if the game can continue.
bool TwentyFourtyEight::check_game_state() {
    // Checks for any open tiles in which the user can move or a random tile can be placed.
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) return false;
        }
    }

    // If there are no empty tiles, checks if the user can move in a direction (to combine similar tiles).
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE - 1; j++){
            if(board[i][j] == board[i][j + 1]) return false;
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE - 1; j++){
            if(board[j][i] == board[j + 1][i]) return false;
        }
    }

    return true;
}

// Randomly places a 2 or 4 tile in an empty tile.
void TwentyFourtyEight::random_placer() {
    // If the board is the same after the user attempts to move, does not place a random tile.
    if (board_copy == board) return;

    int i, j, tile;
    int rand_num[2] = {2, 4};
    bool placed = false;
    int placedTile = 0;
    random_device rand_gen;

    // Counts number of placed tiles
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j] != 0) placedTile++;
        }
    }
    // If board is full, then returns.
    if(placedTile == BOARD_SIZE*BOARD_SIZE) return;

    // Using the random_device generator, places a tile randomly.
    while(!placed) {
        i = rand_gen() % BOARD_SIZE;
        j = rand_gen() % BOARD_SIZE;
        tile = rand_gen() % 2;
        if (board[i][j] == 0) {
            board[i][j] = rand_num[tile];
            placed = true;
        }
    }
}

/* Move Functions
 * Moves all tiles to appropriate side of board.
 * Adds similar tiles that are next to each other in the appropriate direction.
 * Replaces the similar tile farther from the appropriate side with an empty tile.
 * Moves all tiles to appropriate side of board again.
 * 
 * Score is added on by the sum of the tiles that are merged.
*/
void TwentyFourtyEight::move_up() {
    board_copy = board;

    for (int i = 0; i < BOARD_SIZE; i++) {
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
    for (int row = 0; row < BOARD_SIZE; row++){
        for (int column = 0; column < BOARD_SIZE - 1; column++){
            if (board[column][row] == 0) continue;
            if (board[column + 1][row] == board[column][row]){
                board[column][row] += board[column + 1][row];
                board[column + 1][row] = 0;
                score += board[column][row];
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
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
    board_copy = board;

    for (int i = 0; i < BOARD_SIZE; i++) {
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
    for (int row = 0; row < BOARD_SIZE; row++){
        for(int column = BOARD_SIZE - 1; column > 0; column--){
            if (board[column][row] == 0) continue;
            if (board[column - 1][row] == board[column][row]){
                board[column][row] += board[column - 1][row];
                board[column - 1][row] = 0;
                score += board[column][row];
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
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
    board_copy = board;

    for (int i = 0; i < BOARD_SIZE; i++) {
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
    for (int column = BOARD_SIZE - 1; column >= 0; column--){
        for (int row = 0; row < BOARD_SIZE - 1; row++){
            if (board[column][row] == 0) continue;
            if (board[column][row] == board[column][row + 1]){
                board[column][row] += board[column][row + 1];
                board[column][row + 1] = 0;
                score += board[column][row];
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
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
    board_copy = board;

    for (int i = 0; i < BOARD_SIZE; i++) {
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

    for (int column = 0; column < BOARD_SIZE; column++) {
        for (int row = BOARD_SIZE - 1; row > 0; row --) {
            if (board[column][row] == 0) continue;
            if (board[column][row] == board[column][row - 1]) {
                board[column][row] += board[column][row - 1];
                board[column][row - 1] = 0;
                score += board[column][row];
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
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