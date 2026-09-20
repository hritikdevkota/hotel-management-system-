#include "../include/BookingManager.h"
#include "../include/InputValidator.h"
#include "../include/ConsoleUI.h"
#include <iostream>
#include <iomanip>

using namespace std;

BookingManager::BookingManager() {
    bookings = fileHandler.loadBookings();
    customers = fileHandler.loadCustomers();
    services = fileHandler.loadServices();
}

void BookingManager::checkInCustomer(RoomManager& roomMgr) {
    ConsoleUI::printHeader("CUSTOMER CHECK-IN");
    int roomNum = InputValidator::getValidInt("Enter Room Number for Check-In: ");
    Room* room = roomMgr.findRoom(roomNum);

    if (room == nullptr) {
        cout << "Error: Room " << roomNum << " does not exist.\n";
        return;
    }
    if (room->getIsOccupied()) {
        cout << "Error: Room " << roomNum << " is currently occupied!\n";
        return;
    }

    string cId = InputValidator::getValidString("Enter Customer ID/Passport No: ");
    string name = InputValidator::getValidString("Enter Customer Full Name: ");
    string phone = InputValidator::getValidPhone("Enter Customer Phone Number: ");
    string checkInDate = InputValidator::getValidString("Enter Check-In Date (YYYY-MM-DD): ");
    int days = InputValidator::getValidInt("Enter Expected Duration of Stay (Days): ");

    int newBookingId = bookings.empty() ? 101 : bookings.back().getBookingId() + 1;

    Customer newCust(cId, name, phone);
    Booking newBooking(newBookingId, roomNum, cId, name, checkInDate, days, room->getPricePerNight());

    customers.push_back(newCust);
    bookings.push_back(newBooking);
    roomMgr.setRoomStatus(roomNum, true);

    fileHandler.saveCustomers(customers);
    fileHandler.saveBookings(bookings);

    cout << "\nCheck-In Successful! Booking ID: " << newBookingId << "\n";
}

void BookingManager::addServiceCharge() {
    ConsoleUI::printHeader("ADD SERVICE CHARGE (ROOM SERVICE / LAUNDRY)");
    int roomNum = InputValidator::getValidInt("Enter Room Number: ");

    bool activeFound = false;
    for (const auto& b : bookings) {
        if (b.getRoomNumber() == roomNum && !b.getIsCompleted()) {
            activeFound = true;
            break;
        }
    }

    if (!activeFound) {
        cout << "Error: No active check-in found for Room " << roomNum << "\n";
        return;
    }

    string desc = InputValidator::getValidString("Enter Service Description (e.g., Dinner, Laundry): ");
    double amt = InputValidator::getValidDouble("Enter Charge Amount ($): ");

    int newChargeId = services.empty() ? 1 : services.back().getChargeId() + 1;
    services.push_back(ServiceCharge(newChargeId, roomNum, desc, amt));
    fileHandler.saveServices(services);

    cout << "\nService charge added successfully!\n";
}

void BookingManager::checkOutCustomer(RoomManager& roomMgr) {
    ConsoleUI::printHeader("CUSTOMER CHECK-OUT & BILLING");
    int roomNum = InputValidator::getValidInt("Enter Room Number for Check-Out: ");

    Booking* activeBooking = nullptr;
    for (auto& b : bookings) {
        if (b.getRoomNumber() == roomNum && !b.getIsCompleted()) {
            activeBooking = &b;
            break;
        }
    }

    if (activeBooking == nullptr) {
        cout << "Error: No active booking found for Room " << roomNum << "\n";
        return;
    }

    string outDate = InputValidator::getValidString("Enter Check-Out Date (YYYY-MM-DD): ");
    activeBooking->markCompleted(outDate);
    roomMgr.setRoomStatus(roomNum, false);

    // Calculate extra service charges
    double totalServiceCost = 0.0;
    vector<ServiceCharge> roomServices;
    for (const auto& s : services) {
        if (s.getRoomNumber() == roomNum) {
            roomServices.push_back(s);
            totalServiceCost += s.getAmount();
        }
    }

    double roomCost = activeBooking->calculateRoomTotal();
    double subtotal = roomCost + totalServiceCost;
    double tax = subtotal * 0.13; // 13% Tax
    double grandTotal = subtotal + tax;

    // Print Invoice Receipt
    ConsoleUI::printHeader("OFFICIAL INVOICE RECEIPT");
    cout << "Booking ID    : " << activeBooking->getBookingId() << "\n";
    cout << "Customer Name : " << activeBooking->getCustomerName() << "\n";
    cout << "Room Number   : " << activeBooking->getRoomNumber() << "\n";
    cout << "Check-In Date : " << activeBooking->getCheckInDate() << "\n";
    cout << "Check-Out Date: " << activeBooking->getCheckOutDate() << "\n";
    ConsoleUI::printDivider();

    cout << left << setw(35) << "Room Charge (" + to_string(activeBooking->getDaysOfStay()) + " nights @ $" + to_string(activeBooking->getRoomRate()) + ")"
         << "$" << fixed << setprecision(2) << roomCost << "\n";

    for (const auto& s : roomServices) {
        cout << left << setw(35) << (" Service: " + s.getDescription())
             << "$" << fixed << setprecision(2) << s.getAmount() << "\n";
    }

    ConsoleUI::printDivider();
    cout << left << setw(35) << "Subtotal:" << "$" << subtotal << "\n";
    cout << left << setw(35) << "Tax (13%):" << "$" << tax << "\n";
    cout << left << setw(35) << "GRAND TOTAL:" << "$" << grandTotal << "\n";
    ConsoleUI::printDivider();

    fileHandler.saveBookings(bookings);
    cout << "\nCheck-out completed and record saved successfully!\n";
}

void BookingManager::viewActiveBookings() const {
    ConsoleUI::printHeader("ACTIVE BOOKINGS");
    cout << left << setw(12) << "Booking ID"
         << setw(10) << "Room No"
         << setw(20) << "Customer Name"
         << setw(15) << "Check-In"
         << setw(10) << "Days" << "\n";
    ConsoleUI::printDivider();

    bool found = false;
    for (const auto& b : bookings) {
        if (!b.getIsCompleted()) {
            found = true;
            cout << left << setw(12) << b.getBookingId()
                 << setw(10) << b.getRoomNumber()
                 << setw(20) << b.getCustomerName()
                 << setw(15) << b.getCheckInDate()
                 << setw(10) << b.getDaysOfStay() << "\n";
        }
    }
    if (!found) cout << "No active bookings currently.\n";
    ConsoleUI::printDivider();
}

void BookingManager::viewBookingHistory() const {
    ConsoleUI::printHeader("BOOKING HISTORY");
    cout << left << setw(12) << "Booking ID"
         << setw(10) << "Room No"
         << setw(20) << "Customer Name"
         << setw(15) << "Status" << "\n";
    ConsoleUI::printDivider();

    for (const auto& b : bookings) {
        cout << left << setw(12) << b.getBookingId()
             << setw(10) << b.getRoomNumber()
             << setw(20) << b.getCustomerName()
             << setw(15) << (b.getIsCompleted() ? "Completed" : "Active") << "\n";
    }
    ConsoleUI::printDivider();
}