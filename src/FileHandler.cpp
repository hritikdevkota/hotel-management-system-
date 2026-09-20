#include "FileHandler.h"
#include <fstream>
#include <string>
#include <vector>

// --- LOAD OPERATIONS ---

std::vector<Room> FileHandler::loadRooms() const {
    std::vector<Room> rooms;
    std::ifstream inFile(roomsFile);
    if (!inFile) return rooms;

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            rooms.push_back(Room::fromCSV(line));
        }
    }
    inFile.close();
    return rooms;
}

std::vector<Customer> FileHandler::loadCustomers() const {
    std::vector<Customer> customers;
    std::ifstream inFile(customersFile);
    if (!inFile) return customers;

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            customers.push_back(Customer::fromCSV(line));
        }
    }
    inFile.close();
    return customers;
}

std::vector<Booking> FileHandler::loadBookings() const {
    std::vector<Booking> bookings;
    std::ifstream inFile(bookingsFile);
    if (!inFile) return bookings;

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            bookings.push_back(Booking::fromCSV(line));
        }
    }
    inFile.close();
    return bookings;
}

std::vector<ServiceCharge> FileHandler::loadServices() const {
    std::vector<ServiceCharge> services;
    std::ifstream inFile(servicesFile);
    if (!inFile) return services;

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            services.push_back(ServiceCharge::fromCSV(line));
        }
    }
    inFile.close();
    return services;
}

// --- SAVE OPERATIONS ---

void FileHandler::saveRooms(const std::vector<Room>& rooms) {
    std::ofstream outFile(roomsFile, std::ios::trunc);
    if (!outFile) return;

    for (const auto& room : rooms) {
        outFile << room.toCSV() << '\n';
    }
    outFile.close();
}

void FileHandler::saveCustomers(const std::vector<Customer>& customers) {
    std::ofstream outFile(customersFile, std::ios::trunc);
    if (!outFile) return;

    for (const auto& customer : customers) {
        outFile << customer.toCSV() << '\n';
    }
    outFile.close();
}

void FileHandler::saveBookings(const std::vector<Booking>& bookings) {
    std::ofstream outFile(bookingsFile, std::ios::trunc);
    if (!outFile) return;

    for (const auto& booking : bookings) {
        outFile << booking.toCSV() << '\n';
    }
    outFile.close();
}

void FileHandler::saveServices(const std::vector<ServiceCharge>& services) {
    std::ofstream outFile(servicesFile, std::ios::trunc);
    if (!outFile) return;

    for (const auto& service : services) {
        outFile << service.toCSV() << '\n';
    }
    outFile.close();
}