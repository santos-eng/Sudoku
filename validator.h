#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <array>

class Validator
{
public:
    Validator();
    enum class State {
        Incomplete,
        Complete,
        Invalid
    };
    static State isValid(const int board[9][9], std::array<bool,9>& invalRow,
                 std::array<bool,9>& invalCol, std::array<bool,9>& invalBox);
};

#endif // VALIDATOR_H
