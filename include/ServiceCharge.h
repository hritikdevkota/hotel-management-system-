#ifndef SERVICE_CHARGE_H
#define SERVICE_CHARGE_H

#include <string>

class ServiceCharge {
private:
    int chargeId;
    int roomNumber;
    std::string description;
    double amount;

public:
    ServiceCharge();
    ServiceCharge(int id, int roomNum, std::string desc, double amt);

    int getChargeId() const;
    int getRoomNumber() const;
    std::string getDescription() const;
    double getAmount() const;

    std::string toCSV() const;
    static ServiceCharge fromCSV(const std::string& line);
};

#endif // SERVICE_CHARGE_H