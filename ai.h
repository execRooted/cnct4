#ifndef AI_H
#define AI_H

#include "game.h"
#include <stdbool.h>

int getAIMove(char board[BOARD_ROWS][BOARD_COLS]);
int minimax(char board[BOARD_ROWS][BOARD_COLS], int depth, bool maximizingPlayer);
int scorePosition(char board[BOARD_ROWS][BOARD_COLS], char piece);
int scoreWindow(char window[4], char piece);

#endif