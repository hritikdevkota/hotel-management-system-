#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>

class InputValidator {
public:
    // Guarantees a valid integer input from the user
    static int getValidInt(const std::string& prompt);

    // Guarantees a valid double (floating-point) input
    static double getValidDouble(const std::string& prompt);

    // Guarantees a non-empty string input
    static std::string getValidString(const std::string& prompt);

    // Validates phone numbers (numeric check)
    static std::string getValidPhone(const std::string& prompt);
};

#endif // INPUT_VALIDATOR_H