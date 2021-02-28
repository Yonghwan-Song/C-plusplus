#ifndef SDDS_PARKING_H
#define SDDS_PARKING_H
#include "Menu.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"

namespace sdds
{
	const int MAX_ParkingSpots = 100;

	class Parking {
		char* m_filename;
		Menu m_ParkingM;
		Menu m_VehicleM;
		int m_NumofSpots;
		int m_NumofParkedVehicles;
		Vehicle* m_ParkingSpots[MAX_ParkingSpots];
		bool Load_datafile();
		void Save_datafile() const;
		bool isEmpty() const;
		void Parking_status() const;
		void Park_vehicle();
		void Return_vehicle();
		void List_vehicleParked() const;
		bool Close_parking();
		bool Exit_ParkingApp() const;
	public:
		Parking(const char* datafile, int noOfSpots);
		~Parking();
		Parking(const Parking&) = delete;
		Parking& operator=(const Parking&) = delete;
		int run();
		

	};
}
#endif // !SDDS_PARKING_H
