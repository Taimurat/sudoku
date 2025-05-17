#include <iostream>
#include <vector>
#include "../headers/sudoku.h"
#include "../headers/strategy.h"
#include "../headers/helpers.h"
#include "../headers/sudokuSolver.h"
//#include <unordered_map>

#define DEBUG

int main() {

    Sudoku voidSudoku(vector<vector<int>>
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    });
    Sudoku easiestSudoku(vector<vector<int>>
    {
        {3, 0, 0, 9, 6, 7, 0, 0, 1},
        {0, 4, 0, 3, 0, 2, 0, 8, 0},
        {0, 2, 0, 0, 0, 0, 0, 7, 0},
        {0, 7, 0, 0, 0, 0, 0, 9, 0},
        {0, 0, 0, 8, 7, 3, 0, 0, 0},
        {5, 0, 0, 0, 1, 0, 0, 0, 3},
        {0, 0, 4, 7, 0, 5, 1, 0, 0},
        {9, 0, 5, 0, 0, 0, 2, 0, 7},
        {8, 0, 0, 6, 2, 1, 0, 0, 4}
    });
    Sudoku gentleSudoku(vector<vector<int>>
    {
        {0, 0, 0, 0, 0, 4, 0, 2, 8},
        {4, 0, 6, 0, 0, 0, 0, 0, 5},
        {1, 0, 0, 0, 3, 0, 6, 0, 0},
        {0, 0, 0, 3, 0, 1, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 1, 4, 0},
        {0, 0, 0, 7, 0, 9, 0, 0, 0},
        {0, 0, 2, 0, 1, 0, 0, 0, 3},
        {9, 0, 0, 0, 0, 0, 5, 0, 7},
        {6, 7, 0, 4, 0, 0, 0, 0, 0}
    });

    Sudoku moderateSudoku(vector<vector<int>>
    {
        {7, 2, 0, 0, 9, 6, 0, 0, 3},
        {0, 0, 0, 2, 0, 5, 0, 0, 0},
        {0, 8, 0, 0, 0, 4, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 6, 0},
        {1, 0, 6, 5, 0, 3, 8, 0, 7},
        {0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 0, 8, 0, 0, 0, 9, 0},
        {0, 0, 0, 7, 0, 2, 0, 0, 0},
        {2, 0, 0, 4, 3, 0, 0, 1, 8}
    });
    Sudoku nakedMadnessSudoku(vector<vector<int>>
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 9, 0, 0, 5, 0, 0},
        {5, 6, 0, 3, 1, 0, 0, 9, 0},
        {1, 0, 0, 6, 0, 0, 0, 2, 8},
        {0, 0, 4, 0, 0, 0, 7, 0, 0},
        {2, 7, 0, 0, 0, 4, 0, 0, 3},
        {0, 4, 0, 0, 6, 8, 0, 3, 5},
        {0, 0, 2, 0, 0, 5, 9, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    });

    Sudoku MySudoku(vector<vector<int>>
    {
        {0, 2, 0, 0, 0, 0, 0, 7, 0},
        {0, 0, 0, 5, 0, 0, 0, 6, 0},
        {0, 0, 0, 9, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 5, 0, 0},
        {0, 1, 0, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 9, 0, 8},
        {9, 0, 5, 0, 0, 0, 4, 0, 0},
        {6, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 8, 0, 0, 0, 0, 0}
    });


    SudokuSolver::initializeStrategies();

    Sudoku& testSudoku = MySudoku;

    #ifdef DEBUG
    testSudoku.debugDisplay();
    SudokuSolver slv(&testSudoku);
    std::cout << testSudoku.GetIsValid() << std::endl;
    slv.brutSolve();
    slv.getSudoku()->debugDisplay();

    #else
    testSudoku.display();
    SudokuSolver slv(&testSudoku);
    std::cout << "After solving:" << std::endl;
    slv.solve();
    slv.getSudoku()->debugDisplay();

    #endif //DEBUG

    return 0;
}
