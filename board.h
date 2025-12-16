#ifndef BOARD_H
#define BOARD_H

#include "game.h"
#include <stdbool.h>

void initBoard(char board[BOARD_ROWS][BOARD_COLS]);
void printBoard(char board[BOARD_ROWS][BOARD_COLS], char winner);
void animateDrop(char board[BOARD_ROWS][BOARD_COLS], int col, char piece);
bool isValidMove(char board[BOARD_ROWS][BOARD_COLS], int col);
int makeMove(char board[BOARD_ROWS][BOARD_COLS], int col, char piece);
void undoMove(char board[BOARD_ROWS][BOARD_COLS], int col);
bool checkWin(char board[BOARD_ROWS][BOARD_COLS], char p);
bool isDraw(char board[BOARD_ROWS][BOARD_COLS]);

#endif