#ifndef ROOM_H
#define ROOM_H

#include <string>

struct Room {
    int id;
    std::string number;
    std::string type;     
    double price;      
    int capacity;       
    std::string status;    

    std::string toCSV() const;
    static Room fromCSV(const std::string& line);
};

#endif
