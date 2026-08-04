#include "Food.h"
#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

namespace seneca {

    Food::Food(const Food& src) : Billable(src) {
        m_ordered = src.m_ordered;
        m_child = src.m_child;
        ut.alocpy(m_customize, src.m_customize);
    }

    Food& Food::operator=(const Food& src) {
        if (this != &src) {
            Billable::operator=(src);
            m_ordered = src.m_ordered;
            m_child = src.m_child;
            ut.alocpy(m_customize, src.m_customize);
        }
        return *this;
    }

    Food::~Food() {
        delete[] m_customize;
        m_customize = nullptr;
    }

    double Food::price() const {
        if (ordered() && m_child) {
            return Billable::price() / 2.0;
        }
        return Billable::price();
    }

    bool Food::ordered() const {
        return m_ordered;
    }

    bool Food::order() {
        Menu foodSizeMenu("Food Size Selection", "Back", 3, 3);
        foodSizeMenu << "Adult" << "Child";

        size_t selection = foodSizeMenu.select();
        if (selection == 1) { // Adult
            m_child = false;
            m_ordered = true;
        } else if (selection == 2) { // Child
            m_child = true;
            m_ordered = true;
        } else { // Back
            m_child = false;
            m_ordered = false;
            delete[] m_customize;
            m_customize = nullptr;
            return false;
        }

        std::cout << "Special instructions\n> ";
        char customBuf[1024]{};
        std::cin.getline(customBuf, 1024);

        if (customBuf[0] == '\0' || ut.isspace(customBuf)) {
            delete[] m_customize;
            m_customize = nullptr;
        } else {
            ut.alocpy(m_customize, customBuf);
        }

        return true;
    }

    std::ostream& Food::print(std::ostream& ostr) const {
        const char* itemName = (const char*)*this;
        size_t len = 0;
        if (itemName) {
            while (itemName[len] && len < 25) {
                ostr << itemName[len];
                len++;
            }
        }
        for (size_t i = len; i < 28; i++) {
            ostr << '.';
        }

        if (!ordered()) {
            ostr << ".....";
        } else {
            if (m_child) {
                ostr << "Child";
            } else {
                ostr << "Adult";
            }
        }

        ostr.setf(std::ios::fixed);
        ostr.precision(2);
        ostr.setf(std::ios::right, std::ios::adjustfield);
        ostr.width(7);
        ostr << price();

        if (m_customize && &ostr == &std::cout) {
            ostr << " >> ";
            for (size_t i = 0; i < 30 && m_customize[i] != '\0'; i++) {
                ostr << m_customize[i];
            }
        }

        return ostr;
    }

    std::ifstream& Food::read(std::ifstream& file) {
        char nameBuf[256]{};
        double priceVal = 0.0;

        if (file.getline(nameBuf, 256, ',')) {
            file >> priceVal;
            if (file) {
                file.ignore(10000, '\n');
                name(nameBuf);
                Billable::price(priceVal);
                m_child = false;
                m_ordered = false;
                delete[] m_customize;
                m_customize = nullptr;
            }
        }
        return file;
    }

}