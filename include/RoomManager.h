#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <vector>
#include "Room.h"
#include "FileHandler.h"

class RoomManager {
private:
    std::vector<Room> rooms;
    FileHandler fileHandler;

public:
    RoomManager();

    void addRoom();
    void displayAllRooms() const;
    void searchRoom() const;
    void updateRoomPrice();
    
    Room* findRoom(int roomNumber);
    void setRoomStatus(int roomNumber, bool isOccupied);
    void saveChanges();
    const std::vector<Room>& getRooms() const;
};

#endif // ROOM_MANAGER_H