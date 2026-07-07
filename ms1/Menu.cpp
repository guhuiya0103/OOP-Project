#include "Menu.h"
#include "constants.h"
#include "Utils.h"
#include <iostream>

namespace seneca{
    MenuItem::MenuItem(const char* title, int numberIdt, int sizeIdt,int rowNum){
        if(title==nullptr||ut.isspace(title)||sizeIdt>4||numberIdt>4||rowNum>(int)MaximumNumberOfMenuItems){
            m_title = nullptr;
            m_numberIdt = 0;
            m_sizeIdt = 0;
            m_rowNum = 0;
        }
        else{
            m_title = ut.alocpy(title);
            m_numberIdt = numberIdt;
            m_sizeIdt = sizeIdt;
            m_rowNum = rowNum;
        }
    }
   
    MenuItem::~MenuItem(){
        delete[] m_title;
        m_title = nullptr;
    }

    MenuItem::operator bool() const{
        if(m_title == nullptr && m_numberIdt == 0 && m_sizeIdt == 0 && m_rowNum == 0){
            return false;
        }
        else{
            return true;
        }
    }

    std::ostream& MenuItem::display(std::ostream& ostr) const{
        if(*this){
            int totalSpaces=m_numberIdt*m_sizeIdt;
            for(int i=0; i<totalSpaces; i++){
                ostr<<" ";
            }
            if(m_rowNum>=0){
                if(m_rowNum<10){
                    ostr<<" "<<m_rowNum<<"- ";
                }
                else{
                    ostr<<m_rowNum<<"- ";
                }
            }
            const char* firstLetter = m_title;
            while(*firstLetter&& ut.isspace(*firstLetter)){
                firstLetter++;
            }
            ostr<<firstLetter;
        }
        else{
            ostr<<"??????????";
        }
        return ostr;
    }
}
