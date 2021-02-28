#ifndef SDDS_READWRITABLE_H
#define SDDS_READWRITABLE_H
namespace sdds
{
	class ReadWritable {
	private:
		bool m_IscommaSeparated;
	public:
		ReadWritable();
		virtual ~ReadWritable();
		bool isCsv() const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream& istr = std::cin) = 0;
		virtual std::ostream& write(std::ostream& ostr = std::cout)const = 0;
	};

	std::istream& operator>>(std::istream& istr, ReadWritable& _ReadWritbale);
	std::ostream& operator<<(std::ostream& ostr, const ReadWritable& _ReadWritable);
}
#endif // !SDDS_READWRITABLE_H
