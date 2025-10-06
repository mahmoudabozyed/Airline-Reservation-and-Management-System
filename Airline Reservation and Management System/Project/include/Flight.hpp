#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <string>

class Flight {
private:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureTime;
    std::string arrivalTime;
    std::string aircraftType;
    int totalSeats;
    std::string status;
    double cost;

public:
    Flight(const std::string& fnum, const std::string& orig, const std::string& dest,
           const std::string& dept, const std::string& arr, const std::string& aircraft, int seats, const std::string& stat, double cost);

    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::string getDepartureTime() const;
    std::string getArrivalTime() const;
    std::string getAircraftType() const;
    int getTotalSeats() const;
    std::string getStatus() const;
    double getCost() const;
};

#endif