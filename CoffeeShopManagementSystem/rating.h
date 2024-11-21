#ifndef RATING_H
#define RATING_H

#include <string>

struct Rating {
    int* ratings;
    int count;
};

float calculateAverageRating(const Rating& rating);

bool readRatingsFromFile(const std::string& filename, Rating& rating);

#endif
