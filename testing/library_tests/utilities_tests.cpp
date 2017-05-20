#include <catch.hpp>
#include "utilities.h"

TEST_CASE("Utilities Test", "[conway_lib]") {

    SECTION("Raw Entries Random Initialization Exception") {
        int numberOfEntries = 100;
        std::vector<int> rawEntriesFilled(numberOfEntries, 0);
        REQUIRE_THROWS_AS(cgol::initializeRandomRawEntries(rawEntriesFilled,
                                                           numberOfEntries),
                          std::runtime_error);
    }


    SECTION("Raw Entries Initialization With Zeros Exception") {
        int numberOfEntries = 100;
        std::vector<int> rawEntriesFilled(numberOfEntries, 0);
        REQUIRE_THROWS_AS(cgol::initializeRawEntriesWithZeros(rawEntriesFilled,
                                                              numberOfEntries),
                          std::runtime_error);
    }

    SECTION("Raw Entries Initialization With Zeros Constructor") {
        int numberOfEntries = 4;
        std::vector<int> rawEntriesEmpty;
        cgol::initializeRawEntriesWithZeros(rawEntriesEmpty, numberOfEntries);
        for (const auto &entry : rawEntriesEmpty) REQUIRE(entry == 0);
    }
}