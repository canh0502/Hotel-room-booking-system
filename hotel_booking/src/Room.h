#ifndef ROOM_H
#define ROOM_H

#include <string>

// Represents a single room in the hotel (FR3.1, Data Model: ROOM / ROOMTYPE)
struct Room {
    int id;
    std::string number;
    std::string type;      // e.g. "Deluxe", "Suite"
    double price;          // price per night
    int capacity;          // max guests
    std::string status;    // "Available", "Occupied", "Cleaning", "Maintenance"

    std::string toCSV() const;
    static Room fromCSV(const std::string& line);
};

#endif
