#include "Admin.h"
#include <ctime>

Admin::Admin(const std::string& login, const std::string& pwd,
    const std::string& fullName, const std::string& phoneNumber, bool hash)
    : Users(login, pwd, fullName, phoneNumber, hash)
{}

std::string Admin::getRole() const { return "Admin"; };