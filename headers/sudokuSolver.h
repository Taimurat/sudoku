#ifndef _SUDOKUSOLVER_H_
#define _SUDOKUSOLVER_H_

#pragma once
#include "../headers/sudoku.h"
#include "../headers/strategy.h"
#include "../headers/helpers.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Sudoku;
class BaseStrategy;

class SudokuSolver
{
public:
    SudokuSolver();

    SudokuSolver(Sudoku*);

    Sudoku* getSudoku();

    void solve();

    int brutSolve();
    
    bool SudokuIsSolved();

    vector<Sudoku*>& solutionFinder();

    static void initializeStrategies();

    ~SudokuSolver();
private:

    int brutSolveOneCell(Sudoku*, std::stack<Cell*>*, vector<Sudoku*>*);

    Sudoku* sudoku;
    int countOfSolvedCells;
    queue<Cell*> AllNewSolved;

    static vector<BaseStrategy*> Strategies;
    static int COUNT_OF_SUDOKU_CELLS;
};


#endif //_SUDOKUSOLVER_H_