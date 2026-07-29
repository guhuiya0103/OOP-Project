#include "Billable.h"
#include "Utils.h"

namespace seneca {

    void Billable::price(double value) {
        m_price = value;
    }

    void Billable::name(const char* name) {
        ut.alocpy(m_name, name);
    }

    Billable::Billable() {
        m_name = nullptr;
        m_price = 0.0;
    }

    Billable::Billable(const char* name, double price) {
        m_price = price;
        ut.alocpy(m_name, name);
    }

    Billable::Billable(const Billable& src) {
        m_price = src.m_price;
        ut.alocpy(m_name, src.m_name);
    }

    Billable& Billable::operator=(const Billable& src) {
        m_price = src.m_price;
        ut.alocpy(m_name, src.m_name);
        return *this;
    }

    Billable::~Billable() {
        delete[] m_name;
        m_name = nullptr;
    }

    double Billable::price() const {
        return m_price;
    }

    Billable::operator const char* () const {
        return m_name;
    }

    double operator+(double money, const Billable& B) {
        return money + B.price();
    }

    double& operator+=(double& money, const Billable& B) {
        money += B.price();
        return money;
    }

}