#include "barista.h"
#include <iostream>
#include <fstream>

void loadBaristasFromFile(Barista baristas[], int& baristaCount, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file " << filename << "\n";
        return;
    }

    baristaCount = 0;
    while (inFile >> baristas[baristaCount].baristaId) {
        inFile.ignore();
        std::getline(inFile, baristas[baristaCount].name, ',');
        inFile >> baristas[baristaCount].shiftNumber;
        inFile.ignore();
        inFile >> baristas[baristaCount].completedOrders;
        inFile.ignore();
        std::getline(inFile, baristas[baristaCount].status, ',');
        baristas[baristaCount].ordersInProgress = 0;
        ++baristaCount;
    }

    inFile.close();
}

void saveBaristasToFile(const Barista baristas[], int baristaCount, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Unable to open file " << filename << "\n";
        return;
    }

    for (int i = 0; i < baristaCount; ++i) {
        outFile << baristas[i].baristaId << ","
            << baristas[i].name << ","
            << baristas[i].shiftNumber << ","
            << baristas[i].completedOrders << ","
            << baristas[i].status << "\n";
    }

    outFile.close();
}

void addBarista(Barista baristas[], int& baristaCount) {
    if (baristaCount >= 100) {
        std::cerr << "Max num of baristas reached\n";
        return;
    }

    Barista newBarista;
    newBarista.baristaId = baristaCount + 1;
    std::cout << "Enter barista name: ";
    std::cin.ignore();
    std::getline(std::cin, newBarista.name);
    std::cout << "Enter shift number: ";
    std::cin >> newBarista.shiftNumber;
    newBarista.completedOrders = 0;
    newBarista.status = "Active";
    newBarista.ordersInProgress = 0;

    baristas[baristaCount] = newBarista;
    ++baristaCount;

    std::cout << "Barista added successfully\n";
}

void listBaristas(const Barista baristas[], int baristaCount) {
    std::cout << "List of baristas:\n";
    for (int i = 0; i < baristaCount; ++i) {
        std::cout << "ID: " << baristas[i].baristaId
            << ", Name: " << baristas[i].name
            << ", Shift: " << baristas[i].shiftNumber
            << ", Completed Orders: " << baristas[i].completedOrders
            << ", Status: " << baristas[i].status
            << ", Orders In Progress: " << baristas[i].ordersInProgress << "\n";
    }
}

void rateBarista(Barista baristas[], int baristaCount) {
    int baristaId;
    std::cout << "Enter barista ID to rate: ";
    std::cin >> baristaId;

    for (int i = 0; i < baristaCount; ++i) {
        if (baristas[i].baristaId == baristaId) {
            int rating;
            std::cout << "Enter rating for " << baristas[i].name << " (1-5): ";
            std::cin >> rating;
            if (rating < 1 || rating > 5) {
                std::cerr << "Invalid rating. Provide a rating between 1 and 5\n";
                return;
            }
            baristas[i].completedOrders += rating;
            std::cout << "Barista " << baristas[i].name << " rated successfully\n";
            return;
        }
    }

    std::cerr << "Barista with ID " << baristaId << " not found\n";
}

void updateBaristaOrdersStatus(int baristaId, int change, Barista baristas[], int baristaCount) {
    for (int i = 0; i < baristaCount; ++i) {
        if (baristas[i].baristaId == baristaId) {
            baristas[i].ordersInProgress += change;
            std::cout << "Barista " << baristas[i].name << " now has "
                << baristas[i].ordersInProgress << " orders in progress\n";
            return;
        }
    }
    std::cerr << "Barista with ID " << baristaId << " not found\n";
}

void assignOrderToBarista(int baristaId, int orderId, Barista baristas[], int baristaCount) {
    for (int i = 0; i < baristaCount; ++i) {
        if (baristas[i].baristaId == baristaId) {
            if (baristas[i].ordersInProgress < MAX_ORDERS) {
                baristas[i].assignedOrders[baristas[i].ordersInProgress] = orderId;
                baristas[i].ordersInProgress++;
                std::cout << "Order " << orderId << " assigned to barista " << baristas[i].name << ".\n";
                return;
            }
            else {
                std::cerr << "Barista " << baristas[i].name << " has too many orders in progress\n";
                return;
            }
        }
    }
    std::cerr << "Barista with ID " << baristaId << " not found\n";
}

bool isBaristaAvailable(const Barista& barista) {
    return barista.ordersInProgress < MAX_ORDERS;
}
