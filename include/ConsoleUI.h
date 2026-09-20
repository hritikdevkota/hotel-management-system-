#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <string>

class ConsoleUI {
public:
    static void printHeader(const std::string& title);
    static void printDivider();
    static void printMenu();
    static void clearConsole();
};

#endif // CONSOLE_UI_H