#include <iostream>
#include "ReadWritable.h"
using namespace std;

namespace sdds
{
	ReadWritable::ReadWritable() : m_IscommaSeparated(false) {
	}
	ReadWritable::~ReadWritable() {
	}
	bool ReadWritable::isCsv() const {
		return m_IscommaSeparated;
	}
	void ReadWritable::setCsv(bool value) {
		m_IscommaSeparated = value;
	}

	std::istream& operator>>(std::istream& istr, ReadWritable& _ReadWritbale) {
		return _ReadWritbale.read(istr);
	}
	std::ostream& operator<<(std::ostream& ostr, const ReadWritable& _ReadWritable) {
		return _ReadWritable.write(ostr);
	}
}