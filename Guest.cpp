#include "Guest.h"
#include <ctime>


Guest::Guest(const std::string& login, const std::string& pwd,
    const std::string& fullName, const std::string& phoneNumber)
    : Users(login, pwd, fullName, phoneNumber)
 {}

std::string Guest::getRole() const { return "Guest"; };

