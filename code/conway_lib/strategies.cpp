#include "strategies.h"

void
cgol::calculateStep(const GameGridSharedPtrT &prev, GameGridSharedPtrT &next,
                    int row, int col) {

    int aliveNeighbours = 0;
    aliveNeighbours += prev->getEntry(row - 1, col);
    aliveNeighbours += prev->getEntry(row + 1, col);
    aliveNeighbours += prev->getEntry(row - 1, col - 1);
    aliveNeighbours += prev->getEntry(row + 1, col + 1);
    aliveNeighbours += prev->getEntry(row, col - 1);
    aliveNeighbours += prev->getEntry(row, col + 1);
    aliveNeighbours += prev->getEntry(row - 1, col + 1);
    aliveNeighbours += prev->getEntry(row + 1, col - 1);

    bool isCellAlive = (prev->getEntry(row, col) == 1);
//    std::cout << "isCellAlive: " << isCellAlive << " aliveNeighbours: " << aliveNeighbours << std::endl;
    if (isCellAlive) {
        if((aliveNeighbours < 2 || aliveNeighbours > 3)) {
            next->setEntry(row, col, 0);
        } else {
            next->setEntry(row, col, 1);
        }

    }
    else if(aliveNeighbours == 3) {
        next->setEntry(row, col, 1);
    }
}

const cgol::StepsHistorySharedPtrT
cgol::strategyCPU(const cgol::GameGridSharedPtrT &inputGrid,
                  int steps) {

    GameGridSharedPtrT prev = std::make_shared<GameGrid>(*(inputGrid.get()));
    cgol::StepsHistorySharedPtrT stepsHistory;
    stepsHistory.push_back(prev);

    for (int i = 0; i < steps; ++i) {
        // Create a grid for next step
        GameGridSharedPtrT next = std::make_shared<GameGrid>(
                inputGrid->getWidth(), inputGrid->getHeight(), false);
//        std::cout << " step " << i << std::endl;
        // Update next step grid
        for (int row = 0; row < inputGrid->getHeight(); ++row) {
            for (int col = 0; col < inputGrid->getWidth(); ++col) {
                calculateStep(prev, next, row, col);
            }
        }
        // Temp debug
//        prev->print();

        // Save next step
        stepsHistory.push_back(next);
        prev = next;
    }

    return stepsHistory;
}
