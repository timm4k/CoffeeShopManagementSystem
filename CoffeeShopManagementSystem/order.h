#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "barista.h"
#include "drink.h"

struct Order {
    int orderId;
    std::string customerName;
    Drink orderedDrink;
    Barista* assignedBarista;
    std::string status;
};

void updateOrderStatus(Order orders[], int orderCount, int orderId, const std::string& status, Barista baristas[], int baristaCount);
void updateBaristaOrdersStatus(int baristaId, int change, Barista baristas[], int baristaCount);
void addOrder(Order orders[], int& orderCount, const Drink drinks[], int drinkCount, Barista baristas[], int baristaCount);
void displayOrders(const Order orders[], int orderCount);
void deleteOrder(Order orders[], int& orderCount, int orderId);

#endif