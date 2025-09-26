#include "Guest.h"

Guest::Guest(int id, const std::string& login, const std::string& passwordHash,
    const std::string& firstName, const std::string& lastName,
    const std::string& patronymic, const std::string& phoneNumber,
    const std::string& address)
    : Users(id, login, passwordHash, firstName, lastName, patronymic, phoneNumber),
    address(address) {
    registrationDate = std::time(nullptr);
}

std::string Guest::getAddress() const { return address; }
std::time_t Guest::getRegistrationDate() const { return registrationDate; }

std::string Guest::getRegistrationDateString() const {
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&registrationDate));
    return std::string(buffer);
}

void Guest::setAddress(const std::string& address) {
    this->address = address;
}

std::string Guest::getRole() const { return "Guest"; }
bool Guest::canManageUsers() const { return false; }
bool Guest::canManageTests() const { return false; }
bool Guest::canTakeTests() const { return true; }