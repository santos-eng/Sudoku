#include "validator.h"
#include <unordered_set>

Validator::Validator() {}

// See LEETCODE 271, Valid Sudoku
Validator::State Validator::isValid(const std::array<std::array<int,9>,9>& board, std::array<bool,9>& invalRow,
                        std::array<bool,9>& invalCol, std::array<bool,9>& invalBox) {
    int n = 9;
    invalRow.fill(false);
    invalCol.fill(false);
    invalBox.fill(false);
    Validator::State state = State::Incomplete;
    std::unordered_set<int> rowSet[9];
    std::unordered_set<int> colSet[9];
    std::unordered_set<int> boxSet[9];

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int val = board[r][c];
            if (!val)
                continue;

            if (!rowSet[r].insert(val).second) {
                state = State::Invalid;
                invalRow[r] = true;
            }
            if (!colSet[c].insert(val).second) {
                state = State::Invalid;
                invalCol[c] = true;
            }

            int boxId = (r/3) * 3 + c/3;
            if (!boxSet[boxId].insert(val).second) {
                state = State::Invalid;
                invalBox[boxId] = true;
            }
        }
    }

    // Check if solved
    if (state == State::Incomplete) {
        for (auto& set : boxSet) {
            if (set.size() != 9)
                return State::Incomplete;
        }
        return State::Complete; // every box full
    }
    return state;
}
