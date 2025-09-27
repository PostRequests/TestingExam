#include "Admin.h"
#include <ctime>

Admin::Admin(const std::string& login, const std::string& pwd,
    const std::string& fullName, const std::string& phoneNumber)
    : Users(login, pwd, fullName, phoneNumber)
{}

std::string Admin::getRole() const { return "Admin"; };