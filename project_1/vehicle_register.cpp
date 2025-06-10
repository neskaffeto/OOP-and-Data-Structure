#include "vehicle_register.h"
#include <sstream>
#include <stdexcept>

vehicle_register::vehicle_register() = default;

void vehicle_register::register_vehicle(const registration_plate & plate, const ucn & owner) {
    auto& plates = owner_and_plate[owner];  // намира или създава празен вектор

    // проверка за вече регистриран plate
    for (const auto& reg : plates) {
        if (reg == plate) {
            throw std::invalid_argument("Registration plate already exists");
        }
    }

    plates.push_back(plate);
}

void vehicle_register::deregister(const registration_plate & plate) {
    for (auto it = owner_and_plate.begin(); it != owner_and_plate.end(); ++it) {
        auto& plates = it->second;
        auto plate_it = std::find(plates.begin(), plates.end(), plate);
        if (plate_it != plates.end()) {
            plates.erase(plate_it);
            if (plates.empty()) {
                owner_and_plate.erase(it);
            }
            return;
        }
    }
    std::invalid_argument("Plate not found");
}

std::vector<registration_plate> vehicle_register::owned_vehicles(const ucn & person) const {
    auto it = owner_and_plate.find(person);
    if (it != owner_and_plate.end()) {
        return it->second;
    }
    return {};
}

std::ostream& operator<<(std::ostream& file, const vehicle_register& vr) {
    for (const auto& entry : vr.owner_and_plate) {
        for (const auto& plate : entry.second) {
            file << entry.first.to_string() << " " << plate.to_string() << std::endl;
        }
    }
    return file;
}

std::istream& operator>>(std::istream& is, vehicle_register& vr) {
    std::istream& operator>>(std::istream & is, vehicle_register & vr) {
        registration_plate plate;
        ucn owner;

        while (is >> owner >> plate) {
            try {
                vr.register_vehicle(plate, owner);  // Регистрира превозното средство на собственика
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error registering vehicle: " << e.what() << std::endl;
            }
        }
        return is;
    }
}
