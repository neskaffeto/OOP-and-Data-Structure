#pragma once
#include <string>
#include <istream>
#include <ostream>
class ucn {
	int gg[2];
	int mm[2];
	int dd[2];
	int reg[3];
	int p;

	char* egn_val;

	static bool validate(const std::string& egn, int& y, int& m, int& d, std::string& reg);
	static bool valid_date(int y, int m, int d);
	static int calculate_lastd(const std::string& egn);
	static std::string get_region(const int reg) ;

public:
	ucn(const char* egn);
	int year(ucn egn) const;
	int month(ucn egn) const;
	int day(ucn egn) const;
	std::string region() const;
	static bool is_valid_ucn(const char* str);
	const char* to_string() const;
	friend std::ostream& operator<<(std::ostream& file, const ucn& egn);
	friend std::istream& operator>>(std::istream& file, ucn& egn);
};