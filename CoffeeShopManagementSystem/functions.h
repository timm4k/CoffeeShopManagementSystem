#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "drink.h"
#include "order.h"
#include "barista.h"

const int MAX_DRINKS = 100;
const int MAX_ORDERS = 100;
const int MAX_BARISTAS = 10;

void loadDrinksFromFile(Drink drinks[], int& drinkCount, const std::string& filename);
void saveDrinksToFile(const Drink drinks[], int drinkCount, const std::string& filename);

void loadOrdersFromFile(Order orders[], int& orderCount, const std::string& filename);
void saveOrdersToFile(const Order orders[], int orderCount, const std::string& filename);

void loadBaristasFromFile(Barista baristas[], int& baristaCount, const std::string& filename);
void saveBaristasToFile(const Barista baristas[], int baristaCount, const std::string& filename);

void addDrink(Drink drinks[], int& drinkCount);
void editDrink(Drink drinks[], int drinkCount);
void deleteDrink(Drink drinks[], int& drinkCount);
void displayMenu(const Drink drinks[], int drinkCount);
void displayOrders(const Order orders[], int orderCount);

void addOrder(Order orders[], int& orderCount, const Drink drinks[], int drinkCount, Barista baristas[], int baristaCount);

void updateOrderStatus(Order orders[], int orderCount, int orderId, const std::string& status, Barista baristas[], int baristaCount);

void deleteOrder(Order orders[], int& orderCount, int orderId);

void addBarista(Barista baristas[], int& baristaCount);
void listBaristas(const Barista baristas[], int baristaCount);
void rateBarista(Barista baristas[], int baristaCount);

void displayCafeStatistics(int orderCount, int baristaCount, int drinkCount, const Order orders[], const Barista baristas[], const Drink drinks[]);

#endif
