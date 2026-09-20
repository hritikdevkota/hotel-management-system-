#include "../include/ConsoleUI.h"
#include "../include/InputValidator.h"
#include "../include/RoomManager.h"
#include "../include/BookingManager.h"
#include "../include/ReportGenerator.h"
#include "../include/FileHandler.h"
#include <iostream>

using namespace std;

int main() {
    // Initialize managers and services
    RoomManager roomMgr;
    BookingManager bookingMgr;
    FileHandler fileHandler;

    while (true) {
        ConsoleUI::printMenu();
        int choice = InputValidator::getValidInt("Select an option (1-8): ");

        switch (choice) {
            case 1: {
                // Room Sub-Menu
                ConsoleUI::printHeader("ROOM MANAGEMENT");
                cout << "  1. Add New Room\n";
                cout << "  2. View All Rooms\n";
                cout << "  3. Search Room Details\n";
                cout << "  4. Update Room Price\n";
                ConsoleUI::printDivider();
                
                int subChoice = InputValidator::getValidInt("Select an option (1-4): ");
                if (subChoice == 1) roomMgr.addRoom();
                else if (subChoice == 2) roomMgr.displayAllRooms();
                else if (subChoice == 3) roomMgr.searchRoom();
                else if (subChoice == 4) roomMgr.updateRoomPrice();
                else cout << "Invalid selection.\n";
                break;
            }
            case 2:
                bookingMgr.checkInCustomer(roomMgr);
                break;
            case 3:
                bookingMgr.addServiceCharge();
                break;
            case 4:
                bookingMgr.checkOutCustomer(roomMgr);
                break;
            case 5:
                bookingMgr.viewActiveBookings();
                break;
            case 6:
                bookingMgr.viewBookingHistory();
                break;
            case 7: {
                // Analytics Sub-Menu
                ConsoleUI::printHeader("REPORTS & ANALYTICS");
                cout << "  1. Occupancy Percentage Report\n";
                cout << "  2. Revenue Summary Report\n";
                ConsoleUI::printDivider();

                int reportChoice = InputValidator::getValidInt("Select an option (1-2): ");
                if (reportChoice == 1) ReportGenerator::generateOccupancyReport(roomMgr);
                else if (reportChoice == 2) ReportGenerator::generateRevenueReport(fileHandler);
                else cout << "Invalid selection.\n";
                break;
            }
            case 8:
                cout << "\nSaving all data and exiting system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid menu choice! Please select between 1 and 8.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
        ConsoleUI::clearConsole();
    }

    return 0;
}