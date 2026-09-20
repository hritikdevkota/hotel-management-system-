#include "../include/InputValidator.h"
#include <iostream>
#include <limits>

using namespace std;

int InputValidator::getValidInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "Invalid input. Please enter a valid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double InputValidator::getValidDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "Invalid input. Please enter a valid numerical price or amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string InputValidator::getValidString(const string& prompt) {
    string str;
    while (true) {
        cout << prompt;
        getline(cin, str);
        if (!str.empty()) return str;
        cout << "Input cannot be empty. Please try again.\n";
    }
}

string InputValidator::getValidPhone(const string& prompt) {
    string phone;
    while (true) {
        cout << prompt;
        getline(cin, phone);
        
        bool isValid = !phone.empty();
        for (char c : phone) {
            if (!isdigit(c) && c != '-' && c != '+') {
                isValid = false;
                break;
            }
        }
        
        if (isValid) return phone;
        cout << "Invalid phone number. Use digits, dashes, or '+' only.\n";
    }
}