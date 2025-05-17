#include "../headers/sudoku.h"
#include "../headers/strategy.h"
#include "../headers/helpers.h"
#include "../headers/sudokuSolver.h"
#include <iostream>
#include <vector>

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
    Strategies.push_back(new NakedPair());
    Strategies.push_back(new NakedTripled());
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

int SudokuSolver::brutSolve()
{
    solve();
    std::vector<Sudoku*> solutions = solutionFinder();

    std::cout << solutions.size() << std::endl;
    if (solutions.size() == 1)
    {
        sudoku = std::move(new Sudoku(*solutions[0]));
    }
    else
    {
        std::cout << "There are " << solutions.size() << " counts of solutions" << std::endl;
    }
    return solutions.size();
}

vector<Sudoku*>& SudokuSolver::solutionFinder()
{
    std::vector<Sudoku*>* solution = new std::vector<Sudoku*>;

    Sudoku* tmpSudoku = new Sudoku(*sudoku);
    
    std::stack<Cell*>* tmp = new std::stack<Cell*>();
    for (std::vector<Cell*> row : tmpSudoku->getBoard())
    {
        for (Cell* cell : row)
        {
            if (!(cell->getIsSolved())) { tmp->push(cell); }
        }
    }
    
    int res = brutSolveOneCell(tmpSudoku, tmp, solution);
    
    return *solution;
}

int SudokuSolver::brutSolveOneCell(Sudoku* tmpSudoku, std::stack<Cell*>* tmp, vector<Sudoku*>* result)
{
    if (tmp->empty()) { 
        std::cout << tmpSudoku->GetIsValid() << std::endl; 
        tmpSudoku->debugDisplay(); 
        if (tmpSudoku->GetIsValid())
        {
            Sudoku* solution = new Sudoku(*tmpSudoku);
            result->push_back(solution);
        }
        return tmpSudoku->GetIsValid();
    }
    int res = 0;
    
    Cell* cell = tmp->top();
    tmp->pop();
    for (int candidate : cell->getCandidates())
    {
        cell->setValue(candidate);
        if (tmpSudoku->GetIsValid())
        {
            tmpSudoku->display();
            res += brutSolveOneCell(tmpSudoku, tmp, result);
        }
    }
    
    *cell = Cell(*sudoku->getBoard()[cell->getRow()][cell->getColumn()]);
    tmp->push(cell);
    return res;
}

bool SudokuSolver::SudokuIsSolved()
{
    return countOfSolvedCells == COUNT_OF_SUDOKU_CELLS;
}

SudokuSolver::~SudokuSolver() {}