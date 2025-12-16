#include "board.h"
#include <stdio.h>
#include <unistd.h>

#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

void initBoard(char board[BOARD_ROWS][BOARD_COLS]) {
    for (int r = 0; r < BOARD_ROWS; r++)
        for (int c = 0; c < BOARD_COLS; c++)
            board[r][c] = '.';
}

void printBoard(char board[BOARD_ROWS][BOARD_COLS], char winner) {
    printf("\033[2J\033[H");
    int start_y = 1;
    int start_x = 1;

    for (int r = 0; r < BOARD_ROWS; r++) {
        for (int c = 0; c < BOARD_COLS; c++) {
            int y = start_y + r * CELL_HEIGHT;
            int x = start_x + c * CELL_WIDTH;
            char piece = board[r][c];
            if (winner && piece == winner) {
                printf(YELLOW);
            } else if (piece == PLAYER_PIECE) {
                printf(BLUE);
            } else if (piece == AI_PIECE) {
                printf(RED);
            } else {
                printf(CYAN);
            }
            if (piece == 'X') {
                printf("\033[%d;%dH  XX  ", y+1, x+2);
                printf("\033[%d;%dH X  X ", y+2, x+2);
                printf("\033[%d;%dH  XX  ", y+3, x+2);
            } else if (piece == 'O') {
                printf("\033[%d;%dH  OO  ", y+1, x+2);
                printf("\033[%d;%dH O  O ", y+2, x+2);
                printf("\033[%d;%dH  OO  ", y+3, x+2);
            } else {
                printf("\033[%d;%dH      ", y+1, x+2);
                printf("\033[%d;%dH      ", y+2, x+2);
                printf("\033[%d;%dH      ", y+3, x+2);
            }
            printf(RESET);
        }
    }
    int top_y = start_y;
    int left_x = start_x;
    int right_x = start_x + BOARD_COLS * CELL_WIDTH;
    for (int x = left_x; x < right_x; x++) {
        mvprintw(top_y, x, "-");
    }

    int bottom_y = start_y + BOARD_ROWS * CELL_HEIGHT;
    for (int x = left_x; x < right_x; x++) {
        mvprintw(bottom_y, x, "-");
    }

    for (int r = 0; r < BOARD_ROWS; r++) {
        int border_y = start_y + r * CELL_HEIGHT;
        for (int i = 0; i < CELL_HEIGHT; i++) {
            mvprintw(border_y + i, left_x, "|");
        }
    }

    for (int r = 0; r < BOARD_ROWS; r++) {
        int border_y = start_y + r * CELL_HEIGHT;
        for (int i = 0; i < CELL_HEIGHT; i++) {
            mvprintw(border_y + i, right_x, "|");
        }
    }

    for (int r = 0; r < BOARD_ROWS; r++) {
        int sep_y = start_y + r * CELL_HEIGHT;
        for (int c = 0; c < BOARD_COLS - 1; c++) {
            int sep_x = start_x + (c + 1) * CELL_WIDTH;
            for (int i = 0; i < CELL_HEIGHT; i++) {
                mvprintw(sep_y + i, sep_x, "|");
            }
        }
    }

    int num_y = start_y + BOARD_ROWS * CELL_HEIGHT + 1;
    for (int c = 0; c < BOARD_COLS; c++) {
        int num_x = start_x + c * CELL_WIDTH + 2;
        mvprintw(num_y, num_x, "  %d", c);
    }
    refresh();
}

void animateDrop(char board[BOARD_ROWS][BOARD_COLS], int col, char piece) {
    int row = -1;
    for (int r = BOARD_ROWS - 1; r >= 0; r--) {
        if (board[r][col] == '.') {
            row = r;
            break;
        }
    }
    if (row == -1) return;
    for (int r = 0; r <= row; r++) {
        board[r][col] = piece;
        printBoard(board, 0);
        napms(100);
        if (r < row) board[r][col] = '.';
    }
}

bool isValidMove(char board[BOARD_ROWS][BOARD_COLS], int col) {
    return col >= 0 && col < BOARD_COLS && board[0][col] == '.';
}

int makeMove(char board[BOARD_ROWS][BOARD_COLS], int col, char piece) {
    for (int r = BOARD_ROWS - 1; r >= 0; r--) {
        if (board[r][col] == '.') {
            board[r][col] = piece;
            return r;
        }
    }
    return -1;
}

void undoMove(char board[BOARD_ROWS][BOARD_COLS], int col) {
    for (int r = 0; r < BOARD_ROWS; r++) {
        if (board[r][col] != '.') {
            board[r][col] = '.';
            break;
        }
    }
}

bool checkWin(char board[BOARD_ROWS][BOARD_COLS], char p) {
    for (int r = 0; r < BOARD_ROWS; r++)
        for (int c = 0; c < BOARD_COLS - 3; c++)
            if (board[r][c] == p && board[r][c+1] == p && board[r][c+2] == p && board[r][c+3] == p)
                return true;

    for (int r = 0; r < BOARD_ROWS - 3; r++)
        for (int c = 0; c < BOARD_COLS; c++)
            if (board[r][c] == p && board[r+1][c] == p && board[r+2][c] == p && board[r+3][c] == p)
                return true;

    for (int r = 0; r < BOARD_ROWS - 3; r++)
        for (int c = 0; c < BOARD_COLS - 3; c++) {
            char window[4];
            for (int i = 0; i < 4; i++)
                window[i] = board[r+i][c+i];
            if (window[0] == p && window[1] == p && window[2] == p && window[3] == p)
                return true;
        }

    for (int r = 3; r < BOARD_ROWS; r++)
        for (int c = 0; c < BOARD_COLS - 3; c++) {
            char window[4];
            for (int i = 0; i < 4; i++)
                window[i] = board[r-i][c+i];
            if (window[0] == p && window[1] == p && window[2] == p && window[3] == p)
                return true;
        }

    return false;
}

bool isDraw(char board[BOARD_ROWS][BOARD_COLS]) {
    for (int c = 0; c < BOARD_COLS; c++)
        if (board[0][c] == '.')
            return false;
    return true;
}