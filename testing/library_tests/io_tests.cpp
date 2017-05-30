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

    cgol::GameGridSharedPtrT generalGame1 = std::make_shared<cgol::GameGrid>(
            generalRawData, 8, 7);

    SECTION("Loading From File - Correct Standard Input") {
        cgol::GameGridSharedPtrT loaded = cgol::loadGridFromFile(
                "./resources/correct_file_structure_1.txt");
        REQUIRE(*generalGame1.get() == *loaded.get());
    }

    SECTION("Loading From File - Correct Messy Input") {
        cgol::GameGridSharedPtrT loaded = cgol::loadGridFromFile(
                "./resources/correct_file_structure_2.txt");
        REQUIRE(*generalGame1.get() == *loaded.get());
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

    SECTION("Dumping To File - Inconsistent Dimensions") {
        cgol::GameGridSharedPtrT game2 = std::make_shared<cgol::GameGrid>(
                generalRawData, 2, 28);
        cgol::StepsHistoryT history = {generalGame1, game2};
        REQUIRE_THROWS_AS(
                cgol::dumpGameHistory(history,
                                      "test_file_dumping_dim_inc.txt"),
                std::logic_error);
    }

    SECTION("Dump Then Load") {
        std::string fileToCheck = "test_load_dump.txt";
        cgol::StepsHistoryT history = {generalGame1};
        cgol::dumpGameHistory(history, fileToCheck);
        cgol::GameGridSharedPtrT loaded = cgol::loadGridFromFile(fileToCheck);
        REQUIRE(*loaded.get() == *generalGame1.get());
    }

}
