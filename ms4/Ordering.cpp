#include <iostream>
#include <fstream>
#include "Ordering.h"
#include "Menu.h"
#include "Utils.h"

namespace seneca {
void Ordering::printBillTitle(std::ostream& ostr) const {
        ostr << "Bill # ";
        ostr.width(3);
        ostr.fill('0');
        ostr.setf(std::ios::right, std::ios::adjustfield);
        ostr << m_billSerialNo;
        ostr.fill(' ');
        ostr << " =============================\n";
    }

    void Ordering::printTotals(std::ostream& ostr, double total) const {
        double tax = total * Tax;
        double grandTotal = total + tax;

        ostr.setf(std::ios::fixed);
        ostr.precision(2);

        ostr << "                     Total:";
        ostr.width(13);
        ostr << total << std::endl;

        ostr << "                     Tax:";
        ostr.width(15);
        ostr << tax << std::endl;

        ostr << "                     Total+Tax:";
        ostr.width(9);
        ostr << grandTotal << std::endl;

        ostr << "========================================\n";
    }

    size_t Ordering::countRecords(const char* file) const {
        size_t count = 0;
        if (file) {
            std::ifstream f(file);
            char ch;
            while (f.get(ch)) {
                if (ch == '\n') {
                    count++;
                }
            }
        }
        return count;
    }

    Ordering::Ordering(const char* drinkFileName, const char* foodFileName) {
        size_t drinkRecords = countRecords(drinkFileName);
        size_t foodRecords = countRecords(foodFileName);

        std::ifstream drinkFile(drinkFileName);
        std::ifstream foodFile(foodFileName);

        if (drinkRecords > 0 && foodRecords > 0 && drinkFile && foodFile) {
            m_drinkArray = new Drink[drinkRecords];
            m_foodArray = new Food[foodRecords];

            size_t drinksRead = 0;
            for (size_t i = 0; i < drinkRecords && drinkFile; i++) {
                if (m_drinkArray[i].read(drinkFile)) {
                    drinksRead++;
                }
            }

            size_t foodsRead = 0;
            for (size_t i = 0; i < foodRecords && foodFile; i++) {
                if (m_foodArray[i].read(foodFile)) {
                    foodsRead++;
                }
            }

            if (drinksRead != drinkRecords || foodsRead != foodRecords) {
                delete[] m_drinkArray;
                m_drinkArray = nullptr;
                delete[] m_foodArray;
                m_foodArray = nullptr;
                m_noOfDrinks = 0;
                m_noOfFoods = 0;
            } else {
                m_noOfDrinks = drinksRead;
                m_noOfFoods = foodsRead;
            }
        }

        m_billSerialNo = 1;
        m_noOfBillItems = 0;
        for (size_t i = 0; i < MaximumNumberOfBillItems; i++) {
            m_billItems[i] = nullptr;
        }
    }

    Ordering::~Ordering() {
        delete[] m_foodArray;
        m_foodArray = nullptr;
        delete[] m_drinkArray;
        m_drinkArray = nullptr;

        for (size_t i = 0; i < m_noOfBillItems; i++) {
            delete m_billItems[i];
            m_billItems[i] = nullptr;
        }
    }

    Ordering::operator bool() const {
        return m_drinkArray != nullptr && m_foodArray != nullptr;
    }

    size_t Ordering::noOfBillItems() const {
        return m_noOfBillItems;
    }

    bool Ordering::hasUnsavedBill() const {
        return m_noOfBillItems > 0;
    }

    void Ordering::listFoods() const {
        std::cout << "List Of Avaiable Meals\n";
        std::cout << "========================================\n";
        for (size_t i = 0; i < m_noOfFoods; i++) {
            m_foodArray[i].print(std::cout);
            std::cout << "\n";
        }
        std::cout << "========================================\n";
    }

    void Ordering::listDrinks() const {
        std::cout << "List Of Avaiable Drinks\n";
        std::cout << "========================================\n";
        for (size_t i = 0; i < m_noOfDrinks; i++) {
            m_drinkArray[i].print(std::cout);
            std::cout << "\n";
        }
        std::cout << "========================================\n";
    }

    void Ordering::orderFood() {
        Menu foodMenu("Food Menu", "Back to Order", 2);
        for (size_t i = 0; i < m_noOfFoods; i++) {
            foodMenu << (const char*)m_foodArray[i];
        }

        size_t selection = foodMenu.select();
        if (selection != 0 && m_noOfBillItems < MaximumNumberOfBillItems) {
            Food* food = new Food(m_foodArray[selection - 1]);
            if (food->order()) {
                m_billItems[m_noOfBillItems++] = food;
            } else {
                delete food;
            }
        }
    }

    void Ordering::orderDrink() {
        Menu drinkMenu("Drink Menu", "Back to Order", 2);
        for (size_t i = 0; i < m_noOfDrinks; i++) {
            drinkMenu << (const char*)m_drinkArray[i];
        }

        size_t selection = drinkMenu.select();
        if (selection != 0 && m_noOfBillItems < MaximumNumberOfBillItems) {
            Drink* drink = new Drink(m_drinkArray[selection - 1]);
            if (drink->order()) {
                m_billItems[m_noOfBillItems++] = drink;
            } else {
                delete drink;
            }
        }
    }

    void Ordering::printBill(std::ostream& ostr) const {
        double total = 0.0;
        printBillTitle(ostr);
        for (size_t i = 0; i < m_noOfBillItems; i++) {
            m_billItems[i]->print(ostr);
            ostr << "\n";
            total += m_billItems[i]->price();
        }
        printTotals(ostr, total);
    }

    void Ordering::resetBill() {
        char filename[100]{};
        ut.makeBillFileName(filename, m_billSerialNo);
        std::ofstream file(filename);
        if (file) {
            printBill(file);
        }
        std::cout << "Saved bill number " << m_billSerialNo << "\n";
        std::cout << "Starting bill number " << (m_billSerialNo + 1) << "\n";

        for (size_t i = 0; i < m_noOfBillItems; i++) {
            delete m_billItems[i];
            m_billItems[i] = nullptr;
        }
        m_billSerialNo++;
        m_noOfBillItems = 0;
    }

}