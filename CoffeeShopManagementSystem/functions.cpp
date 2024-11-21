#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void addOrder(Order orders[], int& orderCount, const Drink drinks[], int drinkCount, Barista baristas[], int baristaCount) {
    if (orderCount < MAX_ORDERS) {
        Order newOrder;
        std::cout << "Enter customer name: ";
        std::getline(std::cin, newOrder.customerName);

        std::cout << "Enter order ID: ";
        std::cin >> newOrder.orderId;
        std::cin.ignore();

        std::cout << "Enter drink name: ";
        std::getline(std::cin, newOrder.orderedDrink.name);
        std::cout << "Enter size: ";
        std::getline(std::cin, newOrder.orderedDrink.size);

        bool drinkFound = false;
        for (int i = 0; i < drinkCount; i++) {
            if (drinks[i].name == newOrder.orderedDrink.name && drinks[i].size == newOrder.orderedDrink.size) {
                drinkFound = true;
                newOrder.orderedDrink.price = drinks[i].price;
                newOrder.orderedDrink.availability = drinks[i].availability;
                break;
            }
        }

        if (!drinkFound) {
            std::cout << "Drink not found in the menu\n";
            return;
        }

        std::cout << "Assign barista by ID: ";
        int baristaId;
        std::cin >> baristaId;

        bool baristaFound = false;
        for (int i = 0; i < baristaCount; i++) {
            if (baristas[i].baristaId == baristaId) {
                newOrder.assignedBarista = &baristas[i];
                baristaFound = true;
                break;
            }
        }

        if (!baristaFound) {
            std::cout << "Barista not found\n";
            return;
        }

        newOrder.status = "In Progress";
        orders[orderCount++] = newOrder;
        std::cout << "Order added successfully\n";
    }
    else {
        std::cout << "Order list is full\n";
    }
}

void updateOrderStatus(Order orders[], int orderCount, int orderId, const std::string& status, Barista baristas[], int baristaCount) {
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].orderId == orderId) {
            orders[i].status = status;

            if (orders[i].assignedBarista != nullptr) {
                if (status == "Completed") {
                    updateBaristaOrdersStatus(orders[i].assignedBarista->baristaId, -1, baristas, baristaCount);
                }
                else if (status == "In Progress") {
                    updateBaristaOrdersStatus(orders[i].assignedBarista->baristaId, 1, baristas, baristaCount);
                }
            }
            std::cout << "Order " << orderId << " status updated to " << status << ".\n";
            return;
        }
    }
    std::cout << "Order ID " << orderId << " not found\n";
}

void updateBaristaOrdersStatus(int baristaId, int change, Barista baristas[], int baristaCount) {
    for (int i = 0; i < baristaCount; ++i) {
        if (baristas[i].baristaId == baristaId) {
            baristas[i].ordersInProgress += change;
            std::cout << "Barista " << baristas[i].name << " now has " << baristas[i].ordersInProgress << " orders in progress\n";
            return;
        }
    }
    std::cout << "Barista with ID " << baristaId << " not found.\n";
}

void displayCafeStatistics(int orderCount, int baristaCount, int drinkCount, const Order orders[], const Barista baristas[], const Drink drinks[]) {
    std::cout << "Cafe Statistics:\n";
    std::cout << "----------------------------------\n";
    std::cout << "Total orders: " << orderCount << "\n";
    std::cout << "Total baristas: " << baristaCount << "\n";
    std::cout << "Total drinks available: " << drinkCount << "\n";
    std::cout << "----------------------------------\n";

    int completedOrders = 0;
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].status == "Completed") {
            ++completedOrders;
        }
    }
    std::cout << "Completed orders: " << completedOrders << "\n";
    std::cout << "Orders in progress: " << (orderCount - completedOrders) << "\n";
    std::cout << "----------------------------------\n";

    double totalDrinkPrice = 0.0;
    for (int i = 0; i < drinkCount; ++i) {
        totalDrinkPrice += drinks[i].price;
    }
    if (drinkCount > 0) {
        std::cout << "Average drink price: $" << (totalDrinkPrice / drinkCount) << "\n";
    }
    else {
        std::cout << "No drinks available to calculate average price\n";
    }
    std::cout << "----------------------------------\n";

    int maxOrders = 0;
    std::string topBaristaName;
    for (int i = 0; i < baristaCount; ++i) {
        if (baristas[i].ordersInProgress > maxOrders) {
            maxOrders = baristas[i].ordersInProgress;
            topBaristaName = baristas[i].name;
        }
    }
    if (!topBaristaName.empty()) {
        std::cout << "Barista with most orders: " << topBaristaName << " (" << maxOrders << " orders in progress)\n";
    }
    else {
        std::cout << "No baristas currently handling orders\n";
    }
    std::cout << "----------------------------------\n";
}

void saveOrdersToFile(const Order orders[], int orderCount, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < orderCount; ++i) {
            outFile << orders[i].orderId << ","
                << orders[i].customerName << ","
                << orders[i].orderedDrink.name << ","
                << orders[i].orderedDrink.size << ","
                << orders[i].orderedDrink.price << ","
                << orders[i].orderedDrink.availability << ","
                << orders[i].status << "\n";
        }
        outFile.close();
        std::cout << "Orders saved to file successfully\n";
    }
    else {
        std::cout << "Error opening file for saving orders\n";
    }
}

void loadOrdersFromFile(Order orders[], int& orderCount, const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            Order newOrder;
            std::getline(ss, newOrder.customerName, ',');
            ss >> newOrder.orderId;
            std::getline(ss, newOrder.orderedDrink.name, ',');
            std::getline(ss, newOrder.orderedDrink.size, ',');
            ss >> newOrder.orderedDrink.price;
            ss >> newOrder.orderedDrink.availability;
            std::getline(ss, newOrder.status, ',');

            orders[orderCount++] = newOrder;
        }
        inFile.close();
        std::cout << "Orders loaded from file successfully\n";
    }
    else {
        std::cout << "Error opening file for loading orders\n";
    }
}

