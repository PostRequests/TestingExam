#pragma once
#include "Users.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Guest.h"
#include "Admin.h"
class UserManager : Users
{
private:
    std::vector<std::shared_ptr<Users>> users;
    int nextId;
    static const std::string ADMIN_LOGIN; // Стандартный логин админа

public:
    UserManager();

    // Методы для работы с пользователями
    bool registerGuest(const std::string& login, const std::string& password,
        const std::string& firstName, const std::string& lastName,
        const std::string& patronymic, const std::string& phoneNumber,
        const std::string& address);

    bool createAdmin(const std::string& password,
        const std::string& firstName, const std::string& lastName,
        const std::string& patronymic, const std::string& phoneNumber);

    std::shared_ptr<Users> authenticate(const std::string& login, const std::string& password) const;
    std::shared_ptr<Users> getUserByLogin(const std::string& login) const;
    std::shared_ptr<Users> getUserById(int id) const;

    bool userExists(const std::string& login) const;
    bool deleteUser(int id);
    bool deleteUserByLogin(const std::string& login);

    std::vector<std::shared_ptr<Users>> getAllUsers() const;
    std::vector<std::shared_ptr<Guest>> getAllGuests() const;
    std::shared_ptr<Admin> getAdmin() const;

    bool changeUserPassword(int userId, const std::string& newPassword);
    bool changeUserPasswordByLogin(const std::string& login, const std::string& newPassword);

    // Сохранение и загрузка пользователей
    bool saveUsersToFile(const std::string& filename) const;
    bool loadUsersFromFile(const std::string& filename);

    // Валидация данных
    static bool isValidLogin(const std::string& login);
    static bool isValidPassword(const std::string& password);
    static bool isValidPhoneNumber(const std::string& phoneNumber);

private:
    int generateNextId();
};


