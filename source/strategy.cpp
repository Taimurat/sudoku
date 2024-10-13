#include "../headers/sudoku.h"
#include "../headers/strategy.h"
#include "../headers/helpers.h"
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

typedef std::unordered_map< Cell*, std::pair< int,  std::unordered_set<int> > > SolvedCells;


NakedSingle::NakedSingle() {}

/**
 * @brief This function apply NakedSingle strategy to the sudoku. 
 *
 * This method also doesnt modify the sudoku
 * @note Given sudoku must be valid and has unique solution.
 * 
 * @param sudoku The applied sudoku
 * @return Vector of solved cells
 */
SolvedCells NakedSingle::apply(const Sudoku& sudoku)
{
    SolvedCells result; //default value of int is 0

    for(int row = 0; row < 9; ++row)
    {
        for (Cell* cell : sudoku.getBoard()[row])
        {
            if (!cell->getIsSolved() && cell->getCountOfCandidates() == 1)
            {
                result[cell].first = cell->getValue();
            }
        }
    }

    return result;
}

NakedSingle::~NakedSingle() {}



ClearCandidatesByRules::ClearCandidatesByRules() {}

/**
 * @brief This function apply ClearCandidatesByRules strategy to the sudoku. 
 *
 * This method also doesnt modify the sudoku
 * @note Given sudoku must be valid and has unique solution.
 * 
 * @param sudoku The applied sudoku
 * @return Vector of solved cells
 */
SolvedCells ClearCandidatesByRules::apply(const Sudoku& sudoku) 
{

    SolvedCells result; //default value of int is 0

    for(int value = 1; value <= 9; ++value)
    {
        for (Cell* cell : sudoku.getSolvedNumbers()[value])
        {

            //row
            for (Cell* candidatesCell : sudoku.getBoard()[cell->getRow()])
            {
                if (candidatesCell->hasCandidate(cell->getValue())) 
                { 
                    result[candidatesCell].second.insert(cell->getValue());
                }
            }

            //column
            for (Cell* candidatesCell : sudoku.getInversedBoard()[cell->getColumn()])
            {
                if (candidatesCell->hasCandidate(cell->getValue())) 
                { 
                    result[candidatesCell].second.insert(cell->getValue());
                }
            }

            //box
            for (Cell* candidatesCell : sudoku.getByBoxBoard()[cell->getBox()])
            {
                if (candidatesCell->hasCandidate(cell->getValue())) 
                { 
                    result[candidatesCell].second.insert(cell->getValue());
                }
            }
        }
    }

    return result;
}

ClearCandidatesByRules::~ClearCandidatesByRules() {}




HiddenSinglet::HiddenSinglet() {}

/**
 * @brief This function apply HiddenSinglet strategy to the sudoku. 
 *
 * This method also doesnt modify the sudoku
 * @note Given sudoku must be valid and has unique solution.
 * 
 * @param sudoku The applied sudoku
 * @return Vector of solved cells
 */
SolvedCells HiddenSinglet::apply(const Sudoku& sudoku) 
{
    SolvedCells result;

    auto countInDomen = [](int value, vector<Cell*> domen) -> int
    {
        int count = 0;
        for (Cell* cell : domen)
        {
            if (!cell->getIsSolved() && cell->hasCandidate(value)) { ++count; }
        }

        return count;
    };
    int countOfValue;

    for (int value = 1; value <= 9; ++value)
    {
        for (int domen = 0; domen < 9; ++domen)
        {
            //in row
            countOfValue = countInDomen(value, sudoku.getBoard()[domen]);
            for (Cell* cell : sudoku.getBoard()[domen])
            {
                if (!cell->getIsSolved() && countOfValue == 1 && cell->hasCandidate(value))
                {
                    result[cell].first = value;
                }
            }

            //in column
            countOfValue = countInDomen(value, sudoku.getInversedBoard()[domen]);
            for (Cell* cell : sudoku.getInversedBoard()[domen])
            {
                if (!cell->getIsSolved() && countOfValue == 1 && cell->hasCandidate(value))
                {
                    result[cell].first = value;
                }
            }

            //in box
            countOfValue = countInDomen(value, sudoku.getByBoxBoard()[domen]);
            for (Cell* cell : sudoku.getByBoxBoard()[domen])
            {
                if (!cell->getIsSolved() && countOfValue == 1 && cell->hasCandidate(value))
                {
                    result[cell].first = value;
                }
            }
        }
    }

    return result;
}

HiddenSinglet::~HiddenSinglet() {}
