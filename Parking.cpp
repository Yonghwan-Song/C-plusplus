#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Parking.h"
#include "Vehicle.h"
using namespace std;

namespace sdds
{
	Parking::Parking(const char* datafile, int noOfSpots) 
		: m_filename(nullptr), m_NumofParkedVehicles(0), m_ParkingSpots{nullptr} {
		bool judgement = false;
		if (datafile != nullptr && datafile[0] != '\0' && noOfSpots >= 10 && noOfSpots <= MAX_ParkingSpots) {
			m_NumofSpots = noOfSpots;
			m_filename = new char[strlen(datafile) + 1];
			strcpy(m_filename, datafile);
			judgement = Load_datafile();
			if (judgement) {
				m_ParkingM = Menu("Parking Menu, select an action:");
				m_ParkingM.add("Park Vehicle");
				m_ParkingM.add("Return Vehicle");
				m_ParkingM.add("List Parked Vehicles");
				m_ParkingM.add("Close Parking (End of day)");
				m_ParkingM.add("Exit Program");
				m_VehicleM = Menu("Select type of the vehicle:", 1);
				m_VehicleM.add("Car");
				m_VehicleM.add("Motorcycle");
				m_VehicleM.add("Cancel");
			}
		}

		if (!judgement) {
			cout << "Error in data file" << endl;
		}
	}

	bool Parking::Load_datafile() {
		bool state= true;
		ifstream fin;
		if (m_filename != nullptr) {
			fin.open(m_filename);
			if (fin.is_open()) {
				while (!fin.eof()) {
					char type = fin.get();
					fin.ignore();
					Vehicle* tmp_vehicle;
					if (type == 'M') {
						tmp_vehicle = new Motorcycle;
						tmp_vehicle->setCsv(true);
						tmp_vehicle->read(fin);

						if(fin.good()){
							m_ParkingSpots[tmp_vehicle->getParkingSpot()-1] = tmp_vehicle;
							tmp_vehicle = nullptr;
							++m_NumofParkedVehicles;
							state = true;
						}
						else {
							delete tmp_vehicle;
							tmp_vehicle = nullptr;
							state = true; 
						}
					}
					else {
						tmp_vehicle = new Car;
						tmp_vehicle->setCsv(true);
						tmp_vehicle->read(fin);
						
						if (fin.good()) {
							m_ParkingSpots[tmp_vehicle->getParkingSpot()-1] = tmp_vehicle;
							tmp_vehicle = nullptr;
							++m_NumofParkedVehicles;
							state = true;
						}
						else {
							delete tmp_vehicle;
							tmp_vehicle = nullptr;
							state = true;
						}
					}
				}
			}	
			else {
				state = true;
			}
			fin.close();
		}
		return state;
	}

	void Parking::Save_datafile() const {
		ofstream fin;
		if (m_filename != nullptr) {
			fin.open(m_filename);
			for (int i = 0; i < m_NumofSpots; i++) {
				if (m_ParkingSpots[i] != nullptr) {
					m_ParkingSpots[i]->setCsv(true);
					m_ParkingSpots[i]->write(fin);
				}
			}
		}
	}

	Parking::~Parking() {
		Save_datafile();
		for (int i = 0; i < m_NumofSpots; i++) {
			delete m_ParkingSpots[i];
		}
		delete[] m_filename;
	}

	bool Parking::isEmpty() const {
		return m_filename == nullptr ? true : false;
	}

	void Parking::Parking_status() const {
		cout << "****** Seneca Valet Parking ******" << endl;
		cout << "*****  Available spots: " << left << setw(4) << (m_NumofSpots - m_NumofParkedVehicles);
		cout << " *****" << endl;
	}

	void Parking::Park_vehicle() {
		if (m_NumofParkedVehicles == m_NumofSpots) {
			cout << "Parking is full" << endl;
		}
		else {
			int selection = m_VehicleM.run();

			Vehicle* tmp_vehicle;
			bool flag = true;
			int i;
			if (selection == 1) {
				tmp_vehicle= new Car();
				tmp_vehicle->read();

				for (i = 0; i < m_NumofSpots&&flag; i++) {
					if (m_ParkingSpots[i] == nullptr) {
						flag = false;
					}
				}
				m_ParkingSpots[i-1] = tmp_vehicle;
				m_ParkingSpots[i-1]->setParkingSpot(i);
				++m_NumofParkedVehicles;
				tmp_vehicle = nullptr;
				cout << "\nParking Ticket" << endl;
				m_ParkingSpots[i-1]->write();
				cout << endl;
			}
			else if (selection == 2) {
				tmp_vehicle = new Motorcycle();
				tmp_vehicle->read();
				for (i = 0; i < m_NumofSpots && flag; i++) {
					if (m_ParkingSpots[i] == nullptr) {
						flag = false;
					}
				}
				m_ParkingSpots[i-1] = tmp_vehicle;
				m_ParkingSpots[i-1]->setParkingSpot(i);
				++m_NumofParkedVehicles;
				tmp_vehicle = nullptr;
				cout << "\nParking Ticket" << endl;
				m_ParkingSpots[i-1]->write();
				cout << endl;
			}
			else {
				cout << "Parking cancelled" << endl;
			}
		}
	}

	void Parking::Return_vehicle() {
		//get
		cout << "Return Vehicle" << endl;
		cout << "Enter Licence Plate Number: ";
		char Entered_Lplate[MAX_CHAR*2];
		cin >> Entered_Lplate;
		while (strlen(Entered_Lplate) < 1 || strlen(Entered_Lplate) > 8) {
			cout << "Invalid Licence Plate, try again: ";
			cin >> Entered_Lplate;
		}

		//change characters of Entered_Lplate to uppercases so that I can compare with existing LicensePlates.
		for (unsigned int j = 0; j < strlen(Entered_Lplate); j++) {
			Entered_Lplate[j]=toupper(Entered_Lplate[j]);
		}

		//check if the licence plate I got exists in the parking lot.
		bool doesntExist = true;//default.
		int i;
		for (i = 0; i < m_NumofSpots&&doesntExist; i++) {
			if (m_ParkingSpots[i] != nullptr) {
				if (strcmp(m_ParkingSpots[i]->getLicensePlate(), Entered_Lplate) == 0) {
					doesntExist = false;
				}
			}	
		}

		if (doesntExist == false) {
			cout <<'\n'<< "Returning: " << endl;
			m_ParkingSpots[i - 1]->setCsv(false);
			m_ParkingSpots[i - 1]->write();
			cout << endl;
			delete m_ParkingSpots[i - 1];
			m_ParkingSpots[i - 1] = nullptr;
			--m_NumofParkedVehicles;
		}
		else {
			cout << "License plate: " << Entered_Lplate << " Not found" << endl;
		}
	}

	void Parking::List_vehicleParked() const {
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < m_NumofSpots; i++) {
			if (m_ParkingSpots[i] != nullptr) {
				m_ParkingSpots[i]->setCsv(false);
				m_ParkingSpots[i]->write();
				cout << "-------------------------------" << endl;
			}
		}
	}

	bool Parking::Close_parking() {
		bool result = true;
		bool isEmpty = true;
		//Check if there are remaining vehicles in the parking lot.
		for (int i = 0; i < m_NumofSpots&&isEmpty; i++) {
			if (m_ParkingSpots[i] != nullptr) {
				isEmpty = false;
			}
		}

		if (isEmpty) {
			cout << "Closing Parking" << endl;
		}
		else {
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";
			char answer;
			char trailingChar = '\n';
			answer = cin.get();
			trailingChar = cin.get();
			while (trailingChar != '\n' || (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')) {
				if (trailingChar != '\n') {
					cin.ignore(2000, '\n');
					cout << "invalid response, only (y)es or (n)o are acceptable, retry: ";
					cin >> answer;
					trailingChar = cin.get();
				}
				else {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					answer = cin.get();
					trailingChar = cin.get();
				}
			}

			if (answer == 'n' || answer == 'N') {
				result = false;
				cout << "Aborted!" << endl;
			}
			else {
				cout << "Closing Parking" <<endl;
				
				int i;
				for (i = 0; i < m_NumofSpots; i++) {
					if (m_ParkingSpots[i] != nullptr) {//if the spot is not empty,
						cout<<'\n'<< "Towing request" << endl;
						cout << "*********************" << endl;
						m_ParkingSpots[i]->write();
						delete m_ParkingSpots[i];
						m_ParkingSpots[i] = nullptr;
						--m_NumofParkedVehicles;
					}
				}
				result = true;
			}
		}
		
		return result;
	}

	bool Parking::Exit_ParkingApp() const {
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		char answer;
		char trailing = 'e';
		cin >> answer;
		trailing = cin.get();
		cin.putback(trailing);
		while (cin.fail() == true) {
			cin.clear();
			cin.ignore(2000, '\n');
			cout << "Invalid character, try again: ";
			cin >> answer;
			trailing = cin.get();
			cin.putback(trailing);
		}
		cin.ignore(2000, '\n');

		while ((answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n') ||
			trailing != '\n') {
			cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";

			cin >> answer;
			trailing = cin.get();
			cin.putback(trailing);
			while (cin.fail() == true) {
				cin.clear();
				cin.ignore(2000, '\n');
				cout << "Invalid character, try again: ";
				cin >> answer;
				trailing = cin.get();
				cin.putback(trailing);
			}
			cin.ignore(2000, '\n');
		}
		if (answer == 'y' || answer == 'Y') {
			cout << "Exiting program!" << endl;
		}
		return (answer == 'y' || answer == 'Y') ? true : false;
	}

	int Parking::run() {
		int result = 1;
		if (!isEmpty()) {
			bool judgement = true;
			do
			{
				Parking_status();
				int selection = m_ParkingM.run();
				switch (selection)
				{
				case 1: Park_vehicle();
					break;
				case 2: Return_vehicle();
					break;
				case 3: List_vehicleParked();
					break;
				case 4: judgement = !Close_parking();
					break;
				case 5: judgement = !Exit_ParkingApp();
					break;
				default:
					cout << "There is no menu items" << endl;
					judgement = false;
					break;
				}
			} while (judgement);

			result = 0;
		}
		return result;
	}
}
