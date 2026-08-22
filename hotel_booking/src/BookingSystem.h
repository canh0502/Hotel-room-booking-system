#ifndef BOOKING_SYSTEM_H
#define BOOKING_SYSTEM_H

#include <vector>
#include <string>
#include "Room.h"
#include "Booking.h"

class BookingSystem {
private:
    std::vector<Room> rooms;
    std::vector<Booking> bookings;
    std::string roomFile;
    std::string bookingFile;

    int nextRoomId() const;
    int nextBookingId() const;
    bool isRoomAvailable(int roomId, const std::string& checkIn,
                          const std::string& checkOut, int ignoreBookingId = -1) const;

public:
    BookingSystem(const std::string& roomFile, const std::string& bookingFile);

    void load();
    void save() const;

    std::vector<Room> searchAvailableRooms(const std::string& checkIn,
                                            const std::string& checkOut,
                                            int guests) const;
    bool bookRoom(int roomId, const std::string& guestName,
                  const std::string& guestPhone, const std::string& checkIn,
                  const std::string& checkOut);
    bool cancelBooking(int bookingId);
    void listBookingsByGuestPhone(const std::string& phone) const;

    void listAllBookings() const;
    bool checkIn(int bookingId);
    bool checkOut(int bookingId);
    bool makePayment(int bookingId, double amount);

    void addRoom(const std::string& number, const std::string& type,
                 double price, int capacity);
    bool removeRoom(int roomId);
    void listAllRooms() const;
    void printRevenueReport() const;
};

#endif
