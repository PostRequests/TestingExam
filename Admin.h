#pragma once
#include <ctime>
#include <string>
#include "Users.h"

class Admin : public Users 
{
private:


public:
    Admin(const std::string& login, const std::string& pwd,
        const std::string& fullName, const std::string& phoneNumber, bool hash);

    std::string getRole() const;

};