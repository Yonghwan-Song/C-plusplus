/**********************************************************
 * Name: Yonghwan Song
 * Student ID: 135458198
 * Seneca email: ysong115@myseneca.ca
 * Section: NDD
 * Completion Date: 8.8
  **********************************************************/
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
		/////////////////////////////////////////////////////////<-----------------------I got the idea that I should write these together and delete means I don't have to define in implementation file
		MenuItem(const MenuItem&) = delete;					   //<-----------------------So, I deleted the definition of copy&assignment operation in the implementation file.
		MenuItem& operator=(const MenuItem& _item) = delete;   //                        I got this idea from professor Andrei Sajeniouk.
		/////////////////////////////////////////////////////////						And the link is here https://www.youtube.com/watch?v=3VuuWGZQlDE&feature=youtu.be. 
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
		Menu(const Menu&);//<-------------------------------This also I added after watching the video.
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
