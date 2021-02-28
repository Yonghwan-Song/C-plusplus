/**********************************************************
 * Name: Yonghwan Song
 * Student ID: 135458198
 * Seneca email: ysong115@myseneca.ca
 * Section: NDD
 * Completion Date: 8.8
 ->I have done all the coding by myself and only copied the code that my
 professor provided to complete my workshops and assignments.
 **********************************************************/
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
