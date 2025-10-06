#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>

class Reservation {
private:
    std::string reservationId;
    std::string passengerId;
    std::string flightNumber;
    std::string seatNumber;
    std::string paymentMethod;
    double totalCost;
    std::string gate;
    std::string boardingTime;

public:
    Reservation(const std::string& rid, const std::string& pid, const std::string& fnum,
                const std::string& seat, const std::string& payment, double cost,
                const std::string& gate, const std::string& boardingTime);

    std::string getReservationId() const;
    std::string getPassengerId() const;
    std::string getFlightNumber() const;
    std::string getSeatNumber() const;
    std::string getPaymentMethod() const;
    double getTotalCost() const;
    std::string getGate() const;
    std::string getBoardingTime() const;
};

#endif