#ifndef BOOKING_MANAGER_H
#define BOOKING_MANAGER_H

#include <vector>
#include "Booking.h"
#include "Customer.h"
#include "ServiceCharge.h"
#include "RoomManager.h"
#include "FileHandler.h"

class BookingManager {
private:
    std::vector<Booking> bookings;
    std::vector<Customer> customers;
    std::vector<ServiceCharge> services;
    FileHandler fileHandler;

public:
    BookingManager();

    void checkInCustomer(RoomManager& roomMgr);
    void addServiceCharge();
    void checkOutCustomer(RoomManager& roomMgr);
    void viewActiveBookings() const;
    void viewBookingHistory() const;
};

#endif // BOOKING_MANAGER_H