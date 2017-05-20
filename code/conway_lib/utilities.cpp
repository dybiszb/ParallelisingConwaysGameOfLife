#include <stdexcept>
#include "utilities.h"

void cgol::initializeRandomRawEntries(std::vector<int>& rawEntries, int n) {
    if(rawEntries.size() != 0) {
        throw std::runtime_error("Raw entries already initialized.");
    }
    std::srand(unsigned(std::time(0)));
    for (size_t i = 0; i < n; ++i) rawEntries.push_back(i % 2);
    std::random_shuffle(rawEntries.begin(), rawEntries.end());
}

void cgol::initializeRawEntriesWithZeros(std::vector<int>& rawEntries, int n){
    if(rawEntries.size() != 0) {
        throw std::runtime_error("Raw entries already initialized.");
    }
    std::vector<int> zeros(n, 0);
    rawEntries.insert(rawEntries.end(), zeros.begin(), zeros.end());
}