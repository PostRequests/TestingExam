#include "Admin.h"
Admin::Admin(int id, const std::string& login, const std::string& passwordHash,
    const std::string& firstName, const std::string& lastName,
    const std::string& patronymic, const std::string& phoneNumber)
    : Users(id, login, passwordHash, firstName, lastName, patronymic, phoneNumber) {
    updateLastLogin();
}

std::time_t Admin::getLastLogin() const { return lastLogin; }

std::string Admin::getLastLoginString() const {
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&lastLogin));
    return std::string(buffer);
}

void Admin::updateLastLogin() {
    lastLogin = std::time(nullptr);
}

std::string Admin::getRole() const { return "Admin"; }
bool Admin::canManageUsers() const { return true; }
bool Admin::canManageTests() const { return true; }
bool Admin::canTakeTests() const { return false; }