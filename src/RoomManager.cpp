#include "../include/RoomManager.h"
#include "../include/InputValidator.h"
#include "../include/ConsoleUI.h"
#include <iostream>
#include <iomanip>

using namespace std;

RoomManager::RoomManager() {
    rooms = fileHandler.loadRooms();
}

void RoomManager::addRoom() {
    ConsoleUI::printHeader("ADD NEW ROOM");
    int roomNum = InputValidator::getValidInt("Enter Room Number: ");

    for (const auto& r : rooms) {
        if (r.getRoomNumber() == roomNum) {
            cout << "Error: Room number " << roomNum << " already exists!\n";
            return;
        }
    }

    string type = InputValidator::getValidString("Enter Room Type (Single/Double/Deluxe/Suite): ");
    double price = InputValidator::getValidDouble("Enter Price per Night ($): ");

    rooms.push_back(Room(roomNum, type, price));
    saveChanges();
    cout << "\nRoom " << roomNum << " successfully added and saved!\n";
}

void RoomManager::displayAllRooms() const {
    if (rooms.empty()) {
        cout << "\nNo rooms registered in the system.\n";
        return;
    }

    ConsoleUI::printHeader("ALL ROOM RECORDS");
    cout << left << setw(12) << "Room No" 
         << setw(18) << "Type" 
         << setw(18) << "Price/Night" 
         << setw(15) << "Status" << "\n";
    ConsoleUI::printDivider();

    for (const auto& r : rooms) {
        cout << left << setw(12) << r.getRoomNumber()
             << setw(18) << r.getType()
             << "$" << setw(17) << fixed << setprecision(2) << r.getPricePerNight()
             << setw(15) << (r.getIsOccupied() ? "Occupied" : "Available") << "\n";
    }
    ConsoleUI::printDivider();
}

void RoomManager::searchRoom() const {
    if (rooms.empty()) {
        cout << "\nNo rooms registered to search.\n";
        return;
    }

    int roomNum = InputValidator::getValidInt("Enter Room Number to Search: ");
    for (const auto& r : rooms) {
        if (r.getRoomNumber() == roomNum) {
            cout << "\n--- Room Details ---\n";
            cout << "Room Number : " << r.getRoomNumber() << "\n";
            cout << "Type        : " << r.getType() << "\n";
            cout << "Price/Night : $" << fixed << setprecision(2) << r.getPricePerNight() << "\n";
            cout << "Status      : " << (r.getIsOccupied() ? "Occupied" : "Available") << "\n";
            return;
        }
    }
    cout << "Room number " << roomNum << " not found.\n";
}

void RoomManager::updateRoomPrice() {
    int roomNum = InputValidator::getValidInt("Enter Room Number to Update: ");
    Room* r = findRoom(roomNum);

    if (r == nullptr) {
        cout << "Room number " << roomNum << " not found.\n";
        return;
    }

    double newPrice = InputValidator::getValidDouble("Enter New Price per Night ($): ");
    r->setPrice(newPrice);
    saveChanges();
    cout << "Room price updated successfully!\n";
}

Room* RoomManager::findRoom(int roomNumber) {
    for (auto& r : rooms) {
        if (r.getRoomNumber() == roomNumber) {
            return &r;
        }
    }
    return nullptr;
}

void RoomManager::setRoomStatus(int roomNumber, bool isOccupied) {
    Room* r = findRoom(roomNumber);
    if (r != nullptr) {
        r->setOccupied(isOccupied);
        saveChanges();
    }
}

void RoomManager::saveChanges() {
    fileHandler.saveRooms(rooms);
}

const vector<Room>& RoomManager::getRooms() const {
    return rooms;
}