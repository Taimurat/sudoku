#include "../headers/sudoku.h"
#include "../headers/strategy.h"
#include "../headers/helpers.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;

extern std::ofstream fout;




//class Cell

vector<int> Cell::AllCandidates {1, 2, 3, 4, 5, 6, 7, 8, 9};

Cell::Cell(int value, int row, int column) 
    : value(value), row(row), column(column), box(row / 3 * 3 + column / 3), isSolved(false), candidates(AllCandidates) {}

Cell::~Cell() {}

Cell::Cell (const Cell& other)
{
    this->value = other.value;
    this->row = other.row;
    this->column = other.column;
    this->box = other.box;
    this->isSolved = other.isSolved;
    this->candidates = other.candidates;
}

Cell& Cell::operator=(const Cell& other)
{
    this->value = other.value;
    this->row = other.row;
    this->column = other.column;
    this->box = other.box;
    this->isSolved = other.isSolved;
    this->candidates = other.candidates;

    return *this;
}

Cell& Cell::operator=(const Cell&& other) noexcept
{
    this->value = other.value;
    this->row = other.row;
    this->column = other.column;
    this->box = other.box;
    this->isSolved = other.isSolved;
    this->candidates = std::move(other.candidates);

    return *this;
}

Cell::Cell (const Cell&& other) noexcept
{
    this->value = other.value;
    this->row = other.row;
    this->column = other.column;
    this->box = other.box;
    this->isSolved = other.isSolved;
    this->candidates = std::move(other.candidates);
}

int Cell::getValue() const { return value; }
int Cell::getRow() const { return row; }
int Cell::getColumn() const { return column; }
int Cell::getBox() const { return box; }
void Cell::setValue(int val) { value = val; isSolved = (val != 0); candidates.clear(); }
bool Cell::getIsSolved() const { return isSolved; }

bool Cell::hasCandidate(int value) const
{
    return std::find(this->candidates.begin(), this->candidates.end(), value) != this->candidates.end();
}

size_t Cell::getCountOfCandidates() const
{
    return this->candidates.size();
}

vector<int> Cell::getCandidates() const
{
    return this->candidates;
}

/**
 * @brief This function erases candidate in Cell. 
 *
 * The implication is that there is a full guarantee that the candidate will be removed.
 * 
 * @param value The value of deleting candidate
 * @return Erasing successfully or not
 */
bool Cell::eraseCandidate(int value)
{
    
    if (this->isSolved)
    {
        return false;
    }

    bool result = false;
    auto it = std::find(candidates.begin(), candidates.end(), value);
    if (it != candidates.end())
    {
        candidates.erase(it);
        result = true;
    }

    //no more candidates - sudoku unreachable
    else if (candidates.size() == 0)
    {
        throw MyException("Deleted last candidate in cell");
    }

    return result;
}







//class Sudoku

int Sudoku::AllValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

Sudoku::Sudoku() {
    // Board initialize 
    this->board.resize(9, vector<Cell*>(9));
    this->inversedBoard.resize(9, vector<Cell*>(9));
    this->byBoxBoard.resize(9, vector<Cell*>(9));
    this->SolvedNumbers.resize(10, vector<Cell*>{});

    for (int row = 0; row < 9; ++row)
    {
        for (int column = 0; column < 9; ++column)
        {
            this->board[row][column] = new Cell(0, row, column);
            this->inversedBoard[column][row] = this->board[row][column];
            this->byBoxBoard[row / 3 * 3 + column / 3][row % 3 * 3 + column % 3] = this->board[row][column];
        }
    }
}

Sudoku::Sudoku(const vector<vector<int>>& board) : Sudoku() {
    for (int row = 0; row < 9; ++row)
    {
        for (int column = 0; column < 9; ++column)
        {
            if (board[row][column] != 0)
            {
                this->board[row][column]->setValue(board[row][column]);
                this->SolvedNumbers[board[row][column]].push_back(this->board[row][column]);
            }
        }
    }
}

