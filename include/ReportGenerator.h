#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include "RoomManager.h"
#include "BookingManager.h"

class ReportGenerator {
public:
    static void generateOccupancyReport(const RoomManager& roomMgr);
    static void generateRevenueReport(const FileHandler& fileHandler);
};

#endif // REPORT_GENERATOR_H