#include "Passenger.hpp"
#include "Database.hpp"
#include <iostream>
#include <limits> 

Passenger::Passenger(const std::string& uname, const std::string& pwd)
    : User(uname, pwd, "Passenger") {}

void Passenger::displayMenu() {
    std::cout << "--- Passenger Menu ---\n";
    std::cout << "1. Search Flights\n";
    std::cout << "2. View My Reservations\n";
    std::cout << "3. Check-In\n";
    std::cout << "4. Logout\n";
}

void Passenger::searchFlights() {
    std::string origin, destination;
    std::cout << "\n--- Search Flights ---\n";
    
    std::cout << "Enter Origin: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, origin);
    
    std::cout << "Enter Destination: ";
    std::getline(std::cin, destination);

    bool found = false;
    std::cout << "\nSearching flights from " << origin << " to " << destination << "...\n";
    std::cout << "--------------------------------------------------\n";
    
    for (const auto& flight : Database::flights) {
        std::string flightOrigin = flight.getOrigin();
        std::string flightDest = flight.getDestination();
        std::transform(flightOrigin.begin(), flightOrigin.end(), flightOrigin.begin(), ::tolower);
        std::transform(flightDest.begin(), flightDest.end(), flightDest.begin(), ::tolower);
        
        std::string inputOrigin = origin;
        std::string inputDest = destination;
        std::transform(inputOrigin.begin(), inputOrigin.end(), inputOrigin.begin(), ::tolower);
        std::transform(inputDest.begin(), inputDest.end(), inputDest.begin(), ::tolower);

        if (flightOrigin.find(inputOrigin) != std::string::npos && 
            flightDest.find(inputDest) != std::string::npos) {
            found = true;
            std::cout << "Flight Number: " << flight.getFlightNumber() << "\n";
            std::cout << "Route: " << flight.getOrigin() << " -> " << flight.getDestination() << "\n";
            std::cout << "Departure: " << flight.getDepartureTime() << "\n";
            std::cout << "Arrival: " << flight.getArrivalTime() << "\n";
            std::cout << "Seats Available: " << flight.getTotalSeats() << "\n";
            std::cout << "Price: $" << std::fixed << std::setprecision(2) << flight.getCost() << "\n";
            std::cout << "--------------------------------------------------\n";
        }
    }

    if (!found) {
        std::cout << "No flights found from " << origin << " to " << destination << ".\n";
        std::cout << "Suggestions:\n";
        std::cout << "- Check spelling of origin/destination\n";
        std::cout << "- Try using airport codes (e.g. CAI instead of Egypt)\n";
    }
}

void Passenger::viewReservations() {
    std::cout << "\n--- My Reservations ---\n";
    std::cout << "Fetching reservations for " << getUsername() << "...\n";
    std::cout << "--------------------------------------------------\n";

    bool hasReservations = false;
    int reservationCount = 0;

    for (const auto& reservation : Database::reservations) {
        if (reservation.getPassengerId() == getUsername()) {
            hasReservations = true;
            reservationCount++;
            
            std::cout << "Reservation #" << reservationCount << "\n";
            std::cout << "ID: " << reservation.getReservationId() << "\n";
            
            for (const auto& flight : Database::flights) {
                if (flight.getFlightNumber() == reservation.getFlightNumber()) {
                    std::cout << "Flight: " << flight.getFlightNumber() << " (" 
                              << flight.getOrigin() << " -> " << flight.getDestination() << ")\n";
                    std::cout << "Departure: " << flight.getDepartureTime() << "\n";
                    break;
                }
            }
            
            std::cout << "Seat: " << reservation.getSeatNumber() << "\n";
            std::cout << "Total Paid: $" << std::fixed << std::setprecision(2) 
                      << reservation.getTotalCost() << "\n";
            std::cout << "Status: Confirmed\n";
            std::cout << "--------------------------------------------------\n";
        }
    }

    if (!hasReservations) {
        std::cout << "You don't have any reservations yet.\n";
        std::cout << "Please book a flight using option 1 in the main menu.\n";
    }
}

void Passenger::checkIn() {
    viewReservations();
    
    std::string reservationId;
    std::cout << "\n--- Check-In ---\n";
    std::cout << "Enter Reservation ID (or 0 to cancel): ";
    std::cin >> reservationId;

    if (reservationId == "0") {
        std::cout << "Check-In cancelled.\n";
        return;
    }

    bool found = false;
    for (const auto& reservation : Database::reservations) {
        if (reservation.getReservationId() == reservationId && 
            reservation.getPassengerId() == getUsername()) {
            found = true;
            
            for (const auto& flight : Database::flights) {
                if (flight.getFlightNumber() == reservation.getFlightNumber()) {
                    std::cout << "\nCHECK-IN SUCCESSFUL!\n";
                    std::cout << "=================================\n";
                    std::cout << "       ELECTRONIC BOARDING PASS\n";
                    std::cout << "=================================\n";
                    std::cout << " PASSENGER: " << getUsername() << "\n";
                    std::cout << " FLIGHT: " << flight.getFlightNumber() << "\n";
                    std::cout << " ROUTE: " << flight.getOrigin() << " -> " << flight.getDestination() << "\n";
                    std::cout << " DEPARTURE: " << flight.getDepartureTime() << "\n";
                    std::cout << " SEAT: " << reservation.getSeatNumber() << "\n";
                    std::cout << " GATE: " << (reservation.getGate().empty() ? "Will be announced" : reservation.getGate()) << "\n";
                    std::cout << " BOARDING TIME: " << (reservation.getBoardingTime().empty() ? flight.getDepartureTime() : reservation.getBoardingTime()) << "\n";
                    std::cout << "=================================\n";
                    std::cout << "Please arrive at the gate at least 2 hours before departure.\n";
                    break;
                }
            }
            break;
        }
    }

    if (!found) {
        std::cout << "\nERROR: Invalid Reservation ID or reservation doesn't belong to you.\n";
        std::cout << "Please:\n";
    }
}

void Passenger::logout() {
    std::cout << "Logging out...\n";
    std::cout << "Goodbye, " << getUsername() << "!\n";
}