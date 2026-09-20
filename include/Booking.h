#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
private:
    int bookingId;
    int roomNumber;
    std::string customerId;
    std::string customerName;
    std::string checkInDate;
    std::string checkOutDate;
    int daysOfStay;
    double roomRate;
    bool isCompleted;

public:
    Booking();
    Booking(int id, int roomNum, std::string custId, std::string custName, 
            std::string checkIn, int days, double rate, bool completed = false);

    // Getters
    int getBookingId() const;
    int getRoomNumber() const;
    std::string getCustomerId() const;
    std::string getCustomerName() const;
    std::string getCheckInDate() const;
    std::string getCheckOutDate() const;
    int getDaysOfStay() const;
    double getRoomRate() const;
    bool getIsCompleted() const;

    // Setters
    void markCompleted(const std::string& outDate);

    // Calculation
    double calculateRoomTotal() const;

    // File I/O
    std::string toCSV() const;
    static Booking fromCSV(const std::string& line);
};

#endif // BOOKING_H