#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
namespace sdds
{
	class Menu;

	class MenuItem
	{
		char* m_item_Name;
		MenuItem();
		MenuItem(const char*);
		std::ostream& display(std::ostream& os = std::cout) const;
		MenuItem(const MenuItem&) = delete;					   
		MenuItem& operator=(const MenuItem& _item) = delete;   
		~MenuItem();
	public:
		friend class Menu;
	};

	const int MAX_NO_OF_ITEMS = 10;
	class Menu
	{
		char* m_Menu_title;
		MenuItem* m_Arr_items[MAX_NO_OF_ITEMS];
		int m_NumOf_items;
		int m_indent;
		void clear();
	public:
		Menu();
		Menu(const char*, int _indent = 0);
		Menu(const Menu&);
		Menu& operator=(const Menu&);
		Menu& operator=(const char*);
		~Menu();
		void add(const char*);
		Menu& operator<<(const char*);
		void display() const;
		operator int() const;
		operator bool() const;
		bool isEmpty() const;
		int run() const;
	};

}
#endif // !SDDS_MENU_H
