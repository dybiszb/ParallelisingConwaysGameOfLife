
#include "io.h"

cgol::GameGridSharedPtrT cgol::loadGridFromFile(const std::string &path) {
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
    while (std::getline(infile, line)) {
        if (line.empty())
            continue;

        std::stringstream lineStream(line);
        int value;
        int entriesCounter = 0;
        while (lineStream >> value) {
            inputEntries.push_back(value);
            entriesCounter++;
        }

        if (entriesCounter != gridWidth) {
            throw std::runtime_error("Wrong file structure: " + path);
        }

    }
    return std::make_shared<cgol::GameGrid>(inputEntries, gridWidth,
                                            gridHeight);
}

void cgol::dumpGameHistory(const StepsHistoryT &steps,
                           const std::string &path) {
    std::ofstream myfile;
    myfile.open(path);

    const int firstGridWidth = steps[0]->getWidth();
    const int firstGridHeight = steps[0]->getHeight();

    // Dump dimensions
    myfile << firstGridWidth << "\n";
    myfile << firstGridHeight << "\n";

    for (const auto &game : steps) {
        myfile << "\n";

        // Check for dimensions consistency
        const int gameHeight = game->getHeight();
        if (game->getWidth() != firstGridWidth ||
            gameHeight != firstGridHeight) {
            throw std::logic_error(
                    "Error dumping to file - inconsistent dimensions");
        }

        // Dump grid
        for (int row = 0; row < gameHeight; ++row) {
            myfile << game->getRowAsString(row) << "\r\n";
        }
    }

    myfile.close();
}
