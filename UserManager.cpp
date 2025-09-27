#include "UserManager.h"



UserManager::UserManager() {}


bool UserManager::registerGuest(const std::string& login, const std::string& password,
    const std::string& fullName, const std::string& phoneNumber) {

    if (!isValidPassword(password) ||
        !isValidPhoneNumber(phoneNumber) || !isValidLogin(login) || !isValidFullName(fullName)) {
        return false;
    }

    auto guest = std::make_shared<Guest>(login, password,
        fullName, phoneNumber);
    users.push_back(guest);
    return true;
}

bool UserManager::createAdmin(const std::string& login, const std::string& password,
    const std::string& fullName, const std::string& phoneNumber) {

    if (!isValidPassword(password) ||
        !isValidPhoneNumber(phoneNumber) || !isValidLogin(login) || !isValidFullName(fullName)) {
        return false;
    }

    auto admin = std::make_shared<Admin>(login, password, fullName, phoneNumber);
    users.push_back(admin);
    return true;
}


bool UserManager::isValidPhoneNumber(std::string phone) {
    std::regex phoneValid(
        R"(^(\+?\d{1,3}[-.\s]?)?\(?\d{3}\)?[-.\s]?\d{3}[-.\s]?\d{2}[-.\s]?\d{2}$)"
    );
    return std::regex_match(phone, phoneValid);
}

bool UserManager::isValidPassword(std::string password) {
    // ��������� ����� ������ (������ 4 ��������)
    if (password.length() <= 4) {
        return false;
    }
    return true;
}

bool UserManager::isValidLogin(std::string login) {
    // ��������� ����� ������ (������ 4 ��������)
    if (login.length() <= 4) {
        return false;
    }
    // ���������, ��� ������ �� �������� ���� '~'
    for (char c : login) {
        if (c == '~') {
            return false;
        }
    }
    for (auto& user : users) {
        if (user->getLogin() == login) {
            return false;  // ����� ��� ����������
        }
    }
    return true;
}

bool UserManager::isValidFullName(std::string fullName) {
    // ��������� ����� ������ (������ 4 ��������)
    if (fullName.length() <= 4) {
        return false;
    }
    // ���������, ��� ������ �� �������� ���� '~'
    for (char c : fullName) {
        if (c == '~') {
            return false;
        }
    }

   
}