#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string customerId;
    std::string name;
    std::string phone;

public:
    Customer();
    Customer(std::string id, std::string n, std::string p);

    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getPhone() const;

    // Data Serialization for File I/O
    std::string toCSV() const;
    static Customer fromCSV(const std::string& line);
};

#endif // CUSTOMER_H