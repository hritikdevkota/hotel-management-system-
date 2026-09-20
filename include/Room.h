#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
private:
    int roomNumber;
    std::string type;     // Single, Double, Deluxe, Suite
    double pricePerNight;
    bool isOccupied;

public:
    Room();
    Room(int num, std::string t, double price, bool occupied = false);

    // Getters
    int getRoomNumber() const;
    std::string getType() const;
    double getPricePerNight() const;
    bool getIsOccupied() const;

    // Setters
    void setOccupied(bool status);
    void setPrice(double price);
    void setType(const std::string& t);

    // Data Serialization for File I/O
    std::string toCSV() const;
    static Room fromCSV(const std::string& line);
};

#endif // ROOM_H