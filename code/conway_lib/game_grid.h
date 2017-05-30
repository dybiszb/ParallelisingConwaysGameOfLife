#ifndef GAME_GRID_H
#define GAME_GRID_H

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <sstream>
#include "utilities.h"

namespace cgol {

    const size_t GRID_MAX_WIDTH = 256;
    const size_t GRID_MAX_HEIGHT = 256;
    using GridRawEntries = std::vector<int>;

    class GameGrid {
    public:
        /**
         * Creates a grid of specified dimensions. It can be filled with random
         * number or zeros. Each of the dimensions must lie between 0
         * and its maximal value (see GRID_MA_WIDTH and GRID_MAX_HEIGHT).
         * Otherwise std::logic_error will be thrown.
         *
         * @param gridWidth  Width of the grid.
         * @param gridHeight Height of the grid.
         * @param randomize  If true, entries will be randomized. Otherwise,
         *                   the grid will be filled with zeros.
         */
        GameGrid(int gridWidth, int gridHeight, bool randomize = true);

        /**
         * Creates a grid filled with specified entries.
         * Each of the dimensions must lie between 0 and its maximal value
         * (see GRID_MAX_WIDTH and GRID_MAX_HEIGHT). Otherwise std::logic_error
         * will be thrown. What is more, the dimensions must much size of
         * raw entries vector in a sense that:
         * gridWidth * gridHeight = rawEntries.size()
         *
         * @param rawEntries Vector of integers representing a grid as a
         *                   continous block of data (row-wise).
         * @param gridWidth  Width of the grid.
         * @param gridHeight Height of the grid.
         */
        GameGrid(const GridRawEntries &rawEntries, int gridWidth,
                 int gridHeight);

        /**
         * Copy constructor for convenient grid initialization.
         *
         * @param grid A grid whose entries will be copied.
         */
        GameGrid(const GameGrid &grid);

        /**
         * Returns an entry value.
         * NOTE: If accessing data via indices that lies outside of the grid's
         * dimensions, 0 will be returned. It assures that Conway's Game of
         * Life will not have to make additional checks for indices correctness.
         *
         * @param row Number of row. Indexing starts from 0.
         * @param col Number of column. Indexing starts from 0.
         *
         * @return Value of entry at specified column and row.
         */
        int getEntry(int row, int col);

        /**
         * If row or column index is out of scope std::runtime_error will be
         * thrown. If value is different from 0 and 1, also std::runtime_error
         * will be thrown.
         *
         * @param row   Number of row. Indexing starts from 0.
         * @param col   Number of column. Indexing starts from 0.
         * @param value New value for the entry. Must be either 0 or 1.
         */
        void setEntry(int row, int col, int value);

        /**
         * Acquire the grid's width.
         *
         * @return The grid's width.
         */
        int getWidth() const;

        /**
         * Acquire the grid's height.
         *
         * @return The grid's height.
         */
        int getHeight() const;

        /**
         * Returns a copy of the grid's raw entries - vector of integers
         * representing the grid as a continuous block of data in row-wise
         * fashion. E.g.
         * Grid:
         * 1 0 0
         * 0 1 0
         * Would be represented by the vector as:
         * 1 0 0 0 1 0
         * And only knowing the grid's widht and height one can decipher it.
         *
         * @return Raw grid's data in form of a vector of integers.
         */
        GridRawEntries getRawEntries() const;

        // TODO: remove
        void print();

        /**
         * Converts specified row of the grid into coma separated string.
         *
         * @param row Number of row to be onsidered.
         *
         * @return String object of the row's entries.
         */
        std::string getRowAsString(const int row);

        /**
         * Compares two grids entries. If they do not match, false will be
         * return. Otherwise, true.
         *
         * @param other Grid to compare with.
         *
         * @return True - the same entries, false - different entries.
         */
        bool operator==(const GameGrid &other);

    private:
        void checkGridDimensions(int gridWidth, int gridHeight);
        void checkDataCorrectness(const cgol::GridRawEntries &data);

        GridRawEntries m_entries;
        const int m_width;
        const int m_height;
    };

    using GameGridSharedPtrT = std::shared_ptr<GameGrid>;
    using StepsHistoryT = std::vector<GameGridSharedPtrT>;
}

#endif
