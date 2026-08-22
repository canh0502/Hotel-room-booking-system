#include "BookingSystem.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

BookingSystem::BookingSystem(const std::string& roomFile, const std::string& bookingFile)
    : roomFile(roomFile), bookingFile(bookingFile) {}

int BookingSystem::nextRoomId() const {
    int maxId = 0;
    for (const auto& r : rooms) maxId = std::max(maxId, r.id);
    return maxId + 1;
}

int BookingSystem::nextBookingId() const {
    int maxId = 0;
    for (const auto& b : bookings) maxId = std::max(maxId, b.id);
    return maxId + 1;
}
bool BookingSystem::isRoomAvailable(int roomId, const std::string& checkIn,
                                     const std::string& checkOut,
                                     int ignoreBookingId) const {
    for (const auto& b : bookings) {
        if (b.roomId != roomId) continue;
        if (b.id == ignoreBookingId) continue;
        if (b.status == "Cancelled") continue;
        bool overlap = (checkIn < b.checkOut) && (checkOut > b.checkIn);
        if (overlap) return false;
    }
    return true;
}

void BookingSystem::load() {
    rooms.clear();
    bookings.clear();
    std::ifstream rf(roomFile);
    std::string line;
    while (std::getline(rf, line)) {
        if (!line.empty()) rooms.push_back(Room::fromCSV(line));
    }
    std::ifstream bf(bookingFile);
    while (std::getline(bf, line)) {
        if (!line.empty()) bookings.push_back(Booking::fromCSV(line));
    }
}

void BookingSystem::save() const {
    std::ofstream rf(roomFile);
    for (const auto& r : rooms) rf << r.toCSV() << "\n";
    std::ofstream bf(bookingFile);
    for (const auto& b : bookings) bf << b.toCSV() << "\n";
}

std::vector<Room> BookingSystem::searchAvailableRooms(const std::string& checkIn,
                                                       const std::string& checkOut,
                                                       int guests) const {
    std::vector<Room> result;
    for (const auto& r : rooms) {
        if (r.capacity < guests) continue;
        if (r.status == "Maintenance") continue;
        if (isRoomAvailable(r.id, checkIn, checkOut)) result.push_back(r);
    }
    return result;
}

bool BookingSystem::bookRoom(int roomId, const std::string& guestName,
                              const std::string& guestPhone,
                              const std::string& checkIn, const std::string& checkOut) {
    if (!isRoomAvailable(roomId, checkIn, checkOut)) return false;
    Booking b;
    b.id = nextBookingId();
    b.roomId = roomId;
    b.guestName = guestName;
    b.guestPhone = guestPhone;
    b.checkIn = checkIn;
    b.checkOut = checkOut;
    b.status = "Confirmed";
    b.amountPaid = 0.0;
    bookings.push_back(b);
    return true;
}

bool BookingSystem::cancelBooking(int bookingId) {
    for (auto& b : bookings) {
        if (b.id == bookingId) {
            b.status = "Cancelled";
            return true;
        }
    }
    return false;
}

void BookingSystem::listBookingsByGuestPhone(const std::string& phone) const {
    std::cout << std::left << std::setw(6) << "ID" << std::setw(8) << "Room"
              << std::setw(12) << "CheckIn" << std::setw(12) << "CheckOut"
              << std::setw(12) << "Status" << "Paid\n";
    for (const auto& b : bookings) {
        if (b.guestPhone != phone) continue;
        std::cout << std::left << std::setw(6) << b.id << std::setw(8) << b.roomId
                  << std::setw(12) << b.checkIn << std::setw(12) << b.checkOut
                  << std::setw(12) << b.status << b.amountPaid << "\n";
    }
}

void BookingSystem::listAllBookings() const {
    std::cout << std::left << std::setw(6) << "ID" << std::setw(8) << "Room"
              << std::setw(16) << "Guest" << std::setw(12) << "CheckIn"
              << std::setw(12) << "CheckOut" << "Status\n";
    for (const auto& b : bookings) {
        std::cout << std::left << std::setw(6) << b.id << std::setw(8) << b.roomId
                  << std::setw(16) << b.guestName << std::setw(12) << b.checkIn
                  << std::setw(12) << b.checkOut << b.status << "\n";
    }
}

bool BookingSystem::checkIn(int bookingId) {
    for (auto& b : bookings) {
        if (b.id == bookingId && b.status == "Confirmed") {
            b.status = "CheckedIn";
            for (auto& r : rooms) {
                if (r.id == b.roomId) r.status = "Occupied";
            }
            return true;
        }
    }
    return false;
}

bool BookingSystem::checkOut(int bookingId) {
    for (auto& b : bookings) {
        if (b.id == bookingId && b.status == "CheckedIn") {
            b.status = "CheckedOut";
            for (auto& r : rooms) {
                if (r.id == b.roomId) r.status = "Cleaning";
            }
            return true;
        }
    }
    return false;
}

bool BookingSystem::makePayment(int bookingId, double amount) {
    for (auto& b : bookings) {
        if (b.id == bookingId) {
            b.amountPaid += amount;
            return true;
        }
    }
    return false;
}

void BookingSystem::addRoom(const std::string& number, const std::string& type,
                             double price, int capacity) {
    Room r;
    r.id = nextRoomId();
    r.number = number;
    r.type = type;
    r.price = price;
    r.capacity = capacity;
    r.status = "Available";
    rooms.push_back(r);
}

bool BookingSystem::removeRoom(int roomId) {
    auto it = std::remove_if(rooms.begin(), rooms.end(),
                              [roomId](const Room& r) { return r.id == roomId; });
    if (it == rooms.end()) return false;
    rooms.erase(it, rooms.end());
    return true;
}

void BookingSystem::listAllRooms() const {
    std::cout << std::left << std::setw(6) << "ID" << std::setw(10) << "Number"
              << std::setw(12) << "Type" << std::setw(10) << "Price"
              << std::setw(10) << "Capacity" << "Status\n";
    for (const auto& r : rooms) {
        std::cout << std::left << std::setw(6) << r.id << std::setw(10) << r.number
                  << std::setw(12) << r.type << std::setw(10) << r.price
                  << std::setw(10) << r.capacity << r.status << "\n";
    }
}

void BookingSystem::printRevenueReport() const {
    double total = 0;
    int occupied = 0;
    for (const auto& b : bookings) {
        if (b.status != "Cancelled") total += b.amountPaid;
    }
    for (const auto& r : rooms) {
        if (r.status == "Occupied") occupied++;
    }
    std::cout << "Total revenue: " << total << "\n";
    std::cout << "Occupied rooms: " << occupied << " / " << rooms.size() << "\n";
    if (!rooms.empty()) {
        double rate = (double)occupied / rooms.size() * 100.0;
        std::cout << "Occupancy rate: " << rate << "%\n";
    }
}
