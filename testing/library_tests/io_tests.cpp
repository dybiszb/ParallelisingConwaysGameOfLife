#include <catch.hpp>
#include <iostream>
#include "io.h"


TEST_CASE("Input Output Test", "[conway_lib]") {
    std::vector<int> generalRawData = {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 0, 0, 0,
            0, 1, 1, 0, 0, 1, 1, 0,
            0, 1, 0, 0, 0, 0, 1, 0,
            0, 0, 1, 0, 0, 1, 0, 0,
            1, 0, 1, 0, 0, 1, 0, 1,
            1, 1, 0, 0, 0, 0, 1, 1,
    };
    cgol::GameGrid generalGame(generalRawData, 8, 7);

    SECTION("Loading From File - Correct Standard Input") {
        cgol::GameGrid loaded = cgol::loadGridFromFile(
                "./resources/correct_file_structure_1.txt");
        REQUIRE(generalGame == loaded);
    }

    SECTION("Loading From FIle - Correct Messy Input") {
        cgol::GameGrid loaded = cgol::loadGridFromFile(
                "./resources/correct_file_structure_2.txt");
        REQUIRE(generalGame == loaded);
    }

    SECTION("Loading From File - Wrong File Structure") {
        REQUIRE_THROWS_AS(cgol::loadGridFromFile(
                "./resources/wrong_file_structure_1.txt"), std::runtime_error);
        REQUIRE_THROWS_AS(cgol::loadGridFromFile(
                "./resources/wrong_file_structure_2.txt"), std::runtime_error);
        REQUIRE_THROWS_AS(cgol::loadGridFromFile(
                "./resources/wrong_file_structure_3.txt"), std::runtime_error);
        REQUIRE_THROWS_AS(cgol::loadGridFromFile(
                "./resources/wrong_file_structure_4.txt"), std::runtime_error);
        REQUIRE_THROWS_AS(cgol::loadGridFromFile(
                "./resources/wrong_file_structure_5.txt"), std::runtime_error);
        REQUIRE_THROWS_AS(cgol::loadGridFromFile(
                "./resources/wrong_file_structure_6.txt"), std::runtime_error);
        REQUIRE_THROWS_AS(cgol::loadGridFromFile(
                "./resources/wrong_file_structure_7.txt"), std::runtime_error);
    }


}
