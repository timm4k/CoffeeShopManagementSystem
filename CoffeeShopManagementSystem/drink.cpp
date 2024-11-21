#include "drink.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void loadDrinksFromFile(Drink drinks[], int& drinkCount, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file " << filename << "\n";
        return;
    }

    drinkCount = 0;
    while (inFile >> std::ws && std::getline(inFile, drinks[drinkCount].name, ',')) {
        std::getline(inFile, drinks[drinkCount].size, ',');
        inFile >> drinks[drinkCount].price;
        inFile.ignore();
        inFile >> drinks[drinkCount].availability;
        inFile.ignore();
        ++drinkCount;
    }

    inFile.close();
}

void saveDrinksToFile(const Drink drinks[], int drinkCount, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Unable to open file " << filename << "\n";
        return;
    }

    for (int i = 0; i < drinkCount; ++i) {
        outFile << drinks[i].name << ","
            << drinks[i].size << ","
            << drinks[i].price << ","
            << drinks[i].availability << "\n";
    }

    outFile.close();
}

void displayMenu(const Drink drinks[], int drinkCount) {
    std::cout << std::setw(20) << std::left << "Name"
        << std::setw(10) << "Size"
        << std::setw(10) << "Price"
        << std::setw(15) << "Availability" << "\n";
    std::cout << std::string(55, '-') << "\n";

    for (int i = 0; i < drinkCount; ++i) {
        std::cout << std::setw(20) << drinks[i].name
            << std::setw(10) << drinks[i].size
            << std::setw(10) << std::fixed << std::setprecision(2) << drinks[i].price
            << std::setw(15) << drinks[i].availability << "\n";
    }
}

void addDrink(Drink drinks[], int& drinkCount) {
    if (drinkCount >= 100) {
        std::cerr << "Max num of drinks reached\n";
        return;
    }

    Drink newDrink;
    std::cout << "Enter drink name: ";
    std::cin.ignore();
    std::getline(std::cin, newDrink.name);

    std::cout << "Enter size (e.g., Small, Medium, Large): ";
    std::getline(std::cin, newDrink.size);

    std::cout << "Enter price: ";
    while (!(std::cin >> newDrink.price) || newDrink.price <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a positive price: ";
    }

    std::cout << "Enter availability (number of servings): ";
    while (!(std::cin >> newDrink.availability) || newDrink.availability < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a non-negative num: ";
    }

    drinks[drinkCount] = newDrink;
    ++drinkCount;

    std::cout << "Drink added successfully\n";
}

void editDrink(Drink drinks[], int drinkCount) {
    std::string drinkName;
    std::cout << "Enter the name of the drink to edit: ";
    std::cin.ignore();
    std::getline(std::cin, drinkName);

    for (int i = 0; i < drinkCount; ++i) {
        if (drinks[i].name == drinkName) {
            std::cout << "Editing " << drinks[i].name << " (" << drinks[i].size << "):\n";
            std::cout << "Enter new price: ";
            while (!(std::cin >> drinks[i].price) || drinks[i].price <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a positive price: ";
            }

            std::cout << "Enter new availability: ";
            while (!(std::cin >> drinks[i].availability) || drinks[i].availability < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a non-negative num: ";
            }

            std::cout << "Drink updated successfully\n";
            return;
        }
    }

    std::cerr << "Drink not found\n";
}

void deleteDrink(Drink drinks[], int& drinkCount) {
    std::string drinkName;
    std::cout << "Enter the name of the drink to delete: ";
    std::cin.ignore();
    std::getline(std::cin, drinkName);

    for (int i = 0; i < drinkCount; ++i) {
        if (drinks[i].name == drinkName) {
            for (int j = i; j < drinkCount - 1; ++j) {
                drinks[j] = drinks[j + 1];
            }
            --drinkCount;
            std::cout << "Drink deleted successfully\n";
            return;
        }
    }

    std::cerr << "Drink not found\n";
}
