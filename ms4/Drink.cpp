#include "Drink.h"
#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

namespace seneca {

    double Drink::price() const {
        if (!ordered()) {
            return Billable::price();
        }
        switch (m_size) {
        case 'S':
            return Billable::price() * 0.5;
        case 'M':
            return Billable::price() * 0.75;
        case 'L':
            return Billable::price();
        case 'X':
            return Billable::price() * 1.5;
        default:
            return Billable::price();
        }
    }

    bool Drink::ordered() const {
        return m_size == 'S' || m_size == 'M' || m_size == 'L' || m_size == 'X';
    }

    bool Drink::order() {
        Menu drinkSizeMenu("Drink Size Selection", "Back", 3, 3);
        drinkSizeMenu << "Small" << "Medium" << "Larg" << "Extra Large";

        size_t selection = drinkSizeMenu.select();
        switch (selection) {
            case 1:
                m_size = 'S';
                return true;
            case 2:
                m_size = 'M';
                return true;
            case 3:
                m_size = 'L';
                return true;
            case 4:
                m_size = 'X';
                return true;
            default:
                m_size = 0;
                return false;
        }
    }

    std::ostream& Drink::print(std::ostream& ostr) const {
        const char* itemName = (const char*)*this;
        int len = 0;
        if (itemName) {
            while (itemName[len] && len < 25) {
                ostr << itemName[len];
                len++;
            }
        }
        for (int i = len; i < 28; i++) {
            ostr << '.';
        }

        // 2. Size: "SML..", "MID..", "LRG..", "XLR..", or "....."
        if (!ordered()) {
            ostr << ".....";
        } else {
            switch (m_size) {
                case 'S': 
                    ostr << "SML..";
                    break;
                case 'M': 
                    ostr << "MID..";
                    break;
                case 'L': 
                    ostr << "LRG..";
                    break;
                case 'X': 
                    ostr << "XLR..";
                    break;
                default:  
                    ostr << ".....";
                    break;
            }
        }

        ostr.setf(std::ios::fixed);
        ostr.precision(2);
        ostr.setf(std::ios::right, std::ios::adjustfield);
        ostr.width(7);
        ostr << price();

        return ostr;
    }

    std::ifstream& Drink::read(std::ifstream& file) {
        char nameBuf[256]{};
        double priceVal = 0.0;

        if (file.getline(nameBuf, 256, ',')) {
            file >> priceVal;
            if (file) {
                file.ignore(10000, '\n');
                name(nameBuf);
                Billable::price(priceVal);
                m_size = 0;
            }
        }
        return file;
    }
}