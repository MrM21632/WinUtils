/*
 * SudokuConfig.h: Sudoku configuration class definition and method
 * declarations.
 * 
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/11/2017, 9:25pm
 */

#ifndef __GUARD__SUDOKUCONFIG_H_
#define __GUARD__SUDOKUCONFIG_H_

#include "Configuration.h"

/**
 * SudokuConfig: Sudoku solver configuration.
 */
class SudokuConfig : Configuration {
    public:
        SudokuConfig();
        ~SudokuConfig() {}
        std::vector<Configuration*> get_successors();
        bool is_valid();
        bool is_solution();
    
    private:
        int** grid;
}

#endif  // __GUARD__SUDOKUCONFIG_H_