#include <string>
#include <iostream>
#include <conio.h>
#include <ctime>
#include "CardManager.h"

#define uint unsigned int


uint inputUInt(const std::string &hint, const uint min, const uint max, const uint maxLength) {
    std::cout << "[*] " << hint << ": ";
    std::string input;
    while (true) {
        if (const int cur = getch(); cur >= '0' && cur <= '9') {
            if (input.length() < maxLength) {
                input.push_back(static_cast<char>(cur));
                std::cout << cur - '0';
            }
        } else if (cur == '\b') {
            if (input.empty()) {
                continue;
            }
            input.pop_back();
            std::cout << "\b \b";
        } else if (cur == '\n' || cur == '\r') {
            std::cout << std::endl;
            if (input.empty()) {
                std::cout << "[!] Input can not be empty: ";
                continue;
            }
            if (const uint ret = std::stoul(input); ret >= min && ret <= max) {
                return ret;
            }
            std::cout << "[!] Invalid input! Input (" << min << "~" << max << "): " << input;
        }
    }
}

std::string inputString(const std::string &hint) {
    std::cout << "[*] " << hint << ": ";
    std::string input;
    while (true) {
        if (const int cur = getch(); cur == '\b') {
            if (input.empty()) {
                continue;
            }
            input.pop_back();
            std::cout << "\b \b";
        } else if (cur == '\n' || cur == '\r') {
            std::cout << std::endl;
            if (input.empty()) {
                std::cout << "[!] Input can not be empty: ";
                continue;
            }
            return input;
        } else {
            input.push_back(static_cast<char>(cur));
            std::cout << static_cast<char>(cur);
        }
    }
}

bool isRunYear(const uint year) {
    return year % 100 == 0 ? year % 400 == 0 : year % 4 == 0;
}