Sudoku::Sudoku(int** board) : Sudoku() {
    for (int row = 0; row < 9; ++row)
    {
        for (int column = 0; column < 9; ++column)
        {
            if (board[row][column] != 0)
            {
                this->board[row][column]->setValue(board[row][column]);
                this->SolvedNumbers[board[row][column]].push_back(this->board[row][column]);
            }
        }
    }
}

Sudoku::Sudoku(const Sudoku& other)
{
    this->isSolved = other.isSolved;

    this->board.resize(9, vector<Cell*>(9));
    this->inversedBoard.resize(9, vector<Cell*>(9));
    this->byBoxBoard.resize(9, vector<Cell*>(9));
    this->SolvedNumbers.resize(10, vector<Cell*>{});

    for (size_t row = 0; row < other.board.size(); ++row) {
        for (size_t column = 0; column < other.board[row].size(); ++column) {
            this->board[row][column] = new Cell(*other.board[row][column]);
            this->inversedBoard[column][row] = this->board[row][column];
            this->byBoxBoard[row / 3 * 3 + column / 3][row % 3 * 3 + column % 3] = this->board[row][column];
            if (other.board[row][column]->getIsSolved()) { this->SolvedNumbers[this->board[row][column]->getValue()].push_back(this->board[row][column]); }
        }
    }
}

Sudoku::~Sudoku()
{
    //if (board == nullptr) { return; }
    for (auto& row : board) {
        for (Cell* cell : row) {
            delete cell;
        }
    }
}

void Sudoku::display() const
{
    for (int row = 0; row < 9; ++row) 
    {
        for (int column = 0; column < 9; ++column) 
        {
            fout << board[row][column]->getValue() << " ";
        }
        fout << endl;
    }
    fout << endl;
}

void Sudoku::debugDisplay() const
{
    cout << "Usual" << endl;
    for (int row = 0; row < 9; ++row) 
    {
        for (int column = 0; column < 9; ++column) 
        {
            cout << board[row][column]->getValue() << " ";
        }
        cout << endl;
    }

    cout << "Inverted" << endl;
    for (int row = 0; row < 9; ++row) 
    {
        for (int column = 0; column < 9; ++column) 
        {
            cout << inversedBoard[row][column]->getValue() << " ";
        }
        cout << endl;
    }

    cout << "By box" << endl;
    for (int row = 0; row < 9; ++row) 
    {
        for (int column = 0; column < 9; ++column) 
        {
            cout << byBoxBoard[row][column]->getValue() << " ";
        }
        cout << endl;
    }
}

bool Sudoku::GetIsValid()
{
    for (int value = 1; value <= 9; ++value)
    {
        //row
        for (const auto& row : this->board)
        {
            if (std::count_if(row.begin(), row.end(), [&value](Cell* cell) { return cell->getValue() == value; }) > 1) { return false; }
        }
        //column
        for (const auto& column : this->inversedBoard)
        {
            if (std::count_if(column.begin(), column.end(), [&value](Cell* cell) { return cell->getValue() == value; }) > 1) { return false; }
        }
        //box
        for (const auto& box : this->byBoxBoard)
        {
            if (std::count_if(box.begin(), box.end(), [&value](Cell* cell) { return cell->getValue() == value; }) > 1) { return false; }
        }
    }
    return true;
}

void Sudoku::SolveCell(Cell* cell)
{
    this->SolvedNumbers[cell->value].push_back(cell);
    if (!this->GetIsValid())
    {
        throw MyException("The sudoku isnt valid now");
    }
}

const vector<vector<Cell*>>& Sudoku::getBoard() const
{
    return this->board;
}
const vector<vector<Cell*>>& Sudoku::getInversedBoard() const
{
    return this->inversedBoard;
}
const vector<vector<Cell*>>& Sudoku::getByBoxBoard() const
{
    return this->byBoxBoard;
}
const vector<vector<Cell*>>& Sudoku::getSolvedNumbers() const
{
    return this->SolvedNumbers;
}  