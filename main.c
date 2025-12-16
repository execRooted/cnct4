#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "board.h"
#include "ai.h"

#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

int main() {
    char board[BOARD_ROWS][BOARD_COLS];
    bool gameOver = false;
    int col;

    srand(time(0));

    initBoard(board);
    printBoard(board, 0);
    gameOver = false;

    while (!gameOver) {
        printf("Choose a column (0-6): ");
        scanf("%d", &col);
        if (col < 0 || col > 6 || !isValidMove(board, col)) continue;

        animateDrop(board, col, PLAYER_PIECE);

        if (checkWin(board, PLAYER_PIECE)) {
            printBoard(board, PLAYER_PIECE);
            printf("You win!\n");
            sleep(2);
            gameOver = true;
        } else if (isDraw(board)) {
            printBoard(board, 0);
            printf("Draw!\n");
            sleep(2);
            gameOver = true;
        }

        if (gameOver) break;

        col = getAIMove(board);
        printf("AI chooses column %d\n", col);
        sleep(1);
        animateDrop(board, col, AI_PIECE);

        if (checkWin(board, AI_PIECE)) {
            printBoard(board, AI_PIECE);
            printf("AI wins!\n");
            sleep(2);
            gameOver = true;
        } else if (isDraw(board)) {
            printBoard(board, 0);
            printf("Draw!\n");
            sleep(2);
            gameOver = true;
        }
    }

    return 0;
}

