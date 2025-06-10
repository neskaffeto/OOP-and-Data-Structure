#include "ucn.h"

ucn::ucn(const char* egn)
{
	if (egn == nullptr) {
		throw std::invalid_argument("Invalid input");
	}
	if (strlen(egn) != 10)
		throw std::invalid_argument("Invalid input");

	for (int i = 0; i < 10; ++i) {
		if (!isdigit(egn[i]))
			throw std::invalid_argument("Invalid input");
	}
	//year
	if (isdigit(egn[0]) && isdigit(egn[1])) {
		gg[0] = egn[0] - '0';
		gg[1] = egn[1] - '0';
	}
	else throw std::invalid_argument("Invalid input");

	//month
	for (int i = 0; i < 2; ++i) gg[i] = egn[i] - '0';
	for (int i = 0; i < 2; ++i) mm[i] = egn[2 + i] - '0';
	for (int i = 0; i < 2; ++i) dd[i] = egn[4 + i] - '0';
	for (int i = 0; i < 3; ++i) reg[i] = egn[6 + i] - '0';
	p = egn[9] - '0';

	if (!is_valid_ucn(egn_val))
		throw std::invalid_argument("Invalid input");
	strcpy(egn_val, egn);
}
//връща година на раждане
int ucn::year(ucn egn) const
{
	int y = gg[0] * 10 + gg[1];
	int m = mm[0] * 10 + mm[1];

	if (m >= 1 && m <= 12) return 1900 + y;
	if (m >= 21 && m <= 32) return 1800 + y;
	if (m >= 41 && m <= 52) return 2000 + y;

	return -1;
}
//връща месец на раждане
int ucn::month(ucn egn) const
{
	int m = mm[0] * 10 + mm[1];
	if (m >= 1 && m <= 12) return m;
	if (m >= 21 && m <= 32) return m - 20;
	if (m >= 41 && m <= 52) return m - 40;

	return -1;
}

//връша ден на раждане
int ucn::day(ucn egn) const
{
	return dd[0] * 10 + dd[1];
}
//връща региона
std::string ucn::region() const
{
	const int region = reg[0] * 100 + reg[1] * 10 + reg[2];
	return get_region(region);
}
//връща региона по подаден номер
std::string ucn::get_region(const int reg) {

	int region_start[] = {
	0, 44, 94, 140, 170, 184, 218, 234, 282, 302,
	320, 342, 378, 396, 436, 502, 528, 556, 576, 602,
	624, 722, 752, 790, 822, 844, 872, 904, 926
	};

	int region_end[] = {
		43, 93, 139, 169, 183, 217, 233, 281, 301, 319,
		341, 377, 395, 435, 501, 527, 555, 575, 601, 623,
		721, 751, 789, 821, 843, 871, 903, 925, 999
	};

	const char* region_names[] = {
		"Благоевград", "Бургас", "Варна", "Велико Търново", "Видин",
		"Враца", "Габрово", "Кърджали", "Кюстендил", "Ловеч",
		"Монтана", "Пазарджик", "Перник", "Плевен", "Пловдив",
		"Разград", "Русе", "Силистра", "Сливен", "Смолян",
		"София - град", "София - окръг", "Стара Загора", "Добрич", "Търговище",
		"Хасково", "Шумен", "Ямбол", "Друг/Неизвестен"
	};

	const int size = sizeof(region_start) / sizeof(region_start[0]);
	for (int i = 0; i < size; ++i) {
		if (reg>= region_start[i] && reg <= region_end[i]) {
			return region_names[i];
		}
	}
	return "Няма регион";

}

//проверява дали егн е валидно
bool ucn::is_valid_ucn(const char* egn) 
{

	if (strlen(egn) != 10) return false;

	for (int i = 0; i < 10; i++) {
		if (!isdigit(egn[i])) return false;
	}

	int y = (egn[0] - '0') * 10 + (egn[1] - '0');
	int m = (egn[2] - '0') * 10 + (egn[3] - '0');
	int d = (egn[4] - '0') * 10 + (egn[5] - '0');
	if (!valid_date(y, m, d)) return false;

	std::string str(egn);
	return (calculate_lastd(str) == (egn[9] - '0'));
	
}
//проверява дали датата е валидна
bool ucn::valid_date(int y, int m, int d) {
	if (m >= 1 && m <= 12)
		y += 1900;
	else if (m > 20 && m <= 32) {
		y += 1800;
		m -= 20;
	}
	else if (m > 40 && m <= 52) {
		y += 2000;
		m -= 40;
	}
	else return false;

	if (m < 1 || m>12 || d < 1 || d>31) return false;

	int month_days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	if (m == 2 && leap) return d <= 29;

	return d <= month_days[m - 1];
}

//smqta posledna cifra
int ucn::calculate_lastd(const std::string& egn)
{
	int arr[] = { 2,4,8,5,10,9,7,3,6 };
	int sum = 0;
	for (int i = 0; i < 9; i++) {
		sum += (egn[i] - '0') * arr[i];
	}
	int digit = sum % 11;
	if (digit == 10) return 0; //ako e 10 -> 0
	return digit; //poslednata cifra
}

const char* ucn::to_string() const
{
	return egn_val;
}

std::ostream& operator<<(std::ostream& file, const ucn& egn)
{
	if (!file.fail()) {
		throw std::invalid_argument("Invalid input");
	}

	file << egn.to_string() << std::endl;

	return file;
}

std::istream& operator>>(std::istream& file, ucn& egn)
{
	if (!file.fail()) {
		throw std::invalid_argument("Invalid input");
	}
	char buff[11];
	file.getline(buff, 10);

	egn = ucn(buff);
	return file;
}
