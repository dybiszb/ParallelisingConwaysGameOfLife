#include <catch.hpp>
#include <iostream>
#include "game_grid.h"


TEST_CASE("GameGrid Class Test", "[conway_lib]") {
    int gridWidth = 64;
    int gridHeight = 64;
    cgol::GameGrid generalGame(gridWidth, gridHeight);
    cgol::GridRawEntries generalRawEntries = generalGame.getRawEntries();

    SECTION("Constructor With Randomization") {
        REQUIRE_THROWS_AS(cgol::GameGrid(-1, 1), std::logic_error);
        REQUIRE_THROWS_AS(cgol::GameGrid(1, -1), std::logic_error);
        REQUIRE_THROWS_AS(cgol::GameGrid(-1, -1), std::logic_error);
        REQUIRE_THROWS_AS(cgol::GameGrid(cgol::GRID_MAX_WIDTH + 1, 1), std::logic_error);
        REQUIRE_THROWS_AS(cgol::GameGrid(1, cgol::GRID_MAX_HEIGHT + 1), std::logic_error);
    }

    SECTION("Constructor With Zeros") {
        int gridWidth = 2;
        int gridHeight = 2;
        cgol::GameGrid game(gridWidth, gridHeight, false);
        cgol::GridRawEntries rawEntries = game.getRawEntries();

        for(const auto& entry : rawEntries) REQUIRE(entry == 0);
    }

    SECTION("Constructor From Raw Data - Dimensions") {
        std::vector<int> rawEntries(4, 0);
        REQUIRE_THROWS_AS(cgol::GameGrid(rawEntries, 1, 1), std::runtime_error);
        REQUIRE_NOTHROW(cgol::GameGrid(rawEntries, 4, 1));
        REQUIRE_NOTHROW(cgol::GameGrid(rawEntries, 1, 4));
        REQUIRE_NOTHROW(cgol::GameGrid(rawEntries, 2, 2));
    }

    SECTION("Constructor From Raw Data - Consistency") {
        std::vector<int> rawEntries = {1, 0, 1, 0};
        cgol::GameGrid rawGrid(rawEntries, 2, 2);
        cgol::GridRawEntries retrieved = rawGrid.getRawEntries();

        REQUIRE(retrieved[0] == rawEntries[0]);
        REQUIRE(retrieved[1] == rawEntries[1]);
        REQUIRE(retrieved[2] == rawEntries[2]);
        REQUIRE(retrieved[3] == rawEntries[3]);
    }

    SECTION("Entries Acquisition"){
        REQUIRE(generalGame.getWidth() == gridWidth);
        REQUIRE(generalGame.getHeight() == gridHeight);
        REQUIRE(generalRawEntries[5] == generalGame.getEntry(0, 5));
        REQUIRE(generalRawEntries[2 * gridWidth + 3] == generalGame.getEntry(2, 3));
    }

    SECTION("Entries Set Exceptions"){
        REQUIRE_THROWS_AS(generalGame.setEntry(2, 3, -1), std::runtime_error);
    }

    SECTION("Comparision Operator") {
        cgol::GameGrid otherCorrect(generalGame);
        REQUIRE(generalGame == otherCorrect);

        cgol::GridRawEntries incorrectRaw = generalGame.getRawEntries();
        incorrectRaw[3] = (incorrectRaw[3] == 1) ? 0 : 1;
        cgol::GameGrid otherIncorrect(incorrectRaw, gridWidth, gridHeight);
        REQUIRE(!(generalGame == otherIncorrect));
    }

}
