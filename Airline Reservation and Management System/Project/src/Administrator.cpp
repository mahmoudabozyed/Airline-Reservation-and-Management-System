#include "Administrator.hpp"
#include "BookingAgent.hpp"
#include "Passenger.hpp"
#include "Database.hpp"
#include "Aircraft.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

Administrator::Administrator(const std::string& uname, const std::string& pwd)
    : User(uname, pwd, "Administrator") {}

void Administrator::displayMenu() {
    std::cout << "\n--- Administrator Menu ---\n";
    std::cout << "1. Manage Flights\n";
    std::cout << "2. Manage Aircraft\n";
    std::cout << "3. Manage Users\n";
    std::cout << "4. Generate Reports\n";
    std::cout << "5. Logout\n";
}

// دوال إدارة الرحلات
void Administrator::manageFlights() {
    int choice;
    while (true) {
        std::cout << "\n--- Manage Flights ---\n";
        std::cout << "1. Add New Flight\n";
        std::cout << "2. Update Existing Flight\n";
        std::cout << "3. Remove Flight\n";
        std::cout << "4. View All Flights\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            addFlight();
        } else if (choice == 2) {
            updateFlight();
        } else if (choice == 3) {
            removeFlight();
        } else if (choice == 4) {
            viewAllFlights();
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Administrator::addFlight() {
    std::string flightNumber, origin, destination, departureTime, arrivalTime, aircraftType, status;
    int totalSeats;

    std::cout << "\n--- Add New Flight ---\n";
    std::cout << "Enter Flight Number: ";
    std::cin >> flightNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Origin: ";
    std::getline(std::cin, origin);

    std::cout << "Enter Destination: ";
    std::getline(std::cin, destination);

    std::cout << "Enter Departure (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, departureTime);

    std::cout << "Enter Arrival (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, arrivalTime);

    std::cout << "Enter Aircraft Type: ";
    std::getline(std::cin, aircraftType);

    std::cout << "Enter Total Seats: ";
    std::cin >> totalSeats;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Status: ";
    std::getline(std::cin, status);

    Flight newFlight(flightNumber, origin, destination, departureTime, arrivalTime, aircraftType, totalSeats, status,250.0);
    Database::flights.push_back(newFlight);
    Database::saveFlights();
    std::cout << "Flight added successfully!\n";
}

void Administrator::updateFlight() {
    std::string flightNumber;
    std::cout << "\n--- Update Flight ---\n";
    std::cout << "Enter Flight Number: ";
    std::cin >> flightNumber;

    for (auto& flight : Database::flights) {
        if (flight.getFlightNumber() == flightNumber) {
            std::string origin, destination, departureTime, arrivalTime, aircraftType, status;
            int totalSeats;

            std::cout << "Enter New Origin: ";
            std::cin >> origin;
            std::cout << "Enter New Destination: ";
            std::cin >> destination;
            std::cout << "Enter New Departure (YYYY-MM-DD HH:MM): ";
            std::cin.ignore();
            std::getline(std::cin, departureTime);
            std::cout << "Enter New Arrival (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, arrivalTime);
            std::cout << "Enter New Aircraft Type: ";
            std::cin >> aircraftType;
            std::cout << "Enter New Total Seats: ";
            std::cin >> totalSeats;
            std::cout << "Enter New Status: ";
            std::cin >> status;

            flight = Flight(flightNumber, origin, destination, departureTime, arrivalTime, aircraftType, totalSeats, status,250.0);
            Database::saveFlights();
            std::cout << "Flight updated successfully!\n";
            return;
        }
    }
    std::cout << "Flight not found!\n";
}

void Administrator::removeFlight() {
    std::string flightNumber;
    std::cout << "\n--- Remove Flight ---\n";
    std::cout << "Enter Flight Number: ";
    std::cin >> flightNumber;

    auto it = std::remove_if(Database::flights.begin(), Database::flights.end(),
        [flightNumber](const Flight& f) { return f.getFlightNumber() == flightNumber; });

    if (it != Database::flights.end()) {
        Database::flights.erase(it, Database::flights.end());
        Database::saveFlights();
        std::cout << "Flight removed successfully!\n";
    } else {
        std::cout << "Flight not found!\n";
    }
}

void Administrator::viewAllFlights() {
    std::cout << "\n--- All Flights ---\n";
    for (const auto& flight : Database::flights) {
        std::cout << "Flight #: " << flight.getFlightNumber() << "\n"
                  << "Route: " << flight.getOrigin() << " -> " << flight.getDestination() << "\n"
                  << "Departure: " << flight.getDepartureTime() << "\n"
                  << "Arrival: " << flight.getArrivalTime() << "\n"
                  << "Aircraft: " << flight.getAircraftType() << "\n"
                  << "Seats: " << flight.getTotalSeats() << "\n"
                  << "Status: " << flight.getStatus() << "\n"
                  << "-------------------------\n";
    }
}

void Administrator::addAircraft() {
    std::string aircraftId, aircraftType;
    int totalSeats;

    std::cout << "--- Add New Aircraft ---\n";
    std::cout << "Enter Aircraft ID: ";
    std::cin >> aircraftId;
    std::cout << "Enter Aircraft Type: ";
    std::cin >> aircraftType;
    std::cout << "Enter Total Seats: ";
    std::cin >> totalSeats;

    Aircraft newAircraft(aircraftId, aircraftType, totalSeats);
    Database::aircrafts.push_back(newAircraft);
    Database::saveAircrafts();
    std::cout << "Aircraft " << aircraftId << " has been successfully added.\n";
}

void Administrator::updateAircraft() {
    std::string aircraftId;
    std::cout << "--- Update Existing Aircraft ---\n";
    std::cout << "Enter Aircraft ID to Update: ";
    std::cin >> aircraftId;

    for (auto& aircraft : Database::aircrafts) {
        if (aircraft.getAircraftId() == aircraftId) {
            std::string aircraftType;
            int totalSeats;

            std::cout << "Enter New Aircraft Type: ";
            std::cin >> aircraftType;
            std::cout << "Enter New Total Seats: ";
            std::cin >> totalSeats;

            aircraft = Aircraft(aircraftId, aircraftType, totalSeats);
            Database::saveAircrafts();
            std::cout << "Aircraft " << aircraftId << " has been successfully updated.\n";
            return;
        }
    }
    std::cout << "Error: Aircraft not found.\n";
}

void Administrator::removeAircraft() {
    std::string aircraftId;
    std::cout << "--- Remove Aircraft ---\n";
    std::cout << "Enter Aircraft ID to Remove: ";
    std::cin >> aircraftId;

    for (auto it = Database::aircrafts.begin(); it != Database::aircrafts.end(); ++it) {
        if (it->getAircraftId() == aircraftId) {
            Database::aircrafts.erase(it);
            Database::saveAircrafts();
            std::cout << "Aircraft " << aircraftId << " has been successfully removed.\n";
            return;
        }
    }
    std::cout << "Error: Aircraft not found.\n";
}

void Administrator::viewAllAircraft() {
    std::cout << "--- All Aircraft ---\n";
    for (const auto& aircraft : Database::aircrafts) {
        std::cout << "Aircraft ID: " << aircraft.getAircraftId() << "\n";
        std::cout << "Aircraft Type: " << aircraft.getAircraftType() << "\n";
        std::cout << "Total Seats: " << aircraft.getTotalSeats() << "\n";
        std::cout << "-------------------------\n";
    }
}

void Administrator::manageUsers() {
    int choice;
    while (true) {
        std::cout << "--- Manage Users ---\n";
        std::cout << "1. Add New User\n";
        std::cout << "2. Update Existing User\n";
        std::cout << "3. Remove User\n";
        std::cout << "4. View All Users\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            addUser();
        } else if (choice == 2) {
            updateUser();
        } else if (choice == 3) {
            removeUser();
        } else if (choice == 4) {
            viewAllUsers();
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Administrator::addUser() {
    std::string username, password, role;
    std::cout << "--- Add New User ---\n";
    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password;
    std::cout << "Enter Role (Administrator/BookingAgent/Passenger): ";
    std::cin >> role;

    if (role == "Administrator") {
        Database::users.push_back(std::make_shared<Administrator>(username, password));
    } else if (role == "BookingAgent") {
        Database::users.push_back(std::make_shared<BookingAgent>(username, password));
    } else if (role == "Passenger") {
        Database::users.push_back(std::make_shared<Passenger>(username, password));
    } else {
        std::cout << "Error: Invalid role.\n";
        return;
    }
    Database::saveUsers();
    std::cout << "User " << username << " has been successfully added.\n";
}

void Administrator::updateUser() {
    std::string username;
    std::cout << "--- Update Existing User ---\n";
    std::cout << "Enter Username to Update: ";
    std::cin >> username;

    for (auto& user : Database::users) {
        if (user->getUsername() == username) {
            std::string password, role;
            std::cout << "Enter New Password: ";
            std::cin >> password;
            std::cout << "Enter New Role (Administrator/BookingAgent/Passenger): ";
            std::cin >> role;

            user->setPassword(password);
            user->setRole(role);
            Database::saveUsers();
            std::cout << "User " << username << " has been successfully updated.\n";
            return;
        }
    }
    std::cout << "Error: User not found.\n";
}

void Administrator::removeUser() {
    std::string username;
    std::cout << "--- Remove User ---\n";
    std::cout << "Enter Username to Remove: ";
    std::cin >> username;

    for (auto it = Database::users.begin(); it != Database::users.end(); ++it) {
        if ((*it)->getUsername() == username) {
            Database::users.erase(it);
            Database::saveUsers();
            std::cout << "User " << username << " has been successfully removed.\n";
            return;
        }
    }
    std::cout << "Error: User not found.\n";
}

void Administrator::viewAllUsers() {
    std::cout << "--- All Users ---\n";
    for (const auto& user : Database::users) {
        std::cout << "Username: " << user->getUsername() << "\n";
        std::cout << "Role: " << user->getRole() << "\n";
        std::cout << "-------------------------\n";
    }
}

// دوال التقارير
void Administrator::generateReport() {
    int choice;
    while (true) {
        std::cout << "--- Generate Reports ---\n";
        std::cout << "1. Operational Reports\n";
        std::cout << "2. Maintenance Reports\n";
        std::cout << "3. User Activity Reports\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            generateOperationalReport();
        } else if (choice == 2) {
            generateMaintenanceReport();
        } else if (choice == 3) {
            generateUserActivityReport();
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Administrator::generateOperationalReport() {
    std::string monthYear;
    std::cout << "--- Operational Reports ---\n";
    std::cout << "Enter Month and Year for Report (MM-YYYY): ";
    std::cin >> monthYear;

    int totalFlights = 0, completedFlights = 0, delayedFlights = 0, canceledFlights = 0;
    double totalRevenue = 0.0;

    for (const auto& flight : Database::flights) {
        if (flight.getDepartureTime().substr(5, 2) + "-" + flight.getDepartureTime().substr(0, 4) == monthYear) {
            totalFlights++;
            if (flight.getStatus() == "Completed") completedFlights++;
            else if (flight.getStatus() == "Delayed") delayedFlights++;
            else if (flight.getStatus() == "Canceled") canceledFlights++;
        }
    }

    for (const auto& reservation : Database::reservations) {
        totalRevenue += reservation.getTotalCost();
    }

    std::cout << "Report Summary:\n";
    std::cout << "- Total Flights Scheduled: " << totalFlights << "\n";
    std::cout << "- Flights Completed: " << completedFlights << "\n";
    std::cout << "- Flights Delayed: " << delayedFlights << "\n";
    std::cout << "- Flights Canceled: " << canceledFlights << "\n";
    std::cout << "- Total Reservations Made: " << Database::reservations.size() << "\n";
    std::cout << "- Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << "\n";
}

void Administrator::generateMaintenanceReport() {
    std::cout << "--- Maintenance Reports ---\n";
    std::cout << "This feature is under development.\n";
}

void Administrator::generateUserActivityReport() {
    std::cout << "--- User Activity Reports ---\n";
    std::cout << "This feature is under development.\n";
}

void Administrator::logout() {
    std::cout << "Logging out...\n";
    std::cout << "Goodbye, " << getUsername() << "!\n";
}