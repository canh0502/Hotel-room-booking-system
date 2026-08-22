#include "Booking.h"
#include <sstream>
#include <vector>

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) tokens.push_back(item);
    return tokens;
}

std::string Booking::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << roomId << "," << guestName << "," << guestPhone << ","
        << checkIn << "," << checkOut << "," << status << "," << amountPaid;
    return oss.str();
}

Booking Booking::fromCSV(const std::string& line) {
    std::vector<std::string> t = split(line, ',');
    Booking b;
    b.id = std::stoi(t[0]);
    b.roomId = std::stoi(t[1]);
    b.guestName = t[2];
    b.guestPhone = t[3];
    b.checkIn = t[4];
    b.checkOut = t[5];
    b.status = t[6];
    b.amountPaid = std::stod(t[7]);
    return b;
}
