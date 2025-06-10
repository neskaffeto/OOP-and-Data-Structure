#pragma once
#include <map>
#include <vector>
#include <string>
#include <ostream>
#include <istream>
#include "ucn.cpp" 
#include "registration_plate.cpp"

class vehicle_register {
private:
    std::map<ucn, std::vector<registration_plate>> owner_and_plate;
public:
    vehicle_register();

    void register_vehicle (const registration_plate& plate, const ucn& owner);
    void deregister(const registration_plate& registration);
    std::vector<registration_plate> owned_vehicles(const ucn& person) const;

    friend std::ostream& operator<<(std::ostream& file, const vehicle_register& vr);
    friend std::istream& operator>>(std::istream& file, vehicle_register& vr);
};

