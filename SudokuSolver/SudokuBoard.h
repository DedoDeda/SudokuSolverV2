#pragma once

#include <string>
#include <unordered_set>
#include <vector>

class FSudokuBoard
{
    friend std::unordered_set<uint8_t> FindCellTakenValues(const FSudokuBoard&, size_t, size_t);
    
    friend std::unordered_set<uint8_t> FindCellPossibleValues(const FSudokuBoard&, size_t, size_t);

    friend bool TrySolveSimpleCells(FSudokuBoard&);

    friend bool TrySolveComplexCells(FSudokuBoard&);
    
public:
    FSudokuBoard() = default;

    explicit FSudokuBoard(std::vector<uint8_t> InBoardData);

public:
    std::string ToString();

protected:
    size_t BoardDimension = 0;

    size_t BoxDimension = 0;

    std::vector<uint8_t> BoardData;
};
