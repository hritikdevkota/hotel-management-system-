#include "../include/InputValidator.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Strip characters that would corrupt the CSV storage format (see
// FileHandler): a stray comma in a name/description shifts every
// field after it and can crash the next load.
static string sanitizeForCSV(string s) {
    s.erase(remove(s.begin(), s.end(), ','), s.end());
    s.erase(remove(s.begin(), s.end(), '\n'), s.end());
    s.erase(remove(s.begin(), s.end(), '\r'), s.end());
    return s;
}

// If stdin is closed/exhausted (EOF) or otherwise unrecoverable,
// looping forever asking for input would hang/spam output forever.
// Exit cleanly instead.
static void exitIfStreamDead() {
    if (cin.eof()) {
        cout << "\nInput stream closed. Exiting.\n";
        exit(0);
    }
}

int InputValidator::getValidInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        exitIfStreamDead();
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
        exitIfStreamDead();
        cout << "Invalid input. Please enter a valid numerical price or amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string InputValidator::getValidString(const string& prompt) {
    string str;
    while (true) {
        cout << prompt;
        if (!getline(cin, str)) {
            exitIfStreamDead();
        }
        str = sanitizeForCSV(str);
        if (!str.empty()) return str;
        cout << "Input cannot be empty. Please try again.\n";
    }
}

string InputValidator::getValidPhone(const string& prompt) {
    string phone;
    while (true) {
        cout << prompt;
        if (!getline(cin, phone)) {
            exitIfStreamDead();
        }

        bool isValid = !phone.empty();
        for (char c : phone) {
            if (!isdigit(static_cast<unsigned char>(c)) && c != '-' && c != '+') {
                isValid = false;
                break;
            }
        }

        if (isValid) return phone;
        cout << "Invalid phone number. Use digits, dashes, or '+' only.\n";
    }
}