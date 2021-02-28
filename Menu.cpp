/**********************************************************
 * Name: Yonghwan Song
 * Student ID: 135458198
 * Seneca email: ysong115@myseneca.ca
 * Section: NDD
 * Completion Date: 8.8
 //Basically, I had already my code before watching the video, but my code had a abort??(I don't remember what the name of it was) error with caution window coming up on the screen.
 //Hence, I got some help from the video. And after changing some of header file I mentioned in the Menu.h, the problem was resolved.
 //I do not normally prefer detailed instruction but rather think by myself though my codes can look uglier. 
 //But, in this file, I kind of followed detailed instruction of the video, so it might look prettier than other codes in the other file.
 //So, I want you to consider this situation. Thank you!.
 **********************************************************/
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
	//Before watching the video, I did not use the initialization list. But I changed my code so that it looks a bit prettier.
	//My excuse is that I knew the concept before. However, 'm_Arr_items{ nullptr }' is what I didn't know how to use.
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Menu::Menu() :m_Menu_title(nullptr), m_Arr_items{ nullptr }, m_NumOf_items(0), m_indent(0) {											//
																																			//
	}																																		//
																																			//
	Menu::Menu(const char* _title, int _indent) : m_Menu_title(nullptr), m_Arr_items{ nullptr }, m_NumOf_items(0), m_indent(_indent) {		//
		*this = _title;																														//
	}																																		//
  	//I added this copy constructor after watching the video.																				//
	Menu::Menu(const Menu& _menu) : m_Menu_title(nullptr), m_Arr_items{ nullptr }, m_NumOf_items(0), m_indent(_menu.m_indent) {				//
		*this = _menu;																														//
	}																																		//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////<--------------In this part, my previous code that I got hint was much look complicated 
	Menu& Menu::operator=(const Menu& _menu) {						 //				  and I guess there was a 1 block of memory leak out of the previous version of this part.
		if (this != &_menu) {										 //				  In a nutshell, add~~~ part in the for loop and *this= ~~~; are what I couldn't think up.
			clear();										         //				  And, clear() before if was also not my idea. my previous one was separating deallocation of m_Arr_items and m_Menu_title.
			if (!_menu.isEmpty()) {                                  //				  
				*this = _menu.m_Menu_title;                          //
				for (int i = 0; i < _menu.m_NumOf_items; i++) {      //
					add(_menu.m_Arr_items[i]->m_item_Name);          //
				}                                                    //
				m_indent = _menu.m_indent;                           //
			}                                                        //
		}														     //
		return *this;											     //			
	}																 //
	///////////////////////////////////////////////////////////////////															
	
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
	//////////////////////////////////////////////////////<--------------------------- my previous one was like delete[] m_Arr_items[i]->m_item_Name;
			delete m_Arr_items[i];                      //                             But, I don't remember exactly since I changed this part so many times so that I fix the abort error.
			m_Arr_items[i] = nullptr;                   //							   But, after following the instruction in the video, I no more tried to change this part.
		}												//							   So, I can say I didn't know how and when the destructor of MenuItem is called accurately. 
    //////////////////////////////////////////////////////                             
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