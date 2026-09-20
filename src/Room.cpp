#include "../include/Room.h"
#include <sstream>
#include <vector>

using namespace std;

Room::Room() : roomNumber(0), type("Single"), pricePerNight(0.0), isOccupied(false) {}

Room::Room(int num, string t, double price, bool occupied)
    : roomNumber(num), type(t), pricePerNight(price), isOccupied(occupied) {}

int Room::getRoomNumber() const { return roomNumber; }
string Room::getType() const { return type; }
double Room::getPricePerNight() const { return pricePerNight; }
bool Room::getIsOccupied() const { return isOccupied; }

void Room::setOccupied(bool status) { isOccupied = status; }
void Room::setPrice(double price) { pricePerNight = price; }
void Room::setType(const string& t) { type = t; }

string Room::toCSV() const {
    return to_string(roomNumber) + "," + type + "," + 
           to_string(pricePerNight) + "," + (isOccupied ? "1" : "0");
}

Room Room::fromCSV(const string& line) {
    stringstream ss(line);
    string item;
    vector<string> tokens;

    while (getline(ss, item, ',')) {
        tokens.push_back(item);
    }

    if (tokens.size() >= 4) {
        int num = stoi(tokens[0]);
        string t = tokens[1];
        double price = stod(tokens[2]);
        bool occupied = (tokens[3] == "1");
        return Room(num, t, price, occupied);
    }
    return Room();
}