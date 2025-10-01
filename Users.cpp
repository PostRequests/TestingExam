#include "Users.h"
#include <sstream>
#include <string>
#include <iostream>
Users::Users(const std::string& login, const std::string& password,
    const std::string& fullName,const std::string& phoneNumber, bool hash)
    :  login(login), pwd((hash)?hashPassword(password): password),
    fullName(fullName), 
    phoneNumber(phoneNumber) {
}
// Геттеры
std::string Users::getLogin() const { return login; }
std::string Users::getFullName() const { return fullName; }
std::string Users::getPhoneNumber() const { return phoneNumber; }

// Сеттеры
void Users::setPassword(const std::string& newPWD, bool hash) {
    if (hash)
        pwd = hashPassword(newPWD);
    else
        pwd = newPWD;
}

void Users::setFullName(const std::string& fullName) {
    this->fullName = fullName;
}

void Users::setPhoneNumber(const std::string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}




std::string Users::hashPassword(const std::string& password) {
    std::ostringstream oss;
    for (size_t i = 0; i < password.size(); i++) {
        unsigned char byte = static_cast<unsigned char>(password[i]);
        oss << static_cast<unsigned int>(byte);
    }
    return oss.str();
}

bool Users::checkPassword(const std::string& password) const {
    return pwd == hashPassword(password);
}

std::string Users::ToString() const{
    return getRole() + '~' + login + '~' + pwd + '~' + fullName + '~' + phoneNumber;
}