#include <iostream>
#include <fstream>
#include <string>
#include "rating.h"

float calculateAverageRating(const Rating& rating) {
    if (rating.count == 0) {
        std::cout << "No ratings available\n";
        return 0.0f;
    }

    int sum = 0;
    for (int i = 0; i < rating.count; ++i) {
        sum += rating.ratings[i];
    }

    return static_cast<float>(sum) / rating.count;
}

bool readRatingsFromFile(const std::string& filename, Rating& rating) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return false;
    }

    file >> rating.count;
    if (rating.count <= 0) {
        std::cerr << "Invalid number of ratings\n";
        return false;
    }

    rating.ratings = new int[rating.count];

    for (int i = 0; i < rating.count; ++i) {
        file >> rating.ratings[i];
    }

    file.close();
    return true;
}

int main() {
    Rating rating;

    if (!readRatingsFromFile("ratings.txt", rating)) {
        return 1;
    }

    float average = calculateAverageRating(rating);
    if (average > 0.0f) {
        std::cout << "Average rating: " << average << "\n";
    }

    delete[] rating.ratings;

    return 0;
}
