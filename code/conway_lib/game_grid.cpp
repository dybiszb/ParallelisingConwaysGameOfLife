#include "game_grid.h"

cgol::GameGrid::GameGrid(int gridWidth, int gridHeight, bool randomize)
        : m_width(gridWidth), m_height(gridHeight) {

    // Check input arguments
    checkGridDimensions(gridWidth, gridHeight);

    // Reserve space in memory for speedup
    int gridArea = gridWidth * gridHeight;
    m_entries.reserve(static_cast<unsigned long>(gridArea));

    // Initialize the entries
    if (randomize) initializeRandomRawEntries(m_entries, gridArea);
    else initializeRawEntriesWithZeros(m_entries, gridArea);
}

cgol::GameGrid::GameGrid(const cgol::GameGrid &grid) :
        m_width(grid.getWidth()), m_height(grid.getHeight()) {
    m_entries = grid.getRawEntries();
}

cgol::GameGrid::GameGrid(const cgol::GridRawEntries &rawEntries,
                         int gridWidth, int gridHeight)
        : m_width(gridWidth), m_height(gridHeight) {

    checkGridDimensions(gridWidth, gridHeight);
    if (rawEntries.size() / gridWidth != gridHeight ||
        rawEntries.size() / gridHeight != gridWidth) {
        throw std::runtime_error("Error: raw entry data has wrong dimensions");
    }

    m_entries = rawEntries;
}

int cgol::GameGrid::getWidth() const {
    return m_width;
}

int cgol::GameGrid::getHeight() const {
    return m_height;
}

void cgol::GameGrid::checkGridDimensions(int gridWidth, int gridHeight) {
    if (gridWidth > GRID_MAX_WIDTH || gridHeight > GRID_MAX_HEIGHT ||
        gridWidth < 0 || gridHeight < 0) {
        throw std::logic_error(
                "Wrong grid's dimensions. Width's interval is <0, " +
                std::to_string(GRID_MAX_WIDTH) +
                ">. Height's interval is <0, " +
                std::to_string(GRID_MAX_HEIGHT) + ">.");
    }
}

cgol::GridRawEntries cgol::GameGrid::getRawEntries() const {
    return m_entries;
}

int cgol::GameGrid::getEntry(int row, int col) {
    if (row < 0 || row >= m_height || col < 0 || col >= m_width) {
        return 0;
    } else {
        int index = row * m_height + col;
        return m_entries[index];
    }

}

void cgol::GameGrid::setEntry(int row, int col, int value) {
    if (value != 0 && value != 1) {
        throw std::runtime_error("GameGrid can only take values 0 or 1");
    }
    if(row < 0 || row >= m_height || col < 0 || col >= m_width) {
        throw std::runtime_error("ROw or column index is not correct.");
    }
    int index = row * m_height + col;
    m_entries[index] = value;
}

void cgol::GameGrid::print() {
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            std::cout << getEntry(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

bool cgol::GameGrid::operator==(const GameGrid &other) {
    bool widthCheck = m_width == other.getWidth();
    bool heightCheck = m_height == other.getHeight();

    GridRawEntries otherRaw = other.getRawEntries();
    for (int i = 0; i < m_width * m_height; ++i) {
        if (otherRaw[i] != m_entries[i]) return false;
    }

    return widthCheck && heightCheck;
}

