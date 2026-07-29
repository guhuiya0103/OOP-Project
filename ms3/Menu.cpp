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

    Menu::Menu(const char* itemTitle, const char* exitOption, int numberIdt, int sizeIdt)
        : m_numberIdt(numberIdt),
        m_sizeIdt(sizeIdt),
        m_numMenuItems(0), 
        m_itemTitle(itemTitle,numberIdt,sizeIdt,-1),
        m_exitOption(exitOption,numberIdt,sizeIdt,0),
        m_selectionPrompt("> ",numberIdt,sizeIdt,-1){
            for(int i = 0; i < MaximumNumberOfMenuItems; i++){
                m_itemPointers[i]=nullptr;
            }
    }

    Menu& Menu::operator<<(const char* itemTitle){
        if(m_numMenuItems < MaximumNumberOfMenuItems){
            MenuItem* content = new MenuItem(itemTitle,m_numberIdt,m_sizeIdt,m_numMenuItems+1);
            m_itemPointers[m_numMenuItems] = content;
            m_numMenuItems++;
        }
        return *this;    
    }
    
    Menu::~Menu(){
        for(int i = 0; i < m_numMenuItems; i++){
            delete m_itemPointers[i];
            m_itemPointers[i] = nullptr;    
        }
    }

    size_t Menu::select() const{
        if(m_itemTitle){
            m_itemTitle.display() << std::endl;
        }
        for(int i = 0; i < m_numMenuItems; i++){
            if(m_itemPointers[i]!=nullptr){
                m_itemPointers[i]->display() << std::endl;
            }
        }
        m_exitOption.display() << std::endl;
        m_selectionPrompt.display();

        int userSelection = ut.getInt(0, m_numMenuItems);
        return userSelection;
        
    }

    size_t operator<<(std::ostream& ostr, const Menu& m){
        if(&ostr == &std::cout){
            size_t resultSelect = m.select();
            return resultSelect;
        }
        else{
            return 0;
        }       
    }
}