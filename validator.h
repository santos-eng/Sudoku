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
    // Function used for validating during user input. Speed not priority for human solving.
    static State isValid(const std::array<std::array<int,9>,9>& board, std::array<bool,9>& invalRow,
                 std::array<bool,9>& invalCol, std::array<bool,9>& invalBox);
};

#endif // VALIDATOR_H
