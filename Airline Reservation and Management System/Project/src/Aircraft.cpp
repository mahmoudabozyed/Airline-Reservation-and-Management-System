#include "Aircraft.hpp"

Aircraft::Aircraft(const std::string& aircraftId, const std::string& aircraftType, int totalSeats)
    : aircraftId(aircraftId), aircraftType(aircraftType), totalSeats(totalSeats) {}

std::string Aircraft::getAircraftId() const {
    return aircraftId;
}

std::string Aircraft::getAircraftType() const {
    return aircraftType;
}

int Aircraft::getTotalSeats() const {
    return totalSeats;
}