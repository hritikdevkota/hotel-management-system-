#include "../include/Booking.h"
#include <sstream>
#include <vector>

using namespace std;

Booking::Booking()
    : bookingId(0), roomNumber(0), customerId(""), customerName(""),
      checkInDate(""), checkOutDate("N/A"), daysOfStay(1), roomRate(0.0), isCompleted(false) {}

Booking::Booking(int id, int roomNum, string custId, string custName,
                 string checkIn, int days, double rate, bool completed)
    : bookingId(id), roomNumber(roomNum), customerId(custId), customerName(custName),
      checkInDate(checkIn), checkOutDate("N/A"), daysOfStay(days), roomRate(rate), isCompleted(completed) {}

int Booking::getBookingId() const { return bookingId; }
int Booking::getRoomNumber() const { return roomNumber; }
string Booking::getCustomerId() const { return customerId; }
string Booking::getCustomerName() const { return customerName; }
string Booking::getCheckInDate() const { return checkInDate; }
string Booking::getCheckOutDate() const { return checkOutDate; }
int Booking::getDaysOfStay() const { return daysOfStay; }
double Booking::getRoomRate() const { return roomRate; }
bool Booking::getIsCompleted() const { return isCompleted; }

void Booking::markCompleted(const string& outDate) {
    checkOutDate = outDate;
    isCompleted = true;
}

double Booking::calculateRoomTotal() const {
    return daysOfStay * roomRate;
}

string Booking::toCSV() const {
    return to_string(bookingId) + "," + to_string(roomNumber) + "," + customerId + "," +
           customerName + "," + checkInDate + "," + checkOutDate + "," +
           to_string(daysOfStay) + "," + to_string(roomRate) + "," + (isCompleted ? "1" : "0");
}

Booking Booking::fromCSV(const string& line) {
    stringstream ss(line);
    string item;
    vector<string> tokens;

    while (getline(ss, item, ',')) {
        tokens.push_back(item);
    }

    if (tokens.size() >= 9) {
        int id = stoi(tokens[0]);
        int rNum = stoi(tokens[1]);
        string cId = tokens[2];
        string cName = tokens[3];
        string inDate = tokens[4];
        string outDate = tokens[5];
        int days = stoi(tokens[6]);
        double rate = stod(tokens[7]);
        bool completed = (tokens[8] == "1");

        Booking b(id, rNum, cId, cName, inDate, days, rate, completed);
        if (completed) {
            b.markCompleted(outDate);
        }
        return b;
    }
    return Booking();
}