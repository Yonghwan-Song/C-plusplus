#include <iostream>
#include "Utils.h"
using namespace std;
namespace sdds
{
	void indentation(int _indent)
	{
		for (int j = 0; j < 4 * _indent; j++)
		{
			cout << " ";
		}
	}

}