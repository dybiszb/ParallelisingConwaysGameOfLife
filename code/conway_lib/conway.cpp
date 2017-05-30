#include "conway.h"

cgol::ConwaysGameOfLife::ConwaysGameOfLife(GameGridSharedPtrT &inputGrid) {
    if(inputGrid.get() == nullptr) {
        throw std::runtime_error("Error: input grid is nullptr");
    }
    m_inputGrid = inputGrid;
}

const cgol::StepsHistoryT
cgol::ConwaysGameOfLife::run(const cgol::StrategyT &strategy, int steps) {
    if(strategy == nullptr) {
        throw std::runtime_error("Error: inout strategy is nullptr");
    }
    if(steps < 0) {
        throw std::runtime_error("Error: number of steps is negative");
    }

    return strategy(m_inputGrid, steps);
}
