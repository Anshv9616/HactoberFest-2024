#include <iostream>

const int SIZE = 9;

// Function to check if a value can be placed at board[row][col]
bool check(int board[SIZE][SIZE], int row, int col, int val) {
    for (int k = 0; k < SIZE; k++) {
        if (board[row][k] == val || board[k][col] == val) {
            return false; // Check row and column
        }
    }

    // Check the 3x3 box
    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;
    for (int r = boxRowStart; r < boxRowStart + 3; r++) {
        for (int c = boxColStart; c < boxColStart + 3; c++) {
            if (board[r][c] == val) {
                return false;
            }
        }
    }
    
    return true;
}

// Backtracking helper function
bool solveSudoku(int board[SIZE][SIZE], int row, int col) {
    if (row == SIZE) {
        return true; // Solved
    }
    if (col == SIZE) {
        return solveSudoku(board, row + 1, 0); // Move to the next row
    }
    if (board[row][col] != 0) {
        return solveSudoku(board, row, col + 1); // Skip filled cells
    }
    
    for (int val = 1; val <= SIZE; val++) {
        if (check(board, row, col, val)) {
            board[row][col] = val; // Place value
            if (solveSudoku(board, row, col + 1)) {
                return true; // Continue solving
            }
            board[row][col] = 0; // Backtrack
        }
    }
    return false; // Trigger backtrack
}

// Main Sudoku solver function
bool sudokuSolver(int board[SIZE][SIZE]) {
    return solveSudoku(board, 0, 0);
}

// Function to print the board (for testing)
void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    int board[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (sudokuSolver(board)) {
        std::cout << "Solved Sudoku Board:" << std::endl;
        printBoard(board);
    } else {
        std::cout << "No solution exists." << std::endl;
    }

    return 0;
}