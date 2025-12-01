#ifndef SOLVER_H
#define SOLVER_H
#include <array>

class Solver
{
    bool foundOneSol = false;

    bool backtrack(std::array<std::array<int,9>,9>& board, int r, int c);
    bool checkMultiSol(std::array<std::array<int,9>,9>& board, int r, int c);
public:
    Solver();
    // Bitmasks to quickly check validity
    std::array<int,9> rowStore{};
    std::array<int,9> colStore{};
    std::array<int,9> boxStore{};

    bool validLookup(const int r, const int c, const int bit) const;
    void cleanBitmasks();
    void loadBitmasks(std::array<std::array<int,9>,9>& board);

    //Function used for solving the algoirthm, were speed is important
    bool backtrackSolve(std::array<std::array<int,9>,9>& board);

    // Assert if only one valid solution exists, which is official standard
    bool hasUniqueSol(std::array<std::array<int,9>,9>& board);
};

#endif // SOLVER_H
