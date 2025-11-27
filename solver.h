#ifndef SOLVER_H
#define SOLVER_H
#include <array>

class Solver
{
public:
    Solver();
    //Function used for solving the algoirthm, were speed is important
    static void backtrackSolve(std::array<std::array<int,9>,9>& board);
};

#endif // SOLVER_H
