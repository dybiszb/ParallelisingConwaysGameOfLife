#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch.hpp>
#include "conway.h"

TEST_CASE("ConwaysGameOfLife", "[conway_lib]") {
    size_t gridWidth = 3;
    size_t gridHeight = 3;
    cgol::GameGridSharedPtrT grid = std::make_shared<cgol::GameGrid>(gridWidth,
                                                                     gridHeight);
    cgol::ConwaysGameOfLife game(grid);

    SECTION("Constructor") {
        cgol::GameGridSharedPtrT nullGame;
        REQUIRE_THROWS_AS(cgol::ConwaysGameOfLife(nullGame),
                          std::runtime_error);
    }

    SECTION("Run Nullptr Strategy") {
        REQUIRE_THROWS_AS(game.run(nullptr, 1), std::runtime_error);
    }

    SECTION("Run Negative Steps") {
        REQUIRE_THROWS_AS(game.run(cgol::strategyCPU, -1), std::runtime_error);
    }

    SECTION("Strategy CPU - Game Logic Blink Oscillator") {
        std::vector<int> oscillator =
                {0, 0, 0, 0, 0,
                 0, 0, 1, 0, 0,
                 0, 0, 1, 0, 0,
                 0, 0, 1, 0, 0,
                 0, 0, 0, 0, 0};

        cgol::GameGridSharedPtrT oscillatorGrid = std::make_shared<cgol::GameGrid>(
                oscillator, 5, 5);
        cgol::ConwaysGameOfLife oscillatorGame(oscillatorGrid);

        const cgol::StepsHistorySharedPtrT history = oscillatorGame.run(
                cgol::strategyCPU, 2);

        // Consistency with input grid
        REQUIRE(*history[0].get() == *oscillatorGrid.get());

        // First Step Check
        REQUIRE(history[1]->getEntry(1, 2) == 0);
        REQUIRE(history[1]->getEntry(2, 2) == 1);
        REQUIRE(history[1]->getEntry(3, 2) == 0);
        REQUIRE(history[1]->getEntry(2, 1) == 1);
        REQUIRE(history[1]->getEntry(2, 3) == 1);

        // Oscillation Check
        REQUIRE(*history[2].get() == *oscillatorGrid.get());
    }
}