const uint DAYS_OF_MONTHS[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
std::time_t inputDateTime(const std::string &hint) {
    std::cout << "[*] " << hint << "(yyyy-MM-dd HH:mm):     -  -  .  :  \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
    std::string input;
    while (true) {
        if (const int cur = getch(); cur >= '0' && cur <= '9') {
            if (input.size() == 12) continue;
            input.push_back(static_cast<char>(cur));
            std::cout << cur - '0';
            if (input.size() == 4 || input.size() == 6) {
                std::cout << '-';
            } else if (input.size() == 8) {
                std::cout << '.';
            } else if (input.size() == 10) {
                std::cout << ':';
            }
        } else if (cur == '\b') {
            if (input.empty()) {
                continue;
            }
            if (input.size() % 2 == 0 && input.size() >= 4 && input.size() != 12) {
                std::cout << '\b';
            }
            input.pop_back();
            std::cout << "\b \b";
        } else if (cur == '\n' || cur == '\r') {
            std::cout << std::endl;
            if (input.empty()) {
                std::cout << "[!] Input can not be empty!" << std::endl;
                return inputDateTime(hint);
            }
            if (input.size() != 12) {
                std::cout << "[!] Invalid date!" << std::endl;
                return inputDateTime(hint);
            }
            const uint year = std::stoul(input.substr(0, 4));
            const uint month = std::stoul(input.substr(4, 2));
            const uint day = std::stoul(input.substr(6, 2));
            const uint hour = std::stoul(input.substr(8, 2));
            const uint minute = std::stoul(input.substr(10, 2));
            if (month < 1 || month > 12 || day < 1 || day > DAYS_OF_MONTHS[month] + (isRunYear(year) && month == 2) || hour > 23 || minute > 59) {
                std::cout << "[!] Invalid date!" << std::endl;
                return inputDateTime(hint);
            }
            struct tm tm = {};
            tm.tm_year = static_cast<int>(year) - 1900;
            tm.tm_mon = static_cast<int>(month) - 1;
            tm.tm_mday = static_cast<int>(day);
            tm.tm_hour = static_cast<int>(hour);
            tm.tm_min = static_cast<int>(minute);
            return mktime(&tm);
        }
    }
}

void printMenu() {
    std::cout
        << "--------------------------------" << std::endl
        << " Swimming Card Manager" << std::endl
        << "--------------------------------" << std::endl
        << " 1. Create Student Card" << std::endl
        << " 2. Create Teacher Card" << std::endl
        << " 3. Login" << std::endl
        << " 4. About" << std::endl
        << " 0. Exit" << std::endl
        << "--------------------------------" << std::endl;
}

CardManager manager = CardManager();

void printLoginMenu(const int balance) {
    std::cout
        << "--------------------------------" << std::endl
        << " Card Operations" << std::endl
        << "--------------------------------" << std::endl
        << " Balance: " << balance << std::endl
        << " 1. Charge" << std::endl
        << " 2. Consume (swim)" << std::endl
        << " 3. View Bills" << std::endl
        << " 0. Logout" << std::endl
        << "--------------------------------" << std::endl;
}

void loginLoop(std::string cardId) {
    Card &card = manager.getCard(cardId);
    while (true) {
        printLoginMenu(card.getBalance());
        const uint op = inputUInt("Select operation", 0, 3, 1);
        switch (op) {
            case 0: {
                std::cout << "[*] Logged out." << std::endl;
                return;
            }
            case 1: {
                const uint amount = inputUInt("Enter charge amount", 1, 99999, 5);
                card.charge(static_cast<int>(amount));
                std::cout << "[*] Charged " << amount << ". New balance: " << card.getBalance() << std::endl;
                break;
            }
            case 2: {
                card.consume();
                std::cout << "[*] Consumed. New balance: " << card.getBalance() << std::endl;
                break;
            }
            case 3: {
                const auto &bills = card.getBills();
                if (bills.empty()) {
                    std::cout << "[*] No bills recorded." << std::endl;
                } else {
                    std::cout << "[*] Bills:" << std::endl;
                    for (const auto &bill : bills) {
                        std::cout << bill << std::endl;
                    }
                }
                break;
            }
            default: break;
        }
    }
}

int main()
{
    manager.readFile();

    while (true) {
        printMenu();
        const uint op = inputUInt("Select operation", 0, 4, 1);
        switch (op) {
            case 0: {
                manager.saveFile();
                getch();
                std::cout << "[*] Data saved successfully. Goodbye~" << std::endl;
                return 0;
            }
            case 1: {
                const std::string sno = inputString("Student No");
                const std::string name = inputString("Name");
                std::cout << "[*] Gender (0: Male, 1: Female): ";
                const uint genderInput = inputUInt("Gender", 0, 1, 1);
                const Gender gender = static_cast<Gender>(genderInput);
                const std::string affiliation = inputString("Affiliation");
                manager.createStudentCard(
                    const_cast<std::string &>(sno),
                    const_cast<std::string &>(name),
                    gender,
                    affiliation
                );
                std::cout << "[*] Student card created successfully." << std::endl;
                break;
            }
            case 2: {
                const std::string tno = inputString("Teacher No");
                const std::string name = inputString("Name");
                std::cout << "[*] Gender (0: Male, 1: Female): ";
                const uint genderInput = inputUInt("Gender", 0, 1, 1);
                const Gender gender = static_cast<Gender>(genderInput);
                const std::string affiliation = inputString("Affiliation");
                manager.createTeacherCard(
                    const_cast<std::string &>(tno),
                    const_cast<std::string &>(name),
                    gender,
                    affiliation
                );
                std::cout << "[*] Teacher card created successfully." << std::endl;
                break;
            }
            case 3: {
                const std::string cardId = inputString("Card ID");
                loginLoop(cardId);
                break;
            }
            case 4: {
                std::cout
                    << "--------------------------------" << std::endl
                    << " Swimming Card Manager v1.0" << std::endl
                    << " by SXZ, SK, OYH." << std::endl
                    << "--------------------------------" << std::endl;
                break;
            }
            default: break;
        }
    }
}

