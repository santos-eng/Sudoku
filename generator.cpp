#include "generator.h"
#include <vector>
#include <algorithm>




Generator::Generator() {}

bool Generator::fillBoard(std::array<std::array<int,9>,9>& board, int r, int c,
                          Solver& s,std::mt19937& randomGen) {
    if (c == 9) {
        r++;
        c = 0;
    }
    if (r == 9)
        return true;

    if (board[r][c] != 0)
        return fillBoard(board,r,c+1,s,randomGen);

    std::vector<int> nums = {1,2,3,4,5,6,7,8,9};
    std::shuffle(nums.begin(),nums.end(),randomGen);

    int boxID = (r/3) * 3 + (c/3);

    for (int pick : nums) {
        int bit = 1 << (pick - 1);
        if (s.validLookup(r, c, bit)) {
            board[r][c] = pick;
            s.rowStore[r] |= bit;
            s.colStore[c] |= bit;
            s.boxStore[boxID] |= bit;

            if (fillBoard(board,r,c+1,s,randomGen))
                return true;

            board[r][c] = 0;
            s.rowStore[r] &= ~bit;
            s.colStore[c] &= ~bit;
            s.boxStore[boxID] &= ~bit;
        }
    }

    return false; // when branch of current generating sol cannot create a valid sol
}

void Generator::generateUnique(std::array<std::array<int,9>,9>& board,
                               std::array<std::array<bool,9>,9>& fixed, int minClues) {
    Solver s;
    s.cleanBitmasks();

    static std::random_device seed; // sourced from the OS aims for non-determinism
    static std::mt19937 randomGen(seed()); // seed() advances the state that random device uses

    fillBoard(board,0,0,s,randomGen);

    std::vector<int> removalOrder(81);
    for (int i = 0; i < 81; i++)
        removalOrder[i] = i;
    std::shuffle(removalOrder.begin(),removalOrder.end(),randomGen);

    int remainingClues = 81;

    for (int idx : removalOrder) {
        if (remainingClues <= minClues)
            break;

        int r = idx / 9;
        int c = idx % 9;
        int backupVal = board[r][c];

        board[r][c] = 0;
        s.cleanBitmasks();
        s.loadBitmasks(board); // reloaded without the removed value

        if (!s.hasUniqueSol(board))
            board[r][c] = backupVal; // reload the value and retry with another;
        else
            remainingClues--;
    }
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            fixed[r][c] = (board[r][c] != 0);
}

