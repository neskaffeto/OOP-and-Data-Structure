#include "registration_plate.h"

registration_plate::registration_plate(const char* plate)
{
	checkValid(plate, *this);
}


bool registration_plate::operator<(const registration_plate& other) const
{	
	int res = strcmp(this->prefix, other.prefix);
	if (res == -1) return true;
	else if (res == 1) return false;
	for (int i = 0; i < 4; i++) {
		if (this->number[i] > other.number[i])
			return false;
	}
	res = strcmp(this->suffix, other.suffix);
	if (res == -1) return true;
	else return false;
}

bool registration_plate::operator==(const registration_plate& other) const
{
	return !(*this < other) && !(other < *this);
}

const char* registration_plate::to_string() const
{
	char regplate[9];
	int curr_length = strlen(prefix);
	strcpy(regplate, this->prefix);
	for (int i = 0; i < num_size; i++)
	{
		regplate[curr_length+i]=number[i] + '0';
		curr_length++;
	}
	strcpy(regplate + curr_length, suffix);
	return regplate;
}

registration_plate checkValid(const char* plate, registration_plate& pl)
{
	//празен plate
	if (plate == nullptr)
		throw std::invalid_argument("Invalid input");
	//невалидна дължина
	if (strlen(plate) > 8) {
		throw std::invalid_argument("Invalid input");
	}
	//първия символ не е буква
	if (!isalpha(plate[0])) {
		throw std::invalid_argument("Invalid input");
	}

	pl.prefix[0] = plate[0];
	//проверка на втория символ
	if (isalpha(plate[1])) { //ako е втора буква
		pl.prefix[1] = plate[1];
		for (int i = 0; i < num_size; i++) {
			if (isdigit(plate[i + 2])) {
				pl.number[i] = plate[i + 2]-'0';
			}
			else throw std::invalid_argument("Invalid input");
		}
		//проверка за последните 2 символа
		if (isalpha(plate[strlen(plate) - 2]) && isalpha(plate[strlen(plate) - 1])) {
			pl.suffix[0] = plate[strlen(plate) - 2];
			pl.suffix[1] = plate[strlen(plate) - 1];
		}

	}
	else if (isdigit(plate[1])) { //ako е цифра
		pl.number[0] = plate[1] - '0';
		for (int i = 1; i < num_size; i++) {
			if (isdigit(plate[i + 1])) {
				pl.number[i] = plate[i + 1]-'0';
			}
			else throw std::invalid_argument("Invalid input");
		}
		//проверка за последните 2 символа
		if (isalpha(plate[num_size + 1]) && isalpha(plate[num_size + 2]) && strlen(plate) < 8) {
			pl.suffix[0] = plate[num_size + 1];
			pl.suffix[1] = plate[num_size + 2];
		}
	}
	else {
		throw std::invalid_argument("Invalid input");
	}
	return pl;
}

std::ostream& operator<<(std::ostream& file, const registration_plate& plate)
{
	
	if (!file) {
		throw std::invalid_argument("Invalid input");
	}

	file << plate.to_string()<<std::endl;

	return file;

}

std::istream& operator>>(std::istream& is, registration_plate& plate)
{
	if (!is) {
		throw std::invalid_argument("Invalid input");
	}
		char buff[9];
		is.getline(buff, 8);
		
		checkValid(buff, plate);
		

	return is;
}
