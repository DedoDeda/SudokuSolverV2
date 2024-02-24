#include "SudokuBoard.h"

#include <algorithm>

FSudokuBoard::FSudokuBoard(std::vector<uint8_t> InBoardData) :
    BoardData { std::move(InBoardData) }
{
    BoardDimension = static_cast<size_t>(sqrt(BoardData.size()));
    BoxDimension = static_cast<size_t>(sqrt(BoardDimension));

    if (BoardDimension * BoardDimension != BoardData.size() || BoxDimension * BoxDimension != BoardDimension)
    {
        BoardDimension = 0;
        BoxDimension = 0;
        BoardData = std::vector<uint8_t> {};
    }
}

std::string FSudokuBoard::ToString()
{
    auto CountDigits = [](auto X)
    {
        uint8_t DigitsCount = 0;

        do
        {
            X /= 10;
            ++DigitsCount;
        }
        while (X);

        return DigitsCount;
    };

    std::string string;

    const uint8_t MaxDigits = CountDigits(BoardDimension);
    for (size_t Y = 0; Y < BoardDimension; ++Y)
    {
        if (Y % BoxDimension == 0)
        {
            string += std::string((BoardDimension + BoxDimension) * (MaxDigits + 1) + 1, '-') + '\n';
        }
        
        for (size_t X = 0; X < BoardDimension; ++X)
        {
            if (X % BoxDimension == 0)
            {
                string += '|' + std::string(MaxDigits, ' ');
            }
            
            const uint8_t CellValue = BoardData[Y * BoardDimension + X];
            string += std::to_string(CellValue) + std::string(MaxDigits - CountDigits(CellValue) + 1, ' ');
        }

        string += '|' + std::string(MaxDigits, ' ') + '\n';
    }

    string += std::string((BoardDimension + BoxDimension) * (MaxDigits + 1) + 1, '-') + '\n';

    return string;
}