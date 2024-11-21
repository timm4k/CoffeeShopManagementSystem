#ifndef DRINK_H
#define DRINK_H

#include <string>

struct Drink {
    std::string name;
    std::string size;
    float price;
    int availability;
};

void loadDrinksFromFile(Drink drinks[], int& drinkCount, const std::string& filename);
void saveDrinksToFile(const Drink drinks[], int drinkCount, const std::string& filename);
void displayMenu(const Drink drinks[], int drinkCount);
void addDrink(Drink drinks[], int& drinkCount);
void editDrink(Drink drinks[], int drinkCount);
void deleteDrink(Drink drinks[], int& drinkCount);

#endif
