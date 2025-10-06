#include "Database.hpp"
#include "Administrator.hpp"
#include "BookingAgent.hpp"
#include "Passenger.hpp"
#include "Database.hpp"
#include "Aircraft.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<Reservation> Database::reservations;
std::vector<Flight> Database::flights;
std::vector<std::shared_ptr<User>> Database::users;
std::vector<Aircraft> Database::aircrafts;

void Database::loadUsers() {

    users.push_back(std::make_shared<Administrator>("adminUser", "adminPass"));
    users.push_back(std::make_shared<BookingAgent>("agentUser", "agentPass"));
    users.push_back(std::make_shared<Passenger>("passengerUser", "passengerPass"));

    std::ifstream file("users.json");
    if (file.is_open()) {
        json data;
        file >> data;
        file.close();

        for (const auto& userData : data["users"]) {
            std::string username = userData["username"];
            std::string password = userData["password"];
            std::string role = userData["role"];

            if (role == "Administrator") {
                users.push_back(std::make_shared<Administrator>(username, password));
            } else if (role == "BookingAgent") {
                users.push_back(std::make_shared<BookingAgent>(username, password));
            } else if (role == "Passenger") {
                users.push_back(std::make_shared<Passenger>(username, password));
            }
        }
    }
}

void Database::saveUsers() {
    json data;
    for (const auto& user : users) {
        json userData;
        userData["username"] = user->getUsername();
        userData["password"] = user->getPassword();
        userData["role"] = user->getRole();
        data["users"].push_back(userData);
    }

    std::ofstream file("users.json");
    file << data.dump(4);
    file.close();
}

void Database::loadFlights() {
    std::ifstream file("flights.json");
    if (file.is_open()) {
        json data;
        file >> data;
        file.close();

        for (const auto& flightData : data["flights"]) {
            Flight flight(
                flightData["flightNumber"],
                flightData["origin"],
                flightData["destination"],
                flightData["departureTime"],
                flightData["arrivalTime"],
                flightData["aircraftType"],
                flightData["totalSeats"],
                flightData["status"],
                flightData["cost"]
            );
            flights.push_back(flight);
        }
    } else {

        flights.push_back(Flight("AA123", "New York (JFK)", "Los Angeles (LAX)", "2023-12-15 08:30", "2023-12-15 11:45", "Boeing 737", 180, "Scheduled",250.0));
    }
}

void Database::saveFlights() {
    json data;
    for (const auto& flight : flights) {
        json flightData;
        flightData["flightNumber"] = flight.getFlightNumber();
        flightData["origin"] = flight.getOrigin();
        flightData["destination"] = flight.getDestination();
        flightData["departureTime"] = flight.getDepartureTime();
        flightData["arrivalTime"] = flight.getArrivalTime();
        flightData["aircraftType"] = flight.getAircraftType();
        flightData["totalSeats"] = flight.getTotalSeats();
        flightData["status"] = flight.getStatus();
        data["flights"].push_back(flightData);
    }

    std::ofstream file("flights.json");
    file << data.dump(4);
    file.close();
}

void Database::loadReservations() {
    std::ifstream file("reservations.json");
    if (file.is_open()) {
        json data;
        file >> data;
        file.close();

        for (const auto& reservationData : data["reservations"]) {
            Reservation reservation(
                reservationData["reservationId"],
                reservationData["passengerId"],
                reservationData["flightNumber"],
                reservationData["seatNumber"],
                reservationData["paymentMethod"],
                reservationData["totalCost"],
                reservationData["gate"],
                reservationData["boardingTime"]
            );
            reservations.push_back(reservation);
        }
    }
}

void Database::saveReservations() {
    json data;
    for (const auto& reservation : reservations) {
        json reservationData;
        reservationData["reservationId"] = reservation.getReservationId();
        reservationData["passengerId"] = reservation.getPassengerId();
        reservationData["flightNumber"] = reservation.getFlightNumber();
        reservationData["seatNumber"] = reservation.getSeatNumber();
        reservationData["paymentMethod"] = reservation.getPaymentMethod();
        reservationData["totalCost"] = reservation.getTotalCost();
        data["reservations"].push_back(reservationData);
    }

    std::ofstream file("reservations.json");
    file << data.dump(4);
    file.close();
}

bool Database::validateUser(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user->getUsername() == username && user->getPassword() == password) {
            return true;
        }
    }
    return false;
}
// أضف هذه الدوال إلى Database.cpp
void Database::loadAircrafts() {
    std::ifstream file("aircrafts.json");
    if (file.is_open()) {
        json data;
        file >> data;
        file.close();

        for (const auto& aircraftData : data["aircrafts"]) {
            Aircraft aircraft(
                aircraftData["aircraftId"],
                aircraftData["aircraftType"],
                aircraftData["totalSeats"]
            );
            aircrafts.push_back(aircraft);
        }
    } else {
        // بيانات افتراضية إذا لم يوجد ملف
        aircrafts.push_back(Aircraft("A001", "Boeing 737", 180));
        aircrafts.push_back(Aircraft("A002", "Airbus A320", 150));
    }
}

void Database::saveAircrafts() {
    json data;
    for (const auto& aircraft : aircrafts) {
        json aircraftData;
        aircraftData["aircraftId"] = aircraft.getAircraftId();
        aircraftData["aircraftType"] = aircraft.getAircraftType();
        aircraftData["totalSeats"] = aircraft.getTotalSeats();
        data["aircrafts"].push_back(aircraftData);
    }

    std::ofstream file("aircrafts.json");
    file << data.dump(4);
    file.close();
}