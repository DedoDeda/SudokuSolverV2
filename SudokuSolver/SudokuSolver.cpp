#include "SudokuSolver.h"

#include <unordered_set>

std::unordered_set<uint8_t> FindCellTakenValues(const FSudokuBoard& Board, const size_t Y, const size_t X)
{
    std::unordered_set<uint8_t> TakenValues;

    for (size_t CurrentY = 0; CurrentY < Board.BoardDimension; ++CurrentY)
    {
        const uint8_t CurrentCellValue = Board.BoardData[CurrentY * Board.BoardDimension + X];
        if (CurrentCellValue != 0)
        {
            TakenValues.insert(CurrentCellValue);
        }
    }

    for (size_t CurrentX = 0; CurrentX < Board.BoardDimension; ++CurrentX)
    {
        const uint8_t CellValue = Board.BoardData[Y * Board.BoardDimension + CurrentX];
        if (CellValue != 0)
        {
            TakenValues.insert(CellValue);
        }
    }

    const size_t StartY = Y - Y % Board.BoxDimension;
    for (size_t CurrentY = StartY; CurrentY < StartY + Board.BoxDimension; ++CurrentY)
    {
        const size_t StartX = X - X % Board.BoxDimension;
        for (size_t CurrentX = StartX; CurrentX < StartX + Board.BoxDimension; ++CurrentX)
        {
            const uint8_t CurrentCellValue = Board.BoardData[CurrentY * Board.BoardDimension + CurrentX];
            if (CurrentCellValue != 0)
            {
                TakenValues.insert(CurrentCellValue);
            }
        }
    }

    return TakenValues;
}

std::unordered_set<uint8_t> FindCellPossibleValues(const FSudokuBoard& Board, const size_t Y, const size_t X)
{
    std::unordered_set<uint8_t> CellPossibleValues;

    const std::unordered_set<uint8_t> TakenValues = FindCellTakenValues(Board, Y, X);
    for (uint8_t CurrentCellValue = 1; CurrentCellValue <= Board.BoardDimension; ++CurrentCellValue)
    {
        if (TakenValues.find(CurrentCellValue) == TakenValues.end())
        {
            CellPossibleValues.insert(CurrentCellValue);
        }
    }

    return CellPossibleValues;
}

bool TrySolveSimpleCells(FSudokuBoard& OutBoard)
{
    bool bHasAdvanced = false;
    do
    {
        bHasAdvanced = false;

        for (size_t Y = 0; Y < OutBoard.BoardDimension; ++Y)
        {
            for (size_t X = 0; X < OutBoard.BoardDimension; ++X)
            {
                uint8_t& CellValue = OutBoard.BoardData[Y * OutBoard.BoardDimension + X];
                if (!CellValue)
                {
                    const std::unordered_set<uint8_t> CellPossibleValues = FindCellPossibleValues(OutBoard, Y, X);
                    if (CellPossibleValues.size() == 1)
                    {
                        CellValue = *CellPossibleValues.begin();
                        bHasAdvanced = true;
                    }
                    else if (CellPossibleValues.empty())
                    {
                        return false;
                    }
                }
            }
        }
    }
    while (bHasAdvanced);

    return true;
}

bool TrySolveComplexCells(FSudokuBoard& OutBoard)
{
    bool bHasUnsolvedCell = false;

    for (size_t Y = 0; Y < OutBoard.BoardDimension; ++Y)
    {
        for (size_t X = 0; X < OutBoard.BoardDimension; ++X)
        {
            if (!OutBoard.BoardData[Y * OutBoard.BoardDimension + X])
            {
                for (const uint8_t CellPossibleValue : FindCellPossibleValues(OutBoard, Y, X))
                {
                    FSudokuBoard TryBoard = OutBoard;
                    TryBoard.BoardData[Y * OutBoard.BoardDimension + X] = CellPossibleValue;

                    if (SudokuSolver::TrySolveBoard(TryBoard))
                    {
                        OutBoard = TryBoard;
                        return true;
                    }
                }

                bHasUnsolvedCell = true;
            }
        }
    }

    return !bHasUnsolvedCell;
}

bool SudokuSolver::IsBoardSolvable(const FSudokuBoard& Board)
{
    FSudokuBoard TryBoard = Board;
    return TrySolveBoard(TryBoard);
}

bool SudokuSolver::TrySolveBoard(FSudokuBoard& OutBoard)
{
    return TrySolveSimpleCells(OutBoard) && TrySolveComplexCells(OutBoard);
}