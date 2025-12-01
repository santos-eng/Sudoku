#ifndef GENERATOR_H
#define GENERATOR_H
#include <array>
#include <random>
#include "solver.h"
class Generator
{
public:
    Generator();
    static void generateUnique(std::array<std::array<int,9>,9>& board,
                               std::array<std::array<bool,9>,9>& fixed, int clues);

    static bool fillBoard(std::array<std::array<int,9>,9>& board, int r, int c,
                          Solver& s, std::mt19937& randomGen);

};

#endif // GENERATOR_H
