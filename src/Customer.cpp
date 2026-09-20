#include "../include/Customer.h"
#include <sstream>

using namespace std;

Customer::Customer() : customerId(""), name(""), phone("") {}

Customer::Customer(string id, string n, string p) : customerId(id), name(n), phone(p) {}

string Customer::getId() const { return customerId; }
string Customer::getName() const { return name; }
string Customer::getPhone() const { return phone; }

string Customer::toCSV() const {
    return customerId + "," + name + "," + phone;
}

Customer Customer::fromCSV(const string& line) {
    stringstream ss(line);
    string id, name, phone;
    getline(ss, id, ',');
    getline(ss, name, ',');
    getline(ss, phone, ',');
    return Customer(id, name, phone);
}