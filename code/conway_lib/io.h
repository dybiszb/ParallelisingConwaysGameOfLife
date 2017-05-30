#ifndef IO_H
#define IO_H

#include <fstream>
#include <sstream>

#include "game_grid.h"

namespace cgol {
    /**
     * Loads grid from speccified path and generates std::runtime_error exception
     * whenever there is inconsistency with assumed structure. Perfect input
     * file should look like this:
     * ------- file.txt --------
     * 3
     * 2
     *
     * 1 0 0
     * 0 1 0
     * -------------------------
     * First two rows must be filled with grid's width and height.
     * Next, there can be as many empty lines as one wants.
     * Finally, the grid should be written row by row and its values
     * must be white-space separated. Number of whitespaces does not matter.
     *
     * @param path Path to a file with a grid.
     *
     * @return GameGrid object corresponding to grid loaded from file.
     */
    cgol::GameGridSharedPtrT loadGridFromFile(const std::string &path);

    /**
     * Saves consecutive grid states of the game to specified file.
     * Output file structure is as follows:
     * ------- file.txt --------
     * 3
     * 2
     *
     * 1 0 0
     * 0 1 0
     *
     * 0 0 0
     * 0 0 0
     * -------------------------
     * First two rows must be filled with grid's width and height.
     * Next, each state of a grid is dumped and separated by whitespace.
     * Grid is written row by row and its values are also white-space separated.
     *
     * @param steps Consecutive steps/grid states of a game.
     * @param path  Path to output file.
     */
    void dumpGameHistory(const StepsHistoryT &steps,
                         const std::string &path);

}

#endif
