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

void Solver::cleanBitmasks() {
    for (int i = 0; i < 9; i++) {
        rowStore[i] = 0;
        colStore[i] = 0;
        boxStore[i] = 0;
    }
}

void Solver::loadBitmasks(std::array<std::array<int,9>,9>& board) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
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
}

// My implementation of Leetcode 37, Sudoku Solver
bool Solver::backtrackSolve(std::array<std::array<int,9>,9>& board) {
    cleanBitmasks();
    loadBitmasks(board);
    return backtrack(board,0,0);
}

bool Solver::checkMultiSol(std::array<std::array<int,9>,9>& board, int r, int c){
    if (c == 9) {
        r++;
        c = 0;
    }
    if (r == 9) {
        if (foundOneSol)
            return true; // multiple solns found
        foundOneSol = true;
        return false; // search to see if an additional solution can be found

    }

    if (board[r][c] != 0)
        return checkMultiSol(board,r,c+1);

    int boxID = (r/3) * 3 + (c/3);
    for (int pick = 1; pick <= 9; pick++) {
        int bit = 1 << (pick - 1);
        if (validLookup(r, c, bit)) {
            board[r][c] = pick;
            rowStore[r] |= bit;
            colStore[c] |= bit;
            boxStore[boxID] |= bit;

            if (checkMultiSol(board,r,c+1))
                return true;

            board[r][c] = 0;
            rowStore[r] &= ~bit;
            colStore[c] &= ~bit;
            boxStore[boxID] &= ~bit;
        }
    }
    return false; // only one sol exists
}


bool Solver::hasUniqueSol(std::array<std::array<int,9>,9>& board) {
    foundOneSol = false;
    cleanBitmasks();
    loadBitmasks(board);
    std::array<std::array<int,9>,9> boardCopy = board;


    bool multiSol = checkMultiSol(boardCopy,0,0);
    return foundOneSol && !multiSol; // have to check that atleast one sol found incase init board invalid
}

