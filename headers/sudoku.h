#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#pragma once
#include <iostream>
#include <vector>

#include "../headers/strategy.h"
#include "../headers/helpers.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Cell;
class Sudoku;

class Cell {

friend class Sudoku;

public:
    Cell(int value = 0, int row = 0, int column = 0);

    ~Cell();

    Cell (const Cell&);

    Cell& operator=(const Cell&);

    Cell (Cell&&) noexcept;

    int getValue() const;
    int getRow() const;
    int getColumn() const;
    int getBox() const;
    void setValue(int);
    bool getIsSolved() const;

    bool eraseCandidate(int);

    bool hasCandidate(int) const;

    size_t getCountOfCandidates() const;

    vector<int> getCandidates() const;

    static vector<int> AllCandidates;

private:
    int value;
    int row;
    int column;
    int box;
    bool isSolved;
    vector<int> candidates;
};

class Sudoku {

friend class SudokuSolver;

public:
    Sudoku();

    Sudoku(const vector<vector<int>>&);

    Sudoku(int** board);

    void display() const;

    void debugDisplay() const;

    bool GetIsValid();

    void SolveCell(Cell*);

    const vector<vector<Cell*>>& getBoard() const;
    const vector<vector<Cell*>>& getInversedBoard() const;
    const vector<vector<Cell*>>& getByBoxBoard() const;
    const vector<vector<Cell*>>& getSolvedNumbers() const;    

private:
    vector<vector<Cell*>> board;
    vector<vector<Cell*>> inversedBoard;
    vector<vector<Cell*>> byBoxBoard;
    vector<vector<Cell*>> SolvedNumbers;
    bool isSolved;
    
    static int AllValues [];

};

#endif //_SUDOKU_H_