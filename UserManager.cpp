#include "UserManager.h"
UserManager::UserManager() : nextId(1) {}

bool UserManager::registerGuest(const std::string& login, const std::string& password,
    const std::string& firstName, const std::string& lastName,
    const std::string& patronymic, const std::string& phoneNumber,
    const std::string& address) {

    if (!isValidLogin(login) || !isValidPassword(password) ||
        !isValidPhoneNumber(phoneNumber) || userExists(login)) {
        return false;
    }

    std::string passwordHash = Users::hashPassword(password);
    auto guest = std::make_shared<Guest>(generateNextId(), login, passwordHash,
        firstName, lastName, patronymic,
        phoneNumber, address);
    users.push_back(guest);
    return true;
}

bool UserManager::createAdmin(const std::string& password,
    const std::string& firstName, const std::string& lastName,
    const std::string& patronymic, const std::string& phoneNumber) {

    if (userExists(ADMIN_LOGIN) || !isValidPassword(password) ||
        !isValidPhoneNumber(phoneNumber)) {
        return false;
    }

    std::string passwordHash = Users::hashPassword(password);
    auto admin = std::make_shared<Admin>(generateNextId(), ADMIN_LOGIN, passwordHash,
        firstName, lastName, patronymic, phoneNumber);
    users.push_back(admin);
    return true;
}

std::shared_ptr<Users> UserManager::authenticate(const std::string& login, const std::string& password) const {
    auto user = getUserByLogin(login);
    if (user && user->getIsActive() && user->checkPassword(password)) {
        // Обновляем время последнего входа для админа
        if (auto admin = std::dynamic_pointer_cast<Admin>(user)) {
            admin->updateLastLogin();
        }
        return user;
    }
    return nullptr;
}

std::shared_ptr<Users> UserManager::getUserByLogin(const std::string& login) const {
    auto it = std::find_if(users.begin(), users.end(),
        [&login](const std::shared_ptr<Users>& user) {
            return user->getLogin() == login && user->getIsActive();
        });
    return it != users.end() ? *it : nullptr;
}

std::shared_ptr<Users> UserManager::getUserById(int id) const {
    auto it = std::find_if(users.begin(), users.end(),
        [id](const std::shared_ptr<Users>& user) {
            return user->getId() == id && user->getIsActive();
        });
    return it != users.end() ? *it : nullptr;
}

bool UserManager::userExists(const std::string& login) const {
    return getUserByLogin(login) != nullptr;
}

bool UserManager::deleteUser(int id) {
    auto user = getUserById(id);
    if (user && user->getLogin() != ADMIN_LOGIN) { // Нельзя удалить админа
        user->setIsActive(false);
        return true;
    }
    return false;
}

bool UserManager::deleteUserByLogin(const std::string& login) {
    if (login == ADMIN_LOGIN) return false; // Нельзя удалить админа
    auto user = getUserByLogin(login);
    if (user) {
        user->setIsActive(false);
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<Users>> UserManager::getAllUsers() const {
    std::vector<std::shared_ptr<Users>> activeUsers;
    std::copy_if(users.begin(), users.end(), std::back_inserter(activeUsers),
        [](const std::shared_ptr<Users>& user) {
            return user->getIsActive();
        });
    return activeUsers;
}

std::vector<std::shared_ptr<Guest>> UserManager::getAllGuests() const {
    std::vector<std::shared_ptr<Guest>> guests;
    for (const auto& user : users) {
        if (user->getIsActive() && user->getLogin() != ADMIN_LOGIN) {
            if (auto guest = std::dynamic_pointer_cast<Guest>(user)) {
                guests.push_back(guest);
            }
        }
    }
    return guests;
}

std::shared_ptr<Admin> UserManager::getAdmin() const {
    auto user = getUserByLogin(ADMIN_LOGIN);
    return std::dynamic_pointer_cast<Admin>(user);
}

bool UserManager::changeUserPassword(int userId, const std::string& newPassword) {
    if (!isValidPassword(newPassword)) return false;

    auto user = getUserById(userId);
    if (user) {
        user->setPasswordHash(Users::hashPassword(newPassword));
        return true;
    }
    return false;
}

bool UserManager::changeUserPasswordByLogin(const std::string& login, const std::string& newPassword) {
    if (!isValidPassword(newPassword)) return false;

    auto user = getUserByLogin(login);
    if (user) {
        user->setPasswordHash(Users::hashPassword(newPassword));
        return true;
    }
    return false;
}

// Валидация данных
bool UserManager::isValidLogin(const std::string& login) {
    return !login.empty() && login.length() >= 3 && login.length() <= 20 &&
        std::all_of(login.begin(), login.end(), [](char c) {
        return std::isalnum(c) || c == '_' || c == '-';
            });
}

bool UserManager::isValidPassword(const std::string& password) {
    return password.length() >= 6;
}

bool UserManager::isValidPhoneNumber(const std::string& phoneNumber) {
    return !phoneNumber.empty() && phoneNumber.length() >= 10;
}

int UserManager::generateNextId() {
    return nextId++;
}

// Простая реализация сохранения/загрузки (можно расширить)
bool UserManager::saveUsersToFile(const std::string& filename) const {
    // Реализация сохранения в файл
    return false; // Заглушка
}

bool UserManager::loadUsersFromFile(const std::string& filename) {
    // Реализация загрузки из файла
    return false; // Заглушка
}