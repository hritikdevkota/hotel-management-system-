#include "../include/ReportGenerator.h"
#include "../include/ConsoleUI.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ReportGenerator::generateOccupancyReport(const RoomManager& roomMgr) {
    const auto& rooms = roomMgr.getRooms();
    int total = rooms.size();

    if (total == 0) {
        cout << "\nNo rooms registered to evaluate occupancy.\n";
        return;
    }

    int occupied = 0;
    for (const auto& r : rooms) {
        if (r.getIsOccupied()) occupied++;
    }

    double rate = (static_cast<double>(occupied) / total) * 100.0;

    ConsoleUI::printHeader("HOTEL OCCUPANCY ANALYTICS");
    cout << "Total Registered Rooms : " << total << "\n";
    cout << "Occupied Rooms         : " << occupied << "\n";
    cout << "Available Rooms        : " << (total - occupied) << "\n";
    cout << "Current Occupancy Rate : " << fixed << setprecision(2) << rate << "%\n";
    ConsoleUI::printDivider();
}

void ReportGenerator::generateRevenueReport(const FileHandler& fileHandler) {
    auto bookings = fileHandler.loadBookings();
    auto services = fileHandler.loadServices();

    double totalRoomRevenue = 0.0;
    double totalServiceRevenue = 0.0;

    for (const auto& b : bookings) {
        if (b.getIsCompleted()) {
            totalRoomRevenue += b.calculateRoomTotal();
        }
    }

    for (const auto& s : services) {
        totalServiceRevenue += s.getAmount();
    }

    double totalRevenue = totalRoomRevenue + totalServiceRevenue;

    ConsoleUI::printHeader("HOTEL REVENUE SUMMARY");
    cout << "Completed Room Revenue   : $" << fixed << setprecision(2) << totalRoomRevenue << "\n";
    cout << "Total Service Charges    : $" << fixed << setprecision(2) << totalServiceRevenue << "\n";
    cout << "Total Realized Revenue   : $" << fixed << setprecision(2) << totalRevenue << "\n";
    ConsoleUI::printDivider();
}