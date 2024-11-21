#include <iostream>
#include <fstream>
#include "drink.h"
#include "order.h"
#include "barista.h"
#include "functions.h"

const int MAX_DRINKS = 100;
const int MAX_ORDERS = 100;
const int MAX_BARISTAS = 10;

void showMainMenu() {
    std::cout << "\n=== Main Menu ===\n";
    std::cout << "1. View menu\n";
    std::cout << "2. Add a new drink\n";
    std::cout << "3. Edit a drink\n";
    std::cout << "4. Delete a drink\n";
    std::cout << "5. View orders\n";
    std::cout << "6. Add a new order\n";
    std::cout << "7. Update order status\n";
    std::cout << "8. Delete an order\n";
    std::cout << "9. Add a new barista\n";
    std::cout << "10. View barista statistics\n";
    std::cout << "11. Rate a barista\n";
    std::cout << "12. View cafe statistics\n";
    std::cout << "13. Exit\n";
}

int main() {
    Drink drinks[MAX_DRINKS];
    Order orders[MAX_ORDERS];
    Barista baristas[MAX_BARISTAS];
    int drinkCount = 0;
    int orderCount = 0;
    int baristaCount = 0;

    loadDrinksFromFile(drinks, drinkCount, "menu.txt");
    loadOrdersFromFile(orders, orderCount, "order.txt");
    loadBaristasFromFile(baristas, baristaCount, "barista.txt");

    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            displayMenu(drinks, drinkCount);
            break;
        case 2:
            addDrink(drinks, drinkCount);
            break;
        case 3:
            editDrink(drinks, drinkCount);
            break;
        case 4:
            deleteDrink(drinks, drinkCount);
            break;
        case 5:
            displayOrders(orders, orderCount);
            break;
        case 6:
            addOrder(orders, orderCount, drinks, drinkCount, baristas, baristaCount);
            break;
        case 7: {
            int orderId;
            std::string newStatus;
            std::cout << "Enter order ID to update: ";
            std::cin >> orderId;
            std::cout << "Enter new status (e.g., 'Completed', 'In Progress', 'Cancelled'): ";
            std::cin >> newStatus;
            updateOrderStatus(orders, orderCount, orderId, newStatus, baristas, baristaCount);
            break;
        }
        case 8: {
            int orderId;
            std::cout << "Enter order ID to delete: ";
            std::cin >> orderId;
            deleteOrder(orders, orderCount, orderId);
            break;
        }
        case 9:
            addBarista(baristas, baristaCount);
            break;
        case 10:
            listBaristas(baristas, baristaCount);
            break;
        case 11:
            rateBarista(baristas, baristaCount);
            break;
        case 12:
            displayCafeStatistics(orderCount, baristaCount, drinkCount, orders, baristas, drinks);
            break;
        case 13:
            running = false;
            break;
        default:
            std::cout << "Invalid option. Try again\n";
        }
    }

    saveDrinksToFile(drinks, drinkCount, "menu.txt");
    saveOrdersToFile(orders, orderCount, "order.txt");
    saveBaristasToFile(baristas, baristaCount, "barista.txt");

    std::cout << "Program terminated successfully...\n";
    return 0;
}
