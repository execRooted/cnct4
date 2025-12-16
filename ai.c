#include "ai.h"
#include "board.h"
#include <limits.h>

int getAIMove(char board[BOARD_ROWS][BOARD_COLS]) {
    int bestScore = INT_MIN;
    int bestCol = 3; // default center
    for (int c = 0; c < BOARD_COLS; c++) {
        if (isValidMove(board, c)) {
            makeMove(board, c, AI_PIECE);
            int score = minimax(board, DEPTH - 1, false);
            undoMove(board, c);
            if (score > bestScore) {
                bestScore = score;
                bestCol = c;
            }
        }
    }
    return bestCol;
}

int minimax(char board[BOARD_ROWS][BOARD_COLS], int depth, bool maximizingPlayer) {
    if (checkWin(board, AI_PIECE)) return 1000;
    if (checkWin(board, PLAYER_PIECE)) return -1000;
    if (isDraw(board) || depth == 0) return scorePosition(board, AI_PIECE);

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int c = 0; c < BOARD_COLS; c++) {
            if (isValidMove(board, c)) {
                makeMove(board, c, AI_PIECE);
                int eval = minimax(board, depth - 1, false);
                undoMove(board, c);
                if (eval > maxEval) maxEval = eval;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int c = 0; c < BOARD_COLS; c++) {
            if (isValidMove(board, c)) {
                makeMove(board, c, PLAYER_PIECE);
                int eval = minimax(board, depth - 1, true);
                undoMove(board, c);
                if (eval < minEval) minEval = eval;
            }
        }
        return minEval;
    }
}

int scorePosition(char board[BOARD_ROWS][BOARD_COLS], char piece) {
    int score = 0;

    int centerCount = 0;
    for (int r = 0; r < BOARD_ROWS; r++)
        if (board[r][BOARD_COLS/2] == piece) centerCount++;
    score += centerCount * 3;

    for (int r = 0; r < BOARD_ROWS; r++)
        for (int c = 0; c < BOARD_COLS - 3; c++) {
            char window[4];
            for (int i = 0; i < 4; i++) window[i] = board[r][c+i];
            score += scoreWindow(window, piece);
        }

    for (int c = 0; c < BOARD_COLS; c++)
        for (int r = 0; r < BOARD_ROWS - 3; r++) {
            char window[4];
            for (int i = 0; i < 4; i++) window[i] = board[r+i][c];
            score += scoreWindow(window, piece);
        }

    for (int r = 0; r < BOARD_ROWS - 3; r++)
        for (int c = 0; c < BOARD_COLS - 3; c++) {
            char window[4];
            for (int i = 0; i < 4; i++) window[i] = board[r+i][c+i];
            score += scoreWindow(window, piece);
        }

    for (int r = 3; r < BOARD_ROWS; r++)
        for (int c = 0; c < BOARD_COLS - 3; c++) {
            char window[4];
            for (int i = 0; i < 4; i++) window[i] = board[r-i][c+i];
            score += scoreWindow(window, piece);
        }

    return score;
}

int scoreWindow(char window[4], char piece) {
    int score = 0;
    char opp = (piece == PLAYER_PIECE) ? AI_PIECE : PLAYER_PIECE;
    int countPiece = 0, countOpp = 0, countEmpty = 0;

    for (int i = 0; i < 4; i++) {
        if (window[i] == piece) countPiece++;
        else if (window[i] == opp) countOpp++;
        else countEmpty++;
    }

    if (countPiece == 4) score += 100;
    else if (countPiece == 3 && countEmpty == 1) score += 5;
    else if (countPiece == 2 && countEmpty == 2) score += 2;

    if (countOpp == 3 && countEmpty == 1) score -= 4;

    return score;
}