#ifndef BARISTA_H
#define BARISTA_H

#include <string>

const int MAX_ORDERS = 100;

struct Barista {
    int baristaId;
    std::string name;
    int shiftNumber;
    int completedOrders;
    std::string status;
    int ordersInProgress;
    int assignedOrders[MAX_ORDERS];
};

void loadBaristasFromFile(Barista baristas[], int& baristaCount, const std::string& filename);
void saveBaristasToFile(const Barista baristas[], int baristaCount, const std::string& filename);
void addBarista(Barista baristas[], int& baristaCount);
void listBaristas(const Barista baristas[], int baristaCount);
void rateBarista(Barista baristas[], int baristaCount);
void updateBaristaOrdersStatus(int baristaId, int change, Barista baristas[], int baristaCount);
void assignOrderToBarista(int baristaId, int orderId, Barista baristas[], int baristaCount);
bool isBaristaAvailable(const Barista& barista);

#endif