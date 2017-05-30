#ifndef STRATEGIES_H
#define STRATEGIES_H

#include <iostream>
#include "game_grid.h"

#ifdef _OPENMP

#include <omp.h>

#endif

namespace cgol {

    using StrategyT =
    std::function<const cgol::StepsHistoryT(
            const cgol::GameGridSharedPtrT &inputGrid,
            size_t steps)>;


    /**
     * Using rules of Conway's Game of Life, the procedure will interpret data
     * from 'prev' grid at position [row][col] and save the result in 'next'
     * grid. 'next' grid will be modified, 'prev' will stay the same.
     *
     * Thread safe operation if called for different indices of row and column.
     * Data will be only written to the next grid, never read. Writing will
     * change only one, specific entry in the next grid.
     *
     * @param prev Grid of the previous step.
     * @param next Grid for updated entries.
     * @param row  Row of an entry that will be updated.
     * @param col  Column of an entry that will be updated.
     */
    void calculateStep(const GameGridSharedPtrT &prev, GameGridSharedPtrT &next,
                       int row, int col);

    /**
     * The procedure follows signature of StrategyT functor. It provides means
     * for simulating Conway's Game of Life for provided grid for specified
     * number of steps. The calculations will be performe sequentiali using CPU.
     *
     * @param inputGrid Grid with starting entries.
     * @param steps     Number of steps to simulate.
     *
     * @return A vector of grids - each calculated at different step of the
     *         simulation.
     */
    const cgol::StepsHistoryT
    strategyCPU(const cgol::GameGridSharedPtrT &inputGrid, int steps);

    const cgol::StepsHistoryT
    strategyOpenMP(const cgol::GameGridSharedPtrT &inputGrid, int steps);
}


#endif
