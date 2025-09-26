#include "Users.h"


Users::Users(int id, const std::string& login, const std::string& passwordHash,
    const std::string& firstName, const std::string& lastName,
    const std::string& patronymic, const std::string& phoneNumber)
    : id(id), login(login), passwordHash(passwordHash),
    firstName(firstName), lastName(lastName), patronymic(patronymic),
    phoneNumber(phoneNumber), isActive(true) {
}
// Геттеры
int Users::getId() const { return id; }
std::string Users::getLogin() const { return login; }
std::string Users::getPasswordHash() const { return passwordHash; }
std::string Users::getFirstName() const { return firstName; }
std::string Users::getLastName() const { return lastName; }
std::string Users::getPatronymic() const { return patronymic; }
std::string Users::getPhoneNumber() const { return phoneNumber; }
bool Users::getIsActive() const { return isActive; }

std::string Users::getFullName() const {
    return lastName + " " + firstName + " " + patronymic;
}

// Сеттеры
void Users::setPasswordHash(const std::string& newPasswordHash) {
    passwordHash = newPasswordHash;
}

void Users::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void Users::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}

void Users::setPatronymic(const std::string& patronymic) {
    this->patronymic = patronymic;
}

void Users::setPhoneNumber(const std::string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void Users::setIsActive(bool active) {
    isActive = active;
}

// Хеширование пароля с использованием SHA-256
std::string Users::hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

bool Users::checkPassword(const std::string& password) const {
    return passwordHash == hashPassword(password);
}