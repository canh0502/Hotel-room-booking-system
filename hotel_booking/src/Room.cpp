#include "Room.h"
#include <sstream>
#include <vector>

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) tokens.push_back(item);
    return tokens;
}

std::string Room::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << number << "," << type << "," << price << ","
        << capacity << "," << status;
    return oss.str();
}

Room Room::fromCSV(const std::string& line) {
    std::vector<std::string> t = split(line, ',');
    Room r;
    r.id = std::stoi(t[0]);
    r.number = t[1];
    r.type = t[2];
    r.price = std::stod(t[3]);
    r.capacity = std::stoi(t[4]);
    r.status = t[5];
    return r;
}
