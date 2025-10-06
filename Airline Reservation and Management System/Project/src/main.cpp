#include "Administrator.hpp"
#include "BookingAgent.hpp"
#include "Passenger.hpp"
#include "Database.hpp"
#include <iostream>
#include <limits>

int main()
{
    // تحميل جميع البيانات عند بدء البرنامج
    Database::loadUsers();
    Database::loadFlights();
    Database::loadReservations();
    Database::loadAircrafts();

    int roleChoice;
    std::string username, password;
    int adminChoice, agentChoice, passengerChoice;

    while (true)
    {
        std::cout << "\nWelcome to Airline Reservation and Management System\n";
        std::cout << "Please select your role:\n";
        std::cout << "1. Administrator\n";
        std::cout << "2. Booking Agent\n";
        std::cout << "3. Passenger\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> roleChoice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (roleChoice == 4)
        {
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        }

        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (roleChoice == 1)
        {
            if (Database::validateUser(username, password))
            {
                Administrator admin(username, password);
                while (true)
                {
                    admin.displayMenu();
                    std::cout << "Enter choice: ";
                    std::cin >> adminChoice;

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (adminChoice == 1)
                    {
                        admin.manageFlights();
                    }
                    else if (adminChoice == 2)
                    {
                        admin.manageAircraft();
                    }
                    else if (adminChoice == 3)
                    {
                        admin.manageUsers();
                    }
                    else if (adminChoice == 4)
                    {
                        admin.generateReport();
                    }
                    else if (adminChoice == 5)
                    {
                        admin.logout();
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
            else
            {
                std::cout << "Invalid username or password.\n";
            }
        }
        else if (roleChoice == 2)
        {
            if (Database::validateUser(username, password))
            {
                BookingAgent agent(username, password);
                while (true)
                {
                    agent.displayMenu();
                    std::cout << "Enter choice: ";
                    std::cin >> agentChoice;

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (agentChoice == 1)
                    {
                        agent.searchFlights();
                    }
                    else if (agentChoice == 2)
                    {
                        agent.bookFlight();
                    }
                    else if (agentChoice == 3)
                    {
                        agent.modifyReservation();
                    }
                    else if (agentChoice == 4)
                    {
                        agent.cancelReservation();
                    }
                    else if (agentChoice == 5)
                    {
                        std::cout << "Logging out...\n";
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
            else
            {
                std::cout << "Invalid username or password.\n";
            }
        }
        else if (roleChoice == 3)
        {
            if (Database::validateUser(username, password))
            {
                Passenger passenger(username, password);
                while (true)
                {
                    passenger.displayMenu();
                    std::cout << "Enter choice: ";
                    std::cin >> passengerChoice;

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (passengerChoice == 1)
                    {
                        passenger.searchFlights();
                    }
                    else if (passengerChoice == 2)
                    {
                        passenger.viewReservations();
                    }
                    else if (passengerChoice == 3)
                    {
                        passenger.checkIn();
                    }
                    else if (passengerChoice == 4)
                    {
                        std::cout << "Logging out...\n";
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
            else
            {
                std::cout << "Invalid username or password.\n";
            }
        }
        else
        {
            std::cout << "Invalid role choice. Please try again.\n";
        }
    }

    return 0;
}