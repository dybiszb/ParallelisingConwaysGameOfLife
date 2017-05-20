
#include "io.h"

cgol::GameGrid cgol::loadGridFromFile(const std::string& path) {
    cgol::GridRawEntries inputEntries;
    std::string line;
    std::ifstream infile(path);

    // Get grid width
    int gridWidth;
    std::getline(infile, line);
    std::stringstream widthStream(line);
    widthStream >> gridWidth;

    // Get grid height
    int gridHeight;
    std::getline(infile, line);
    std::stringstream heightStream(line);
    heightStream >> gridHeight;

    // Get grid entries
    while (std::getline(infile, line))
    {
        if(line == "") continue;

        std::stringstream lineStream(line);
        int value;
        int entriesCounter = 0;
        while(lineStream >> value) {
            inputEntries.push_back(value);
            entriesCounter++;
        }

        if(entriesCounter != gridWidth) {
            throw std::runtime_error("Wrong file structure: " + path);
        }
    }

    return cgol::GameGrid(inputEntries, gridWidth,gridHeight);
}

void cgol::saveGridToFile(const cgol::GameGrid& grid, const std::string& path) {

}
