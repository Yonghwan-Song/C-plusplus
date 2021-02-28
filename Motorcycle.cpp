#include <iostream>
#include "Motorcycle.h"
using namespace std;

namespace sdds
{
	Motorcycle::Motorcycle() : m_sidecar(false) {
	}

	Motorcycle::Motorcycle(const char* _LicensePlate, const char* _MakeAndModel) : Vehicle(_LicensePlate, _MakeAndModel) {
		if (isEmpty()) m_sidecar = false;
		else m_sidecar = false;
	}

	std::istream& Motorcycle::read(std::istream& istr) {
		if (isCsv()) {
			Vehicle::read(istr);
			istr >> m_sidecar;
			istr.ignore(2000, '\n');
		}
		else {
			cout << endl << "Motorcycle information entry" << endl;
			Vehicle::read(istr);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
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
				m_sidecar = true;
			}
		}
		return istr;
	}

	std::ostream& Motorcycle::write(std::ostream& ostr) const {
		if (isEmpty()) {
			ostr << "Invalid Motorcycle Object" << endl;
		}
		else if (isCsv()) {
			ostr << "M,";
			Vehicle::write(ostr);
			ostr << m_sidecar << endl;
		}
		else {
			ostr << "Vehicle type: Motorcycle" << endl;
			Vehicle::write(ostr);
			if (m_sidecar) ostr << "With Sidecar" << endl;
		}

		return ostr;
	}
}