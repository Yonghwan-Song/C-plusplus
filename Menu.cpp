#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
	MenuItem::MenuItem() {
		m_item_Name = nullptr;
	}

	MenuItem::MenuItem(const char* _item) : m_item_Name(nullptr) {
		if (_item != nullptr) {
			m_item_Name = new char[strlen(_item) + 1];
			strcpy(m_item_Name, _item);
		}
	}

	std::ostream& MenuItem::display(std::ostream& os) const {
		if (m_item_Name != nullptr) {
			os << m_item_Name << endl;
		}
		return os;
	}

	MenuItem::~MenuItem() {
		delete[] m_item_Name;
		m_item_Name = nullptr;
	}
	
	Menu::Menu() :m_Menu_title(nullptr), m_Arr_items{ nullptr }, m_NumOf_items(0), m_indent(0) {											
																																			
	}																																		
																																			
	Menu::Menu(const char* _title, int _indent) : m_Menu_title(nullptr), m_Arr_items{ nullptr }, m_NumOf_items(0), m_indent(_indent) {		
		*this = _title;																														
	}																																		
  	//I added this copy constructor after watching the video.																				
	Menu::Menu(const Menu& _menu) : m_Menu_title(nullptr), m_Arr_items{ nullptr }, m_NumOf_items(0), m_indent(_menu.m_indent) {				
		*this = _menu;																														
	}																																		

	Menu& Menu::operator=(const Menu& _menu) {						 
		if (this != &_menu) {										 
			clear();										         
			if (!_menu.isEmpty()) {                                  				  
				*this = _menu.m_Menu_title;                          
				for (int i = 0; i < _menu.m_NumOf_items; i++) {      
					add(_menu.m_Arr_items[i]->m_item_Name);          
				}                                                    
				m_indent = _menu.m_indent;                           
			}                                                        
		}														     
		return *this;											     			
	}																 
																
	Menu& Menu::operator=(const char* _menu_Title) {			
		if (_menu_Title != nullptr) {							
			delete[] m_Menu_title;								
			m_Menu_title = new char[strlen(_menu_Title) + 1];   
			strcpy(m_Menu_title, _menu_Title);					
		}														
		else {													
			this->clear();										
		}														
																
		return *this;											
	}

	void Menu::add(const char* _MenuItem) {

		if (!isEmpty() && m_NumOf_items < MAX_NO_OF_ITEMS) {

			if (_MenuItem != nullptr) {
				m_Arr_items[m_NumOf_items] = new MenuItem;
				m_Arr_items[m_NumOf_items]->m_item_Name = new char[strlen(_MenuItem) + 1];
				strcpy(m_Arr_items[m_NumOf_items]->m_item_Name, _MenuItem);
				m_NumOf_items++;
			}
			else {
				clear();
			}
		}
	}

	Menu& Menu::operator<<(const char* _MenuItem) {
		add(_MenuItem);
		return *this;
	}

	int Menu::run() const {
		int choice;

		display();

		if (m_NumOf_items != 0) {
			cin >> choice;
			while (cin.fail() == true) {
				cin.clear();
				cin.ignore(2000, '\n');
				cout << "Invalid Integer, try again: ";
				cin >> choice;
			}
			cin.ignore(2000, '\n');

			while (!(choice >= 1 && choice <= m_NumOf_items)) {
				cout << "Invalid selection, try again: ";

				cin >> choice;
				while (cin.fail() == true) {
					cin.clear();
					cin.ignore(2000, '\n');
					cout << "Invalid Integer, try again: ";
					cin >> choice;
				}
				cin.ignore(2000, '\n');
			}
		}
		else
			choice = 0;

		return choice;
	}

	
	
	void Menu::clear() {								
		for (int i = 0; i < m_NumOf_items; i++) {       
			delete m_Arr_items[i];                      
			m_Arr_items[i] = nullptr;                   
		}												
    
		delete[] m_Menu_title;                          
		m_Menu_title = nullptr;                         
		m_NumOf_items = 0;                              
	}                                                   
	
	Menu::operator bool() const {
		return m_Menu_title != nullptr ? true : false;
	}

	bool Menu::isEmpty() const {
		return m_Menu_title == nullptr ? true : false;
	}

	void Menu::display() const {
		if (isEmpty()) {
			cout << "Invalid Menu!" << endl;
		}
		else if (m_NumOf_items == 0) {
			indentation(m_indent);
			cout << m_Menu_title << endl;
			cout << "No Items to display!" << endl;
		}
		else {
			indentation(m_indent);
			cout << m_Menu_title << endl;

			for (int i = 0; i < m_NumOf_items; i++) {
				indentation(m_indent);
				cout << i + 1 << "- ";
				m_Arr_items[i]->display();
			}
			indentation(m_indent);
			cout << "> ";
		}
	}

	Menu::operator int() const {
		return run();
	}

	Menu::~Menu() {
		clear();
	}
}