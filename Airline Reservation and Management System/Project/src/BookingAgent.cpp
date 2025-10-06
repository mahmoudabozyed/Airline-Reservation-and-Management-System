#include "BookingAgent.hpp"
#include "Database.hpp"
#include <iostream>

BookingAgent::BookingAgent(const std::string& uname, const std::string& pwd)
    : User(uname, pwd, "Booking Agent") {}

void BookingAgent::displayMenu() {
    std::cout << "--- Booking Agent Menu ---\n";
    std::cout << "1. Search Flights\n";
    std::cout << "2. Book a Flight\n";
    std::cout << "3. Modify Reservation\n";
    std::cout << "4. Cancel Reservation\n";
    std::cout << "5. Logout\n";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            searchFlights();
            break;
        case 2:
            bookFlight();
            break;
        case 3:
            modifyReservation();
            break;
        case 4:
            cancelReservation();
            break;
        case 5:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            displayMenu();
            break;
    }
}

void BookingAgent::bookFlight() {
    std::string pid, fnum, seat, payment;
    double cost;

    std::cout << "Enter Passenger ID: ";
    std::cin >> pid;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cout << "Enter Flight Number: ";
    std::cin >> fnum;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool flightFound = false;
    for (const auto& flight : Database::flights) {
        if (flight.getFlightNumber() == fnum) {
            flightFound = true;
            break;
        }
    }

    if (!flightFound) {
        std::cout << "Error: Flight " << fnum << " not found.\n";
        return;
    }

    std::cout << "Enter Seat Number (e.g., 12A): ";
    std::cin >> seat;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Payment Method (Credit Card/Cash/PayPal): ";
    std::cin >> payment;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Total Cost: ";
    std::cin >> cost;

    if (std::cin.fail()) { 
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Invalid input. Please enter a number.\n";
        return;
    }

    // الأسطر المضافة الجديدة
    std::string gate, boardingTime;
    std::cout << "Enter Boarding Gate (e.g., A22): ";
    std::cin >> gate;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Boarding Time (HH:MM): ";
    std::cin >> boardingTime;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool seatOccupied = false;
    for (const auto& reservation : Database::reservations) {
        if (reservation.getFlightNumber() == fnum && reservation.getSeatNumber() == seat) {
            seatOccupied = true;
            break;
        }
    }

    if (seatOccupied) {
        std::cout << "Error: Seat " << seat << " on Flight " << fnum << " is already occupied. Please choose a different seat.\n";
    } else {
        Reservation newReservation("R" + std::to_string(Database::reservations.size() + 1), pid, fnum, seat, payment, cost, gate, boardingTime);
        Database::reservations.push_back(newReservation);
        Database::saveReservations();
        std::cout << "Booking successful!\n";
        std::cout << "Reservation ID: " << newReservation.getReservationId() << "\n";
        std::cout << "Passenger: " << pid << "\n";
        std::cout << "Flight: " << fnum << "\n";
        std::cout << "Seat: " << seat << "\n";
        std::cout << "Boarding Gate: " << gate << "\n";
        std::cout << "Boarding Time: " << boardingTime << "\n";
        std::cout << "Total Cost: $" << cost << "\n";
        std::cout << "Payment Method: " << payment << "\n";
    }
}

void BookingAgent::modifyReservation() {
    std::string reservationId;
    std::cout << "Enter Reservation ID: ";
    std::cin >> reservationId;

    bool found = false;
    for (auto& reservation : Database::reservations) {
        if (reservation.getReservationId() == reservationId) {
            found = true;
            std::string newSeat;
            std::cout << "Enter New Seat Number: ";
            std::cin >> newSeat;

            bool seatOccupied = false;
            for (const auto& res : Database::reservations) {
                if (res.getFlightNumber() == reservation.getFlightNumber() && res.getSeatNumber() == newSeat) {
                    seatOccupied = true;
                    break;
                }
            }

            if (seatOccupied) {
                std::cout << "Error: Seat " << newSeat << " is already occupied. Please choose a different seat.\n";
            } else {
                reservation = Reservation(reservationId, reservation.getPassengerId(), reservation.getFlightNumber(), newSeat, reservation.getPaymentMethod(), reservation.getTotalCost(), reservation.getGate(), reservation.getBoardingTime());
                Database::saveReservations();
                std::cout << "Reservation modified successfully!\n";
                std::cout << "New Seat: " << newSeat << "\n";
            }
            break;
        }
    }

    if (!found) {
        std::cout << "Reservation not found.\n";
    }
}

void BookingAgent::searchFlights() {
    std::string origin, destination;
    std::cout << "Enter Origin: ";
    std::cin >> origin;
    std::cout << "Enter Destination: ";
    std::cin >> destination;

    bool found = false;
    for (const auto& flight : Database::flights) {
        if (flight.getOrigin() == origin && flight.getDestination() == destination) {
            found = true;
            std::cout << "Flight Number: " << flight.getFlightNumber() << "\n";
            std::cout << "Departure: " << flight.getDepartureTime() << "\n";
            std::cout << "Arrival: " << flight.getArrivalTime() << "\n";
            std::cout << "Aircraft: " << flight.getAircraftType() << "\n";
            std::cout << "Seats Available: " << flight.getTotalSeats() << "\n";
            std::cout << "Price: " << flight.getCost() << "\n";
            std::cout << "-------------------------\n";
        }
    }

    if (!found) {
        std::cout << "No flights found for the given origin and destination.\n";
    }
}

void BookingAgent::cancelReservation() {
    std::string reservationId;
    std::cout << "Enter Reservation ID: ";
    std::cin >> reservationId;

    bool found = false;
    for (auto it = Database::reservations.begin(); it != Database::reservations.end(); ++it) {
        if (it->getReservationId() == reservationId) {
            found = true;
            std::cout << "Are you sure you want to cancel Reservation ID " << reservationId << "? (yes/no): ";
            std::string confirmation;
            std::cin >> confirmation;

            if (confirmation == "yes") {
                double refundAmount = it->getTotalCost();
                std::string paymentMethod = it->getPaymentMethod();
                Database::reservations.erase(it);
                Database::saveReservations();
                std::cout << "Reservation canceled successfully!\n";
                std::cout << "Refund Amount: $" << refundAmount << " has been credited to " << paymentMethod << ".\n";
            } else {
                std::cout << "Cancellation aborted.\n";
            }
            break;
        }
    }

    if (!found) {
        std::cout << "Reservation not found.\n";
    }
}