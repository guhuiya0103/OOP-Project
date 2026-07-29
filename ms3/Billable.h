#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H

#include <iostream>
#include <fstream>

namespace seneca {

    class Billable {
        char* m_name{ nullptr };
        double m_price{ 0.0 };

    protected:
        void price(double value);
        void name(const char* name);

    public:
        Billable();
        Billable(const char* name, double price);
        Billable(const Billable& src);
        Billable& operator=(const Billable& src);
        virtual ~Billable();

        virtual double price() const;

        // Pure virtual functions
        virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
        virtual bool order() = 0;
        virtual bool ordered() const = 0;
        virtual std::ifstream& read(std::ifstream& file) = 0;

        // Conversion operator
        operator const char* () const;
    };

    // Helper operator overloads
    double operator+(double money, const Billable& B);
    double& operator+=(double& money, const Billable& B);

}

#endif // !SENECA_BILLABLE_H