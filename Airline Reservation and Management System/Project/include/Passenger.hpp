#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"

class Passenger : public User {
public:
    Passenger(const std::string& uname, const std::string& pwd);

    void displayMenu() override;

    void searchFlights();
    void viewReservations();
    void checkIn();
    void logout(); 
};

#endif 