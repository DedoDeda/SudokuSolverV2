#pragma once

#include "SudokuBoard.h"

namespace SudokuSolver
{
    bool IsBoardSolvable(const FSudokuBoard& Board);
    
    bool TrySolveBoard(FSudokuBoard& OutBoard);
}
