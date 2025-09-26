#pragma once
#include "Users.h"
#include <ctime>
class Guest : public Users
{
private:
    std::string address;
    std::time_t registrationDate;

public:
    Guest(int id, const std::string& login, const std::string& passwordHash,
        const std::string& firstName, const std::string& lastName,
        const std::string& patronymic, const std::string& phoneNumber,
        const std::string& address);

    // Геттеры
    std::string getAddress() const;
    std::time_t getRegistrationDate() const;
    std::string getRegistrationDateString() const;

    // Сеттеры
    void setAddress(const std::string& address);

    // Переопределенные виртуальные методы
    std::string getRole() const override;
    bool canManageUsers() const override;
    bool canManageTests() const override;
    bool canTakeTests() const override;
};

