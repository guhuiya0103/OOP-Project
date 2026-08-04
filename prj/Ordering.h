#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H

#include <iostream>
#include <fstream>
#include "constants.h"
#include "Food.h"
#include "Drink.h"
#include "Billable.h"

namespace seneca {
    class Ordering {
        size_t m_noOfFoods{0};
        size_t m_noOfDrinks{0};
        size_t m_noOfBillItems{0};
        size_t m_billSerialNo{1};

        Food* m_foodArray{nullptr};
        Drink* m_drinkArray{nullptr};
        Billable* m_billItems[MaximumNumberOfBillItems]{nullptr};

        void printBillTitle(std::ostream& ostr) const;
        void printTotals(std::ostream& ostr, double total) const;
        size_t countRecords(const char* file) const;

    public:
        Ordering(const char* drinkFileName, const char* foodFileName);
        Ordering(const Ordering&) = delete;
        Ordering& operator=(const Ordering&) = delete;
        ~Ordering();

        operator bool() const;
        size_t noOfBillItems() const;
        bool hasUnsavedBill() const;

        void listFoods() const;
        void listDrinks() const;
        void orderFood();
        void orderDrink();
        void printBill(std::ostream& ostr = std::cout) const;
        void resetBill();
    };

}

#endif // !SENECA_ORDERING_H