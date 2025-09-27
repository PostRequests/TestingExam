#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ctime>
class Users
{
protected:
    std::string login;
    std::string pwd; // Пароль 
    std::string fullName;
    std::string phoneNumber;

public:
    // Конструкторы
    Users(const std::string& login, const std::string& passwordHash,
        const std::string& fullName, const std::string& phoneNumber);

    virtual ~Users() = default;

    // Геттеры
    std::string getLogin() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;

    // Сеттеры
    void setPassword(const std::string& newPasswordHash);
    void setFullName(const std::string& fullName);
    void setPhoneNumber(const std::string& phoneNumber);

    //// Виртуальные методы для полиморфизма
    virtual std::string getRole() const = 0;
    std::string ToString() const;

    // Статический метод для пароля
    static std::string hashPassword(const std::string& password);

    // Метод для проверки пароля
    bool checkPassword(const std::string& password) const;
};
