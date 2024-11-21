#include <iostream>
#include "order.h"

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
            std::cout << "Order " << orderId << " status updated to " << status << "\n";
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
    std::cout << "Barista with ID " << baristaId << " not found\n";
}

void addOrder(Order orders[], int& orderCount, const Drink drinks[], int drinkCount, Barista baristas[], int baristaCount) {
    int drinkChoice, sizeChoice, baristaChoice;

    std::cout << "Enter customer name: ";
    std::cin.ignore();
    std::getline(std::cin, orders[orderCount].customerName);

    std::cout << "Choose a drink:\n";
    for (int i = 0; i < drinkCount; ++i) {
        std::cout << i + 1 << ". " << drinks[i].name << " - $" << drinks[i].price << " (" << drinks[i].availability << " available)\n";
    }
    std::cin >> drinkChoice;
    if (drinkChoice < 1 || drinkChoice > drinkCount) {
        std::cerr << "Invalid drink choice\n";
        return;
    }
    orders[orderCount].orderedDrink = drinks[drinkChoice - 1];

    std::cout << "Choose size: \n1. Small\n2. Medium\n3. Large\n4. Extra Large\n";
    std::cin >> sizeChoice;
    if (sizeChoice == 1) {
        orders[orderCount].orderedDrink.size = "Small";
        orders[orderCount].orderedDrink.price = 75.00;
    }
    else if (sizeChoice == 2) {
        orders[orderCount].orderedDrink.size = "Medium";
        orders[orderCount].orderedDrink.price = 85.00;
    }
    else if (sizeChoice == 3) {
        orders[orderCount].orderedDrink.size = "Large";
        orders[orderCount].orderedDrink.price = 95.00;
    }
    else if (sizeChoice == 4) {
        orders[orderCount].orderedDrink.size = "Extra Large";
        orders[orderCount].orderedDrink.price = 105.00;
    }
    else {
        std::cout << "Invalid size choice, defaulting to Medium\n";
        orders[orderCount].orderedDrink.size = "Medium";
        orders[orderCount].orderedDrink.price = 85.00;
    }

    std::cout << "Assign to a barista:\n";
    for (int i = 0; i < baristaCount; ++i) {
        std::cout << i + 1 << ". " << baristas[i].name << " (" << baristas[i].status << ")\n";
    }
    std::cin >> baristaChoice;
    if (baristaChoice < 1 || baristaChoice > baristaCount) {
        std::cerr << "Invalid barista choice\n";
        return;
    }
    orders[orderCount].assignedBarista = &baristas[baristaChoice - 1];

    orders[orderCount].status = "In Progress";
    std::cout << "Order for " << orders[orderCount].customerName << " is placed and assigned to " << orders[orderCount].assignedBarista->name << "\n";

    ++orderCount;
}

void displayOrders(const Order orders[], int orderCount) {
    std::cout << "Orders List:\n";
    for (int i = 0; i < orderCount; ++i) {
        std::cout << "Order ID: " << orders[i].orderId << ", Customer: " << orders[i].customerName
            << ", Drink: " << orders[i].orderedDrink.name << " (" << orders[i].orderedDrink.size << ")"
            << ", Status: " << orders[i].status << "\n";
    }
}

void deleteOrder(Order orders[], int& orderCount, int orderId) {
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].orderId == orderId) {
            for (int j = i; j < orderCount - 1; ++j) {
                orders[j] = orders[j + 1];
            }
            --orderCount;
            std::cout << "Order ID " << orderId << " has been deleted\n";
            return;
        }
    }
    std::cout << "Order ID " << orderId << " not found\n";
}
