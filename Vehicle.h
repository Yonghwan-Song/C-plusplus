#ifndef SDDS_VEHICLE_H
#define SDDS_VEHICLE_H
#include "ReadWritable.h"
namespace sdds
{
	const int MAX_CHAR = 8;

	class Vehicle : public ReadWritable {
		char m_LicensePlate[MAX_CHAR + 1];
		char* m_MakeAndModel;
		int m_ParkingSpot_Num;
		friend class Parking;
	public:
		Vehicle();
		Vehicle(const char* _LicensePlate, const char* _MakeAndModel);
		Vehicle(const Vehicle&) = delete;
		Vehicle& operator=(const Vehicle&) = delete;
		~Vehicle();
		int getParkingSpot() const;
		void setParkingSpot(int _spotNumber);
		bool operator==(const char* _LicensePlate) const;
		bool operator==(const Vehicle& _a_Vehicle) const;

		virtual std::istream& read(std::istream& istr = std::cin);
		virtual std::ostream& write(std::ostream& ostr = std::cout) const;
	protected:
		void setEmpty();
		bool isEmpty() const;
		const char* getLicensePlate() const;
		const char* getMakeModel() const;
		void setMakeModel(const char* _MakeAndModel);
	};
}
#endif // !SDDS_VEHICLE_H
