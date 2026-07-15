#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"

namespace seneca {
 
   class MenuItem{
   private:
      char* m_title;
      int m_numberIdt;
      int m_sizeIdt;
      int m_rowNum;

      MenuItem(const char* title, int numberIdt, int sizeIdt,int rowNum);
      MenuItem(const MenuItem& item)=delete;
      MenuItem& operator=(const MenuItem& item)=delete;
      ~MenuItem();

      operator bool() const;
      std::ostream& display(std::ostream& ostr=std::cout) const;
      
      friend class Menu;
   };
   class Menu{
      int m_numberIdt;
      int m_sizeIdt;
      int m_numMenuItems;
      MenuItem m_itemTitle;
      MenuItem m_exitOption;
      MenuItem m_selectionPrompt;
      MenuItem* m_itemPointers[MaximumNumberOfMenuItems];

   public:
      Menu(const char* itemTitle, const char* exitOption = "Exit", int numberIdt = 0 , int sizeIdt = 3);
      Menu& operator<<(const char*);
      ~Menu();
      Menu(const Menu&) = delete;
      Menu& operator=(const Menu&) = delete;
      size_t select() const;
      int getInt();
      int getInt(int min, int max);
   };
   size_t operator<<(std::ostream& ostr, const Menu& m);
}



#endif // !SENECA_CONSTANTS_H


