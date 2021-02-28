#ifndef SDDS_CAR_H
#define SDDS_CAR_H
#include "Vehicle.h"

namespace sdds
{
	class Car : public Vehicle {
		bool m_carwash;
	public:
		Car();
		Car(const char* _LicensePlate, const char* _MakeAndModel);
		Car(const Car&) = delete;
		Car& operator=(const Car&) = delete;
		virtual std::istream& read(std::istream& istr = std::cin);
		virtual std::ostream& write(std::ostream& ostr = std::cout) const;
	};
}
#endif