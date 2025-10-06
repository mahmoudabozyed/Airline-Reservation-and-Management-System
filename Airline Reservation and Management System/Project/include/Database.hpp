#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include <string>
#include <memory> 
#include <nlohmann/json.hpp>
#include "User.hpp"
#include "Flight.hpp"
#include "Reservation.hpp"
#include "Aircraft.hpp"

using json = nlohmann::json;

class Database {
public:
    static std::vector<std::shared_ptr<User>> users; 
    static std::vector<Flight> flights;
    static std::vector<Reservation> reservations;
    static std::vector<Aircraft> aircrafts; 

    static void loadUsers();
    static void saveUsers();
    static void loadFlights();
    static void saveFlights();
    static void loadReservations();
    static void saveReservations();
    
    static void loadAircrafts();
    static void saveAircrafts();

    static bool validateUser(const std::string& username, const std::string& password);
};

#endif 