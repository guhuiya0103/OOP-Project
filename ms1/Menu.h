#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>

namespace seneca {
    class MenuItem{
      private:
         char* m_title;
         int m_numberIdt;
         int m_sizeIdt;
         int m_rowNum;

      public:
         MenuItem(const char* title, int numberIdt, int sizeIdt,int rowNum);
         MenuItem(const MenuItem& item)=delete;
         MenuItem& operator=(const MenuItem& item)=delete;
         ~MenuItem();

         operator bool() const;
         std::ostream& display(std::ostream& ostr=std::cout) const;      
   };
}

#endif // !SENECA_CONSTANTS_H


