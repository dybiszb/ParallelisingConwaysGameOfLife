#ifndef CONWAY_H
#define CONWAY_H

#include <iostream>
#include "game_grid.h"
#include "array"
#include "strategies.h"


namespace cgol {

    class ConwaysGameOfLife {
    public:
        /**
         * Specify initial grid for the game.
         *
         * @param inputGrid Grid with initial entries.
         */
        ConwaysGameOfLife(GameGridSharedPtrT &inputGrid);

        /**
         * Simulates Conway's Game of Life for specified number of steps.
         * Resulting grid at each step will be stored in vector and returned
         * for further processing. Please note that the procedure does not
         * modify the input grid, hence multiple strategies can be performed on
         * initial grid.
         *
         * @param strategy Strategy for simulation - see strategies.h.
         * @param steps    Number of the simulation's steps.
         *
         * @return Vector of grids from consecutive steps of the application.
         */
        const cgol::StepsHistorySharedPtrT
        run(const StrategyT &strategy, int steps);

    private:
        GameGridSharedPtrT m_inputGrid;
    };

    using GameSharedPtrT = std::shared_ptr<ConwaysGameOfLife>;
}


#endif
