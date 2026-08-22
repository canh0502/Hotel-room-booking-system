#ifndef BOOKING_H
#define BOOKING_H

#include <string>

// Represents a booking made by a guest (FR1.4, Data Model: BOOKING / PAYMENT)
struct Booking {
    int id;
    int roomId;
    std::string guestName;
    std::string guestPhone;
    std::string checkIn;    // format: YYYY-MM-DD
    std::string checkOut;   // format: YYYY-MM-DD
    std::string status;     // "Confirmed", "CheckedIn", "CheckedOut", "Cancelled"
    double amountPaid;

    std::string toCSV() const;
    static Booking fromCSV(const std::string& line);
};

#endif
