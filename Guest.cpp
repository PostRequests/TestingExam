#include "Guest.h"
#include <ctime>


Guest::Guest(const std::string& login, const std::string& pwd,
    const std::string& fullName, const std::string& phoneNumber, bool hash)
    : Users(login, pwd, fullName, phoneNumber, hash)
 {}

std::string Guest::getRole() const { return "Guest"; };

