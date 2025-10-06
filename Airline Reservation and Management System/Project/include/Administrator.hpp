#ifndef ADMINISTRATOR_HPP
#define ADMINISTRATOR_HPP

#include "User.hpp"

class Administrator : public User {
public:
    Administrator(const std::string& uname, const std::string& pwd);

    void displayMenu() override;

    void addFlight();
    void updateFlight();
    void removeFlight();
    void manageFlights();
    void viewAllFlights();

    void addAircraft();
    void updateAircraft();
    void removeAircraft();
    void manageAircraft();
    void viewAllAircraft();

    void addUser();
    void updateUser();
    void removeUser();
    void manageUsers();
    void viewAllUsers();

    void generateReport();
    void generateOperationalReport();
    void generateMaintenanceReport();
    void generateUserActivityReport();

    void logout();

};

#endif 