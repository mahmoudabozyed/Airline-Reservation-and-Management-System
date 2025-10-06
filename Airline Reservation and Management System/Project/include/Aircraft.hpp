#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <string>

class Aircraft {
public:
    Aircraft(const std::string& aircraftId, const std::string& aircraftType, int totalSeats);

    std::string getAircraftId() const;
    std::string getAircraftType() const;
    int getTotalSeats() const;

private:
    std::string aircraftId;
    std::string aircraftType;
    int totalSeats;
};

#endif 