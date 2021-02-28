/**********************************************************
 * Name: Yonghwan Song
 * Student ID: 135458198
 * Seneca email: ysong115@myseneca.ca
 * Section: NDD
 * Completion Date: 8.8
 ->I have done all the coding by myself and only copied the code that my
 professor provided to complete my workshops and assignments.
 **********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "Vehicle.h"
using namespace std;

namespace sdds
{
	Vehicle::Vehicle() : ReadWritable(),
		m_MakeAndModel(nullptr), m_ParkingSpot_Num(-1) {
		strcpy(m_LicensePlate, "");
	}

	Vehicle::Vehicle(const char* _LicensePlate, const char* _MakeAndModel) : ReadWritable(),
		m_MakeAndModel(nullptr), m_ParkingSpot_Num(-1) {
		if (_LicensePlate != nullptr && _LicensePlate[0] != '\0' && strlen(_LicensePlate) <= MAX_CHAR &&
			_MakeAndModel != nullptr && _MakeAndModel[0] != '\0' && strlen(_MakeAndModel) >= 2) {

			strcpy(m_LicensePlate, _LicensePlate);
			m_MakeAndModel = new char[strlen(_MakeAndModel) + 1];
			strcpy(m_MakeAndModel, _MakeAndModel);
			m_ParkingSpot_Num = 0;
		}
		else strcpy(m_LicensePlate, "");
	}

	Vehicle::~Vehicle() {
		delete[] m_MakeAndModel;
	}
	int Vehicle::getParkingSpot() const {
		return m_ParkingSpot_Num;
	}
	void Vehicle::setParkingSpot(int _SpotNumber) {
		if (_SpotNumber >= 0) {
			m_ParkingSpot_Num = _SpotNumber;
		}
		else setEmpty();
	}

	bool Vehicle::operator==(const char* _LicensePlate) const {
		bool result = true;

		if (isEmpty() || _LicensePlate == nullptr || _LicensePlate[0] == '\0') {
			result = false;
		}
		else if (strlen(m_LicensePlate) == strlen(_LicensePlate)) {

			for (unsigned int i = 0; i < strlen(m_LicensePlate) && result; i++) {
				result = (toupper(m_LicensePlate[i]) == toupper(_LicensePlate[i]));
			}
		}
		else result = false;

		return result;
	}

	bool Vehicle::operator==(const Vehicle& _a_Vehicle) const {
		bool result = true;
		if (isEmpty() || _a_Vehicle.isEmpty()) {
			result = false;
		}
		else if (strlen(m_LicensePlate) == strlen(_a_Vehicle.getLicensePlate())) {
			for (unsigned int i = 0; i < strlen(m_LicensePlate) && result; i++) {
				result = (toupper(m_LicensePlate[i]) == toupper(_a_Vehicle.getLicensePlate()[i]));
			}
		}
		else result = false;

		return result;
	}
	std::istream& Vehicle::read(std::istream& istr) {
		if (isCsv()) {
			istr >> m_ParkingSpot_Num;
			istr.ignore();

			istr.getline(m_LicensePlate, MAX_CHAR + 1, ',');

			char container[15];
			istr.getline(container, 15, ',');

			int sizeOf_MandM = strlen(container) + 1;
			delete[] m_MakeAndModel;
			m_MakeAndModel = new char[sizeOf_MandM];
			strncpy(m_MakeAndModel, container, sizeOf_MandM - 1);
			m_MakeAndModel[sizeOf_MandM - 1] = '\0';

			for (unsigned int i = 0; i < strlen(m_LicensePlate); i++) {
				m_LicensePlate[i] = toupper(m_LicensePlate[i]);
			}
		}
		else {
			//1.
			cout << "Enter Licence Plate Number: ";
			istr.getline(m_LicensePlate, MAX_CHAR + 1, '\n');
				
			while (istr.fail() || strlen(m_LicensePlate) == 0) {
				if (istr.fail()) {
					istr.clear();
					istr.ignore(2000, '\n');
					cout << "Invalid Licence Plate, try again: ";
					istr.getline(m_LicensePlate, MAX_CHAR + 1, '\n');
				}
				else {
					cout << "Invalid Licence Plate, try again: ";
					istr.getline(m_LicensePlate, MAX_CHAR + 1, '\n');
				}
			}

			for (unsigned int i = 0; i < strlen(m_LicensePlate); i++) {
				m_LicensePlate[i] = toupper(m_LicensePlate[i]);
			}

			//2.
			cout << "Enter Make and Model: ";
			char container[61]; //just to make array size enough big because I cannot expect how long a entered string will be.
			istr.getline(container, 61, '\n');

			while (istr.fail() || strlen(container) == 1) {
				if (strlen(container) != 1) {//which means the compiler entered this loop because of cin.fail()
					istr.clear();
					istr.ignore(2000, '\n');
					cout << "Invalid Make and model, try again: ";
					istr.getline(container, 61, '\n');
				}
				else {
					cout << "Invalid Make and model, try again: ";
					istr.getline(container, 61, '\n');
				}
			}

			delete[] m_MakeAndModel;
			m_MakeAndModel = new char[strlen(container) + 1];
			strcpy(m_MakeAndModel, container);

			//3.
			m_ParkingSpot_Num = 0;
		}

		return istr;
	}

	std::ostream& Vehicle::write(std::ostream& ostr) const {
		if (isEmpty()) {
			ostr << "Invalid Vehicle Object" << endl;
		}
		else if (isCsv()) {
			ostr << m_ParkingSpot_Num << "," << m_LicensePlate << "," << m_MakeAndModel << ",";
		}
		else {
			ostr << "Parking Spot Number: ";
			if (m_ParkingSpot_Num == 0) ostr << "N/A" << endl;
			else ostr << m_ParkingSpot_Num << endl;
			ostr << "Licence Plate: " << m_LicensePlate << endl;
			ostr << "Make and Model: " << m_MakeAndModel << endl;
		}

		return ostr;
	}

	//-------------------------------------PROTECTED---------------------------------------
	void Vehicle::setEmpty() {
		strcpy(m_LicensePlate, "");
		delete[] m_MakeAndModel;
		m_MakeAndModel = nullptr;
		m_ParkingSpot_Num = -1;
	}
	bool Vehicle::isEmpty() const {
		return m_ParkingSpot_Num == -1;
	}
	const char* Vehicle::getLicensePlate() const {
		return m_LicensePlate;
	}
	const char* Vehicle::getMakeModel() const {
		return m_MakeAndModel;
	}
	void Vehicle::setMakeModel(const char* _MakeAndModel) {
		if (_MakeAndModel != nullptr && _MakeAndModel[0] != '\0') {
			delete[] m_MakeAndModel;
			m_MakeAndModel = new char[strlen(_MakeAndModel) + 1];
			strcpy(m_MakeAndModel, _MakeAndModel);
		}
		else setEmpty();
	}
	
}