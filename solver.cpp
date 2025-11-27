#include "solver.h"


Solver::Solver() {}

bool Solver::validLookup(const int r, const int c, const int bit) const {
    if (rowStore[r] & bit) {
        return false;
    }
    if (colStore[c] & bit) {
        return false;
    }
    int boxID = (r/3) * 3 + (c/3);
    if (boxStore[boxID] & bit) {
        return false;
    }
    return true;
}

bool Solver::backtrack(std::array<std::array<int,9>,9>& board, int r, int c) {
    if (c == 9) {
        r++;
        c = 0;
    }
    if (r == 9)
        return true;

    if (board[r][c] != 0)
        return backtrack(board,r,c+1);

    int boxID = (r/3) * 3 + (c/3);
    for (int pick = 1; pick <= 9; pick++) {
        int bit = 1 << (pick - 1);
        if (validLookup(r, c, bit)) {
            board[r][c] = pick;
            rowStore[r] |= bit;
            colStore[c] |= bit;
            boxStore[boxID] |= bit;

            if (backtrack(board,r,c+1))
                return true;

            board[r][c] = 0;
            rowStore[r] &= ~bit;
            colStore[c] &= ~bit;
            boxStore[boxID] &= ~bit;
        }
    }
    return false;
}

// My implementation of Leetcode 37, Sudoku Solver
void Solver::backtrackSolve(std::array<std::array<int,9>,9>& board) {
    // clean old bit masks
    for (int i = 0; i < 9; i++) {
        rowStore[i] = 0;
        colStore[i] = 0;
        boxStore[i] = 0;
    }

    int n = 9;
    // Preprocess the values
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int val = board[r][c];
            if (val == 0)
                continue;
            int bit = 1 << (val - 1);
            rowStore[r] |= bit;
            colStore[c] |= bit;
            int boxID = (r/3) * 3 + (c/3);
            boxStore[boxID] |= bit;
        }
    }
    backtrack(board,0,0);
}


