#include "Reservation.hpp"

Reservation::Reservation(const std::string& rid, const std::string& pid, const std::string& fnum,
                         const std::string& seat, const std::string& payment, double cost,
                         const std::string& gate, const std::string& boardingTime)
    : reservationId(rid), passengerId(pid), flightNumber(fnum), seatNumber(seat),
      paymentMethod(payment), totalCost(cost), gate(gate), boardingTime(boardingTime) {}

std::string Reservation::getReservationId() const {
    return reservationId;
}

std::string Reservation::getPassengerId() const {
    return passengerId;
}

std::string Reservation::getFlightNumber() const {
    return flightNumber;
}

std::string Reservation::getSeatNumber() const {
    return seatNumber;
}

std::string Reservation::getPaymentMethod() const {
    return paymentMethod;
}

double Reservation::getTotalCost() const {
    return totalCost;
}

std::string Reservation::getGate() const {
    return gate;
}

std::string Reservation::getBoardingTime() const {
    return boardingTime;
}