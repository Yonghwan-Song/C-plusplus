#ifndef SDDS_MORTORCYCLE_H
#define SDDS_MORTORCYCLE_H
#include "Vehicle.h"

namespace sdds
{
	class Motorcycle : public Vehicle {
		bool m_sidecar;
	public:
		Motorcycle();
		Motorcycle(const char* _LicensePlate, const char* _MakeAndModel);
		Motorcycle(const Motorcycle&) = delete;
		Motorcycle& operator=(const Motorcycle&) = delete;
		virtual std::istream& read(std::istream& istr = std::cin);
		virtual std::ostream& write(std::ostream& ostr = std::cout) const;
	};
}
#endif