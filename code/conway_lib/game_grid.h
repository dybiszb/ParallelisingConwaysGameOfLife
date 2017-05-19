#ifndef GAME_GRID_H
#define GAME_GRID_H

#include <iostream>
#include <memory>
#include <vector>
#include <random>


#include "utilities.h"

namespace cgol {

    const size_t GRID_MAX_WIDTH = 128;
    const size_t GRID_MAX_HEIGHT = 128;
    using GridRawEntries = std::vector<int>;

    class GameGrid {
    public:
        GameGrid(int gridWidth, int gridHeight, bool randomize = true);

        GameGrid(const GridRawEntries &rawEntries, int gridWidth,
                 int gridHeight);

        GameGrid(const GameGrid &grid);

        // In case of accessing value from invalid row/ col - 0 will be
        // returned.
        int getEntry(int row, int col);

        void setEntry(int row, int col, int value);

        int getWidth() const;

        int getHeight() const;

        GridRawEntries getRawEntries() const;

        void print();

        bool operator== (const GameGrid &other);

    private:
        void checkGridDimensions(int gridWidth, int gridHeight);

        GridRawEntries m_entries;
        const int m_width;
        const int m_height;
    };

    using GameGridSharedPtrT = std::shared_ptr<GameGrid>;
    using StepsHistorySharedPtrT = std::vector<GameGridSharedPtrT>;
}

#endif
