#include <iostream>
#include "Ordering.h"
#include "Menu.h"

using namespace seneca;

int main() {
    Ordering ordering("drinks.csv", "foods.csv");

    if (!ordering) {
        std::cout << "Failed to open data files or the data files are corrupted!\n";
        return 1;
    }

    Menu mainMenu("Seneca Restaurant ", "End Program");
    mainMenu << "Order"
             << "Print Bill"
             << "Start a New Bill"
             << "List Foods"
             << "List Drinks";

    Menu orderMenu("Order Menu", "Back to main menu", 1);
    orderMenu << "Food"
              << "Drink";

    Menu confirmExitMenu("You have bills that are not saved, are you sue you want to exit?", "No");
    confirmExitMenu << "Yes";

    bool done = false;

    while (!done) {
        size_t mainChoice = mainMenu.select();

        switch (mainChoice) {
        case 1: { // Order
            bool orderDone = false;
            while (!orderDone) {
                size_t orderChoice = orderMenu.select();
                if (orderChoice == 1) {
                    ordering.orderFood();
                } else if (orderChoice == 2) {
                    ordering.orderDrink();
                } else {
                    orderDone = true; // Back to main menu
                }
            }
            break;
        }
        case 2: // Print Bill
            ordering.printBill();
            break;

        case 3: // Start a New Bill
            ordering.resetBill();
            break;

        case 4: // List Foods
            ordering.listFoods();
            break;

        case 5: // List Drinks
            ordering.listDrinks();
            break;

        case 0: // End Program
            if (ordering.hasUnsavedBill()) {
                size_t confirmChoice = confirmExitMenu.select();
                if (confirmChoice == 1) {
                    done = true; // User confirmed exit with unsaved bill
                }
            } else {
                done = true; // Exit directly if no unsaved bill
            }
            break;
        }
    }

    return 0;
}