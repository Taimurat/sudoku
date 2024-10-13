#include <iostream>
#include <vector>
#include "../headers/sudoku.h"
#include "../headers/strategy.h"
#include "../headers/helpers.h"
#include "../headers/sudokuSolver.h"
//#include <unordered_map>

//#define DEBUG

int main() {
    Sudoku easiestSudoku(vector<vector<int>>
    {
        vector<int> {3, 0, 0, 9, 6, 7, 0, 0, 1},
        vector<int> {0, 4, 0, 3, 0, 2, 0, 8, 0},
        vector<int> {0, 2, 0, 0, 0, 0, 0, 7, 0},
        vector<int> {0, 7, 0, 0, 0, 0, 0, 9, 0},
        vector<int> {0, 0, 0, 8, 7, 3, 0, 0, 0},
        vector<int> {5, 0, 0, 0, 1, 0, 0, 0, 3},
        vector<int> {0, 0, 4, 7, 0, 5, 1, 0, 0},
        vector<int> {9, 0, 5, 0, 0, 0, 2, 0, 7},
        vector<int> {8, 0, 0, 6, 2, 1, 0, 0, 4}
    });
    Sudoku gentleSudoku(vector<vector<int>>
    {
        vector<int> {0, 0, 0, 0, 0, 4, 0, 2, 8},
        vector<int> {4, 0, 6, 0, 0, 0, 0, 0, 5},
        vector<int> {1, 0, 0, 0, 3, 0, 6, 0, 0},
        vector<int> {0, 0, 0, 3, 0, 1, 0, 0, 0},
        vector<int> {0, 8, 7, 0, 0, 0, 1, 4, 0},
        vector<int> {0, 0, 0, 7, 0, 9, 0, 0, 0},
        vector<int> {0, 0, 2, 0, 1, 0, 0, 0, 3},
        vector<int> {9, 0, 0, 0, 0, 0, 5, 0, 7},
        vector<int> {6, 7, 0, 4, 0, 0, 0, 0, 0}
    });

    SudokuSolver::initializeStrategies();

    #ifdef DEBUG
    gentleSudoku.debugDisplay();
    SudokuSolver slv(&gentleSudoku);
    std::cout << gentleSudoku.GetIsValid() << std::endl;
    slv.solve();
    gentleSudoku.debugDisplay();
    #else
    gentleSudoku.display();
    SudokuSolver slv(&gentleSudoku);
    std::cout << "After solving:" << std::endl;
    slv.solve();
    gentleSudoku.display();
    #endif //DEBUG

    return 0;
}
