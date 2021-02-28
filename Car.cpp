/**********************************************************
 * Name: Yonghwan Song
 * Student ID: 135458198
 * Seneca email: ysong115@myseneca.ca
 * Section: NDD
 * Completion Date: 8.8
 ->I have done all the coding by myself and only copied the code that my
 professor provided to complete my workshops and assignments.
 **********************************************************/
#include <iostream>
#include "Car.h"
using namespace std;

namespace sdds
{
	Car::Car() : m_carwash(false) {
	}
	Car::Car(const char* _LicensePlate, const char* _MakeAndModel) : Vehicle(_LicensePlate, _MakeAndModel) {
		if (isEmpty()) m_carwash = false;
		else m_carwash = false;
	}
	std::istream& Car::read(std::istream& istr) {
		if (isCsv()) {
			Vehicle::read(istr);
			istr >> m_carwash;
			istr.ignore(2000, '\n');
		}
		else {
			cout << endl << "Car information entry" << endl;
			Vehicle::read(istr);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			char answer;
			char trailing = 'e';
			istr >> answer;
			trailing = istr.get();
			istr.putback(trailing);
			while (istr.fail()) {
				istr.clear();
				istr.ignore(2000, '\n');
				cout << "Invalid character, try again: ";
				istr >> answer;
				trailing = istr.get();
				istr.putback(trailing);
			}
			istr.ignore(2000, '\n');

			while ((answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n') ||
				trailing != '\n') {
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";

				istr >> answer;
				trailing = istr.get();
				istr.putback(trailing);
				while (istr.fail() == true) {
					istr.clear();
					istr.ignore(2000, '\n');
					cout << "Invalid character, try again: ";
					istr >> answer;
					trailing = istr.get();
					istr.putback(trailing);
				}
				istr.ignore(2000, '\n');
			}
			if (answer == 'y' || answer == 'Y') {
				m_carwash = true;
			}
		}
		return istr;
	}
	std::ostream& Car::write(std::ostream& ostr) const {
		if (isEmpty()) {
			ostr << "Invalid Car Object" << endl;
		}
		else if (isCsv()) {
			ostr << "C,";
			Vehicle::write(ostr);
			ostr << m_carwash << endl;
		}
		else {
			ostr << "Vehicle type: Car" << endl;
			Vehicle::write(ostr);
			if (m_carwash) ostr << "With Carwash" << endl;
			else ostr << "Without Carwash" << endl;
		}

		return ostr;
	}
}