#include "../include/ServiceCharge.h"
#include <sstream>
#include <vector>

using namespace std;

ServiceCharge::ServiceCharge() : chargeId(0), roomNumber(0), description(""), amount(0.0) {}

ServiceCharge::ServiceCharge(int id, int roomNum, string desc, double amt)
    : chargeId(id), roomNumber(roomNum), description(desc), amount(amt) {}

int ServiceCharge::getChargeId() const { return chargeId; }
int ServiceCharge::getRoomNumber() const { return roomNumber; }
string ServiceCharge::getDescription() const { return description; }
double ServiceCharge::getAmount() const { return amount; }

string ServiceCharge::toCSV() const {
    return to_string(chargeId) + "," + to_string(roomNumber) + "," + 
           description + "," + to_string(amount);
}

ServiceCharge ServiceCharge::fromCSV(const string& line) {
    stringstream ss(line);
    string item;
    vector<string> tokens;

    while (getline(ss, item, ',')) {
        tokens.push_back(item);
    }

    if (tokens.size() >= 4) {
        int id = stoi(tokens[0]);
        int rNum = stoi(tokens[1]);
        string desc = tokens[2];
        double amt = stod(tokens[3]);
        return ServiceCharge(id, rNum, desc, amt);
    }
    return ServiceCharge();
}