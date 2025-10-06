#include "Flight.hpp"

Flight::Flight(const std::string& fnum, const std::string& orig, const std::string& dest,
               const std::string& dept, const std::string& arr, const std::string& aircraft, int seats, const std::string& stat, double cost)
    : flightNumber(fnum), origin(orig), destination(dest), departureTime(dept),
      arrivalTime(arr), aircraftType(aircraft), totalSeats(seats), status(stat), cost(cost) {}

std::string Flight::getFlightNumber() const {
    return flightNumber;
}

std::string Flight::getOrigin() const {
    return origin;
}

std::string Flight::getDestination() const {
    return destination;
}

std::string Flight::getDepartureTime() const {
    return departureTime;
}

std::string Flight::getArrivalTime() const {
    return arrivalTime;
}

std::string Flight::getAircraftType() const {
    return aircraftType;
}

int Flight::getTotalSeats() const {
    return totalSeats;
}

std::string Flight::getStatus() const {
    return status;
}

double Flight::getCost() const {
    return cost;
}