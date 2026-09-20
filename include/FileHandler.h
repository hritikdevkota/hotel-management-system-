#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <vector>
#include "Room.h"
#include "Customer.h"
#include "Booking.h"
#include "ServiceCharge.h"

class FileHandler {
private:
    const std::string roomsFile = "data/rooms.txt";
    const std::string customersFile = "data/customers.txt";
    const std::string bookingsFile = "data/bookings.txt";
    const std::string servicesFile = "data/services.txt";

public:
    // Save operations
    void saveRooms(const std::vector<Room>& rooms);
    void saveCustomers(const std::vector<Customer>& customers);
    void saveBookings(const std::vector<Booking>& bookings);
    void saveServices(const std::vector<ServiceCharge>& services);

    // Load operations (Marked as const)
    std::vector<Room> loadRooms() const;
    std::vector<Customer> loadCustomers() const;
    std::vector<Booking> loadBookings() const;
    std::vector<ServiceCharge> loadServices() const;
};

#endif // FILE_HANDLER_H