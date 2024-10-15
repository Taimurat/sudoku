#include "../headers/sudoku.h"
#include "../headers/strategy.h"
#include "../headers/helpers.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <unordered_set>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::unordered_set;

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
                result[cell].first = cell->getCandidates()[0];
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





NakedPair::NakedPair() {}

/**
 * @brief This function apply NakedPair strategy to the sudoku. 
 *
 * This method also doesnt modify the sudoku
 * @note Given sudoku must be valid and has unique solution.
 * 
 * @param sudoku The applied sudoku
 * @return Vector of solved cells
 */
SolvedCells NakedPair::apply(const Sudoku& sudoku) 
{
    SolvedCells result; //default value of int is 0

    //return vector of Cell that contains candidates ONLY in given vector
    /*auto countNakedInDomen = [](vector<int>& candidates, vector<Cell*> domen) -> vector<Cell*>
    {
        vector<Cell*> result;

        for (Cell* cell : domen)
        {
            if (cell->getIsSolved()) { continue; }
            bool isCorrect = true;
            for (int candidate : cell->getCandidates())
            {
                if (std::find(candidates.begin(), candidates.end(), candidate) == candidates.end()) 
                { 
                    isCorrect = false; 
                    break; 
                }
            }
            if (isCorrect) { result.push_back(cell); }
        }

        return result;
    };*/

    auto intersect = [](unordered_set<int>& a, vector<int>&& b)
    {
        for (int i : b) 
        { 
            a.insert(i); 
        }
    };

    for (int domen = 0; domen < 9; ++domen)
    {
        //in row
        for (int indexOfFirstCell = 0; indexOfFirstCell < sudoku.getBoard()[domen].size() - 1; ++indexOfFirstCell)
        {
            Cell* firstCell = sudoku.getBoard()[domen][indexOfFirstCell];
            if (firstCell->getIsSolved()) { continue; }

            for (int indexOfSecondCell = indexOfFirstCell + 1; indexOfSecondCell < sudoku.getBoard()[domen].size(); ++indexOfSecondCell)
            {
                Cell* secondCell = sudoku.getBoard()[domen][indexOfSecondCell];
                if (secondCell->getIsSolved()) { continue; }

                std::unordered_set<int> candidates;
                intersect(candidates, firstCell->getCandidates());
                intersect(candidates, secondCell->getCandidates());

                if (candidates.size() == 2)
                {
                    for (Cell* cell : sudoku.getBoard()[domen])
                    {
                        if  (!cell->getIsSolved() && cell != firstCell
                                                  && cell != secondCell)
                        {
                            for (int candidate : candidates)
                            {
                                if (cell->hasCandidate(candidate))
                                {
                                    result[cell].second.insert(candidate);
                                }
                            }
                        }
                    }
                }
            }
        }

        //in column
        for (int indexOfFirstCell = 0; indexOfFirstCell < sudoku.getInversedBoard()[domen].size() - 1; ++indexOfFirstCell)
        {
            Cell* firstCell = sudoku.getInversedBoard()[domen][indexOfFirstCell];
            if (firstCell->getIsSolved()) { continue; }

            for (int indexOfSecondCell = indexOfFirstCell + 1; indexOfSecondCell < sudoku.getInversedBoard()[domen].size(); ++indexOfSecondCell)
            {
                Cell* secondCell = sudoku.getInversedBoard()[domen][indexOfSecondCell];
                if (secondCell->getIsSolved()) { continue; }

                std::unordered_set<int> candidates;
                intersect(candidates, firstCell->getCandidates());
                intersect(candidates, secondCell->getCandidates());

                if (candidates.size() == 2)
                {
                    for (Cell* cell : sudoku.getInversedBoard()[domen])
                    {
                        if  (!cell->getIsSolved() && cell != firstCell
                                                  && cell != secondCell)
                        {
                            for (int candidate : candidates)
                            {
                                if (cell->hasCandidate(candidate))
                                {
                                    result[cell].second.insert(candidate);
                                }
                            }
                        }
                    }
                }
            }
        }

        //in box
        for (int indexOfFirstCell = 0; indexOfFirstCell < sudoku.getByBoxBoard()[domen].size() - 1; ++indexOfFirstCell)
        {
            Cell* firstCell = sudoku.getByBoxBoard()[domen][indexOfFirstCell];
            if (firstCell->getIsSolved()) { continue; }

            for (int indexOfSecondCell = indexOfFirstCell + 1; indexOfSecondCell < sudoku.getByBoxBoard()[domen].size(); ++indexOfSecondCell)
            {
                Cell* secondCell = sudoku.getByBoxBoard()[domen][indexOfSecondCell];
                if (secondCell->getIsSolved()) { continue; }

                std::unordered_set<int> candidates;
                intersect(candidates, firstCell->getCandidates());
                intersect(candidates, secondCell->getCandidates());

                if (candidates.size() == 2)
                {
                    for (Cell* cell : sudoku.getByBoxBoard()[domen])
                    {
                        if  (!cell->getIsSolved() && cell != firstCell
                                                  && cell != secondCell)
                        {
                            for (int candidate : candidates)
                            {
                                if (cell->hasCandidate(candidate))
                                {
                                    result[cell].second.insert(candidate);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

NakedPair::~NakedPair() {}








NakedTripled::NakedTripled() {}

/**
 * @brief This function apply NakedTripled strategy to the sudoku. 
 *
 * This method also doesnt modify the sudoku
 * @note Given sudoku must be valid and has unique solution.
 * 
 * @param sudoku The applied sudoku
 * @return Vector of solved cells
 */
SolvedCells NakedTripled::apply(const Sudoku& sudoku)
{
    SolvedCells result; //default value of int is 0

    //return vector of Cell that contains candidates ONLY in given vector
    /*auto countNakedInDomen = [](vector<int>& candidates, vector<Cell*> domen) -> vector<Cell*>
    {
        vector<Cell*> result;

        for (Cell* cell : domen)
        {
            if (cell->getIsSolved()) { continue; }
            bool isCorrect = true;
            for (int candidate : cell->getCandidates())
            {
                if (std::find(candidates.begin(), candidates.end(), candidate) == candidates.end()) 
                { 
                    isCorrect = false; 
                    break; 
                }
            }
            if (isCorrect) { result.push_back(cell); }
        }

        return result;
    };*/

    auto intersect = [](unordered_set<int>& a, vector<int>&& b)
    {
        for (int i : b) 
        { 
            a.insert(i); 
        }
    };

    for (int domen = 0; domen < 9; ++domen)
    {
        //in row
        for (int indexOfFirstCell = 0; indexOfFirstCell < sudoku.getBoard()[domen].size() - 1; ++indexOfFirstCell)
        {
            Cell* firstCell = sudoku.getBoard()[domen][indexOfFirstCell];
            if (firstCell->getIsSolved()) { continue; }

            for (int indexOfSecondCell = indexOfFirstCell + 1; indexOfSecondCell < sudoku.getBoard()[domen].size(); ++indexOfSecondCell)
            {
                Cell* secondCell = sudoku.getBoard()[domen][indexOfSecondCell];
                if (secondCell->getIsSolved()) { continue; }

                for (int indexOfThirdCell = indexOfSecondCell + 1; indexOfThirdCell < sudoku.getBoard()[domen].size(); ++indexOfThirdCell)
                {
                    Cell* thirdCell = sudoku.getBoard()[domen][indexOfThirdCell];
                    if (thirdCell->getIsSolved()) { continue; }

                    std::unordered_set<int> candidates;
                    intersect(candidates, firstCell->getCandidates());
                    intersect(candidates, secondCell->getCandidates());
                    intersect(candidates, thirdCell->getCandidates());

                    if (candidates.size() == 3)
                    {
                        for (Cell* cell : sudoku.getBoard()[domen])
                        {
                            if  (!cell->getIsSolved() && cell != firstCell
                                                    && cell != secondCell
                                                    && cell != thirdCell)
                            {
                                for (int candidate : candidates)
                                {
                                    if (cell->hasCandidate(candidate))
                                    {
                                        result[cell].second.insert(candidate);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //in column
        for (int indexOfFirstCell = 0; indexOfFirstCell < sudoku.getInversedBoard()[domen].size() - 1; ++indexOfFirstCell)
        {
            Cell* firstCell = sudoku.getInversedBoard()[domen][indexOfFirstCell];
            if (firstCell->getIsSolved()) { continue; }

            for (int indexOfSecondCell = indexOfFirstCell + 1; indexOfSecondCell < sudoku.getInversedBoard()[domen].size(); ++indexOfSecondCell)
            {
                Cell* secondCell = sudoku.getInversedBoard()[domen][indexOfSecondCell];
                if (secondCell->getIsSolved()) { continue; }

                for (int indexOfThirdCell = indexOfSecondCell + 1; indexOfThirdCell < sudoku.getInversedBoard()[domen].size(); ++indexOfThirdCell)
                {
                    Cell* thirdCell = sudoku.getInversedBoard()[domen][indexOfThirdCell];
                    if (thirdCell->getIsSolved()) { continue; }

                    std::unordered_set<int> candidates;
                    intersect(candidates, firstCell->getCandidates());
                    intersect(candidates, secondCell->getCandidates());
                    intersect(candidates, thirdCell->getCandidates());

                    if (candidates.size() == 3)
                    {
                        for (Cell* cell : sudoku.getInversedBoard()[domen])
                        {
                            if  (!cell->getIsSolved() && cell != firstCell
                                                    && cell != secondCell
                                                    && cell != thirdCell)
                            {
                                for (int candidate : candidates)
                                {
                                    if (cell->hasCandidate(candidate))
                                    {
                                        result[cell].second.insert(candidate);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //in box getByBoxBoard
        for (int indexOfFirstCell = 0; indexOfFirstCell < sudoku.getByBoxBoard()[domen].size() - 1; ++indexOfFirstCell)
        {
            Cell* firstCell = sudoku.getByBoxBoard()[domen][indexOfFirstCell];
            if (firstCell->getIsSolved()) { continue; }

            for (int indexOfSecondCell = indexOfFirstCell + 1; indexOfSecondCell < sudoku.getByBoxBoard()[domen].size(); ++indexOfSecondCell)
            {
                Cell* secondCell = sudoku.getByBoxBoard()[domen][indexOfSecondCell];
                if (secondCell->getIsSolved()) { continue; }

                for (int indexOfThirdCell = indexOfSecondCell + 1; indexOfThirdCell < sudoku.getByBoxBoard()[domen].size(); ++indexOfThirdCell)
                {
                    Cell* thirdCell = sudoku.getByBoxBoard()[domen][indexOfThirdCell];
                    if (thirdCell->getIsSolved()) { continue; }

                    std::unordered_set<int> candidates;
                    intersect(candidates, firstCell->getCandidates());
                    intersect(candidates, secondCell->getCandidates());
                    intersect(candidates, thirdCell->getCandidates());

                    if (candidates.size() == 3)
                    {
                        for (Cell* cell : sudoku.getByBoxBoard()[domen])
                        {
                            if  (!cell->getIsSolved() && cell != firstCell
                                                    && cell != secondCell
                                                    && cell != thirdCell)
                            {
                                for (int candidate : candidates)
                                {
                                    if (cell->hasCandidate(candidate))
                                    {
                                        result[cell].second.insert(candidate);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

NakedTripled::~NakedTripled() {}
