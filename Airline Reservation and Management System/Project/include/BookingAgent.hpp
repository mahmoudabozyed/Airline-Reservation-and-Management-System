#ifndef BOOKINGAGENT_HPP
#define BOOKINGAGENT_HPP

#include "User.hpp"

class BookingAgent : public User {
public:
    BookingAgent(const std::string& uname, const std::string& pwd);

    void displayMenu() override;

    void searchFlights(); 
    void bookFlight();
    void modifyReservation();
    void cancelReservation();
};

#endif 