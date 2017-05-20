#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace cgol {
    /**
     * Specified vector will be filled with provided number of random values
     * (0s and 1s).
     *
     * @param rawEntries Entries to be filled.
     * @param n          Number of entries to filled.
     */
    void initializeRandomRawEntries(std::vector<int>& rawEntries, int n);

    /**
     * Specified vector will be filled with provided number of 0s.
     *
     * @param rawEntries Entries to be filled.
     * @param n          Number of entries to filled.
     */
    void initializeRawEntriesWithZeros(std::vector<int>& rawEntries, int n);
}

#endif
