#include <iostream>
#include <limits>
#include "BookingSystem.h"


static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void guestMenu(BookingSystem& sys) {
    int choice;
    do {
        std::cout << "\n--- Guest menu ---\n"
                  << "1. Search available rooms\n"
                  << "2. Book a room\n"
                  << "3. View my bookings\n"
                  << "4. Cancel a booking\n"
                  << "0. Back\n"
                  << "Choice: ";
        if (!(std::cin >> choice)) { clearInput(); continue; }

        if (choice == 1) {
            std::string in, out;
            int guests;
            std::cout << "Check-in (YYYY-MM-DD): "; std::cin >> in;
            std::cout << "Check-out (YYYY-MM-DD): "; std::cin >> out;
            std::cout << "Number of guests: "; std::cin >> guests;
            auto avail = sys.searchAvailableRooms(in, out, guests);
            if (avail.empty()) {
                std::cout << "No rooms available.\n";
            } else {
                for (const auto& r : avail) {
                    std::cout << "Room " << r.id << " (" << r.number << ") - "
                              << r.type << " - $" << r.price << "/night, capacity "
                              << r.capacity << "\n";
                }
            }
        } else if (choice == 2) {
            int roomId;
            std::string name, phone, in, out;
            std::cout << "Room ID: "; std::cin >> roomId;
            std::cout << "Your name: "; std::cin >> name;
            std::cout << "Your phone: "; std::cin >> phone;
            std::cout << "Check-in (YYYY-MM-DD): "; std::cin >> in;
            std::cout << "Check-out (YYYY-MM-DD): "; std::cin >> out;
            if (sys.bookRoom(roomId, name, phone, in, out)) {
                std::cout << "Booking confirmed.\n";
                sys.save();
            } else {
                std::cout << "Room not available for those dates.\n";
            }
        } else if (choice == 3) {
            std::string phone;
            std::cout << "Your phone: "; std::cin >> phone;
            sys.listBookingsByGuestPhone(phone);
        } else if (choice == 4) {
            int id;
            std::cout << "Booking ID to cancel: "; std::cin >> id;
            if (sys.cancelBooking(id)) {
                std::cout << "Booking cancelled.\n";
                sys.save();
            } else {
                std::cout << "Booking not found.\n";
            }
        }
    } while (choice != 0);
}

static void receptionistMenu(BookingSystem& sys) {
    int choice;
    do {
        std::cout << "\n--- Receptionist menu ---\n"
                  << "1. View all bookings\n"
                  << "2. Check-in a guest\n"
                  << "3. Check-out a guest\n"
                  << "4. Record a payment\n"
                  << "0. Back\n"
                  << "Choice: ";
        if (!(std::cin >> choice)) { clearInput(); continue; }

        if (choice == 1) {
            sys.listAllBookings();
        } else if (choice == 2) {
            int id;
            std::cout << "Booking ID: "; std::cin >> id;
            std::cout << (sys.checkIn(id) ? "Checked in.\n" : "Failed (check booking status).\n");
            sys.save();
        } else if (choice == 3) {
            int id;
            std::cout << "Booking ID: "; std::cin >> id;
            std::cout << (sys.checkOut(id) ? "Checked out.\n" : "Failed (check booking status).\n");
            sys.save();
        } else if (choice == 4) {
            int id;
            double amount;
            std::cout << "Booking ID: "; std::cin >> id;
            std::cout << "Amount: "; std::cin >> amount;
            std::cout << (sys.makePayment(id, amount) ? "Payment recorded.\n" : "Booking not found.\n");
            sys.save();
        }
    } while (choice != 0);
}

static void adminMenu(BookingSystem& sys) {
    int choice;
    do {
        std::cout << "\n--- Admin menu ---\n"
                  << "1. List all rooms\n"
                  << "2. Add a room\n"
                  << "3. Remove a room\n"
                  << "4. View revenue / occupancy report\n"
                  << "0. Back\n"
                  << "Choice: ";
        if (!(std::cin >> choice)) { clearInput(); continue; }

        if (choice == 1) {
            sys.listAllRooms();
        } else if (choice == 2) {
            std::string number, type;
            double price;
            int capacity;
            std::cout << "Room number: "; std::cin >> number;
            std::cout << "Room type: "; std::cin >> type;
            std::cout << "Price/night: "; std::cin >> price;
            std::cout << "Capacity: "; std::cin >> capacity;
            sys.addRoom(number, type, price, capacity);
            sys.save();
            std::cout << "Room added.\n";
        } else if (choice == 3) {
            int id;
            std::cout << "Room ID: "; std::cin >> id;
            std::cout << (sys.removeRoom(id) ? "Room removed.\n" : "Room not found.\n");
            sys.save();
        } else if (choice == 4) {
            sys.printRevenueReport();
        }
    } while (choice != 0);
}

int main() {
    BookingSystem sys("data/rooms.csv", "data/bookings.csv");
    sys.load();

    int choice;
    do {
        std::cout << "\n=== Hotel Room Booking System ===\n"
                  << "1. Guest\n"
                  << "2. Receptionist\n"
                  << "3. Admin\n"
                  << "0. Exit\n"
                  << "Choice: ";
        if (!(std::cin >> choice)) { clearInput(); continue; }

        switch (choice) {
            case 1: guestMenu(sys); break;
            case 2: receptionistMenu(sys); break;
            case 3: adminMenu(sys); break;
        }
    } while (choice != 0);

    sys.save();
    std::cout << "Goodbye.\n";
    return 0;
}
