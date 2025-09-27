#pragma once
#include "Users.h"
#include <ctime>

class Guest : public Users
{
private:


public:
    Guest(const std::string& login, const std::string& pwd,
        const std::string& fullName, const std::string& phoneNumber);

  
     std::string getRole() const;
};
