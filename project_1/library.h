#pragma once
#include "vehicle_register.cpp"
#include <istream>
#include <ostream>

class Library {
private:
    static vehicle_register vr;
public:
    Library() = delete; //Забранява default конструктор
    static void register_car(const char* egn, const char* plate);
    static void deregister_car(const char* plate);
    static std::vector<registration_plate> get_cars(const char* egn);
    static std::ostream& print_result(std::ostream& os);
    static std::istream& get_values(std::istream& is);

};
