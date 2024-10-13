#include "../headers/sudoku.h"
#include "../headers/strategy.h"
#include "../headers/helpers.h"
#include "../headers/sudokuSolver.h"
#include <iostream>
#include <vector>
#include <tuple>

int SudokuSolver::COUNT_OF_SUDOKU_CELLS = 81;
vector<BaseStrategy*> SudokuSolver::Strategies = vector<BaseStrategy*>{};

SudokuSolver::SudokuSolver()
{
    this->AllNewSolved = queue<Cell*>{};
    this->countOfSolvedCells = 0;
}

SudokuSolver::SudokuSolver(Sudoku* sudoku) : SudokuSolver()
{
    this->sudoku = sudoku;
    for (int value : Cell::AllCandidates)
    {
        for (Cell* cell : sudoku->SolvedNumbers[value])
        {
            this->AllNewSolved.push(cell);
            ++countOfSolvedCells;
        }
    }
}

Sudoku* SudokuSolver::getSudoku()
{
    return this->sudoku;
}

void SudokuSolver::initializeStrategies()
{
    Strategies.push_back(new ClearCandidatesByRules());
    Strategies.push_back(new NakedSingle());
    Strategies.push_back(new HiddenSinglet());
}

void SudokuSolver::solve()
{
    bool result;
    while (!this->SudokuIsSolved())
    {
        result = false;
        for (BaseStrategy* strategy : Strategies)
        {
            /*
            * solvedCell:
            * pair< Cell* thisCell, pair< int SetValue, vector<int> erasedCandidates > >
            */
            for(const auto& solvedCell : strategy->apply(*this->sudoku))
            {
                Cell* cell = solvedCell.first;
                int value = solvedCell.second.first;
                const auto& erasedCandidates = solvedCell.second.second;

                if (1 <= value && value <= 9)
                {
                    cell->setValue(value);
                    this->sudoku->SolveCell(cell);
                    ++countOfSolvedCells;
                    result = true;
                }
                else
                {
                    for (const int candidate : erasedCandidates)
                    {
                        if (cell->eraseCandidate(candidate)) { result = true; }
                    }
                }
            }
            if (result) { break; }
        }

        if (!result) 
        { 
            std::cout << "No possible methods to solve this" << std::endl; 
            break; 
        }
    }
}

bool SudokuSolver::SudokuIsSolved()
{
    return countOfSolvedCells == COUNT_OF_SUDOKU_CELLS;
}

SudokuSolver::~SudokuSolver() {}