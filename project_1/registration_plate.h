#pragma once
#include <istream>
#include <ostream>
const int num_size = 4;
const int letter_size = 3;
class registration_plate {
    int number[num_size];
    char prefix[letter_size];
    char suffix[letter_size];
public:
    registration_plate(const char*);
    bool operator<(const registration_plate&) const;
    bool operator==(const registration_plate&) const;
    const char* to_string() const;
    friend std::ostream& operator<<(std::ofstream&, const registration_plate&);
    friend std::istream& operator>>(std::istream&, registration_plate&);
    friend registration_plate checkValid(const char* plate, registration_plate& pl);
};

