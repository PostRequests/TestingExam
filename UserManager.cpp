#include "UserManager.h"



UserManager::UserManager() {}


bool UserManager::registerGuest(const std::string& login, const std::string& password,
    const std::string& fullName, const std::string& phoneNumber, bool hash) {

    if (!isValidPassword(password) ||
        !isValidPhoneNumber(phoneNumber) || !isValidLogin(login) || !isValidFullName(fullName)) {
        return false;
    }

    auto guest = std::make_shared<Guest>(login, password, fullName, phoneNumber, hash);
    users.push_back(guest);
    return true;
}

bool UserManager::createAdmin(const std::string& login, const std::string& password,
    const std::string& fullName, const std::string& phoneNumber, bool hash) {

    if (!isValidPassword(password) ||
        !isValidPhoneNumber(phoneNumber) || !isValidLogin(login) || !isValidFullName(fullName)) {
        return false;
    }

    auto admin = std::make_shared<Admin>(login, password, fullName, phoneNumber, hash);
    users.push_back(admin);
    return true;
}

std::shared_ptr<Users> UserManager::getUser(const std::string& login, const std::string& password)
{
    for (const auto& user : users) {
        if (user->getLogin() == login && user->checkPassword(password)) {
            return user;
        }
    }
    return nullptr;
}

std::vector<std::string> UserManager::getAllUserLogin()
{
    std::vector<std::string> allUsersName;
    for (const auto& user : users) {
        if(user->getRole() == "Guest")
            allUsersName.push_back(user->getLogin());
    }
    return allUsersName;
}


bool UserManager::isValidPhoneNumber(std::string phone) {
    std::regex phoneValid(
        R"(^(\+?\d{1,3}[-.\s]?)?\(?\d{3}\)?[-.\s]?\d{3}[-.\s]?\d{2}[-.\s]?\d{2}$)"
    );
    return std::regex_match(phone, phoneValid);
}

bool UserManager::isValidPassword(std::string password) {
    // Проверяем длину пароля (больше 4 символов)
    if (password.length() <= 4) {
        return false;
    }
    return true;
}

bool UserManager::isValidLogin(std::string login) {
    // Проверяем длину пароля (больше 4 символов)
    if (login.length() <= 4) {
        return false;
    }
  
    for (auto& user : users) {
        if (user->getLogin() == login) {
            return false;  // Логин уже существует
        }
    }
    std::regex p("^[a-zA-Z0-9]+$"); //Проверяем, что содержат только англ буквы и цифры
    return std::regex_match(login, p);
}

bool UserManager::isValidFullName(std::string fullName) {
    // Проверяем длину пароля (больше 4 символов)
    if (fullName.length() <= 4) {
        return false;
    }
    // Проверяем, что пароль не содержит знак '~'
    for (char c : fullName) {
        if (c == '~') {
            return false;
        }
    }
}