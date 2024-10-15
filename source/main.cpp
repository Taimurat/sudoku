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

    Sudoku moderateSudoku(vector<vector<int>>
    {
        vector<int> {7, 2, 0, 0, 9, 6, 0, 0, 3},
        vector<int> {0, 0, 0, 2, 0, 5, 0, 0, 0},
        vector<int> {0, 8, 0, 0, 0, 4, 0, 2, 0},
        vector<int> {0, 0, 0, 0, 0, 0, 0, 6, 0},
        vector<int> {1, 0, 6, 5, 0, 3, 8, 0, 7},
        vector<int> {0, 4, 0, 0, 0, 0, 0, 0, 0},
        vector<int> {0, 3, 0, 8, 0, 0, 0, 9, 0},
        vector<int> {0, 0, 0, 7, 0, 2, 0, 0, 0},
        vector<int> {2, 0, 0, 4, 3, 0, 0, 1, 8}
    });

    SudokuSolver::initializeStrategies();

    #ifdef DEBUG
    moderateSudoku.debugDisplay();
    SudokuSolver slv(&moderateSudoku);
    std::cout << moderateSudoku.GetIsValid() << std::endl;
    slv.solve();
    moderateSudoku.debugDisplay();

    #else
    moderateSudoku.display();
    SudokuSolver slv(&moderateSudoku);
    std::cout << "After solving:" << std::endl;
    slv.solve();
    moderateSudoku.display();

    #endif //DEBUG

    return 0;
}
