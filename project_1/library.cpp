#include "library.h"

vehicle_register Library::vr;

void Library::register_car(const char* egn, const char* plate) {
    ucn u= ucn(egn);
    registration_plate p = registration_plate(plate);
    vr.register_vehicle(p,u);
}

void Library::deregister_car(const char* plate) {
    registration_plate r = registration_plate(plate);
    vr.deregister(r);
}

std::vector<registration_plate> Library::get_cars(const char* egn) {
    ucn owner = ucn(egn);
    return vr.owned_vehicles(owner);
}


std::ostream& Library::print_result(std::ostream& os) {
    os << vr;
    return os;
}

std::istream& Library::get_values(std::istream& is) {
    is >> vr;
    return is;
}