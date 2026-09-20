#include "../include/ConsoleUI.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void ConsoleUI::printHeader(const string& title) {
    printDivider();
    cout << "  " << title << "\n";
    printDivider();
}

void ConsoleUI::printDivider() {
    cout << "=================================================================\n";
}

void ConsoleUI::printMenu() {
    printHeader("HOTEL MANAGEMENT SYSTEM - MAIN MENU");
    cout << "  1. Room Management (Add / View / Search / Edit)\n";
    cout << "  2. Customer Check-In\n";
    cout << "  3. Add Room Service / Service Charges\n";
    cout << "  4. Customer Check-Out & Billing (Invoice Generation)\n";
    cout << "  5. View Active Bookings\n";
    cout << "  6. View Booking History\n";
    cout << "  7. Generate Occupancy & Revenue Reports\n";
    cout << "  8. Save & Exit\n";
    printDivider();
}

void ConsoleUI::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}