#pragma once
#include "Users.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Guest.h"
#include "Admin.h"
#include <regex>

class UserManager  // ������ ������������ �� Users
{
private:
    std::vector<std::shared_ptr<Users>> users;
    
public:
    UserManager();  // ���������������� �����������

    // ������ ��� ������ � ��������������
    bool registerGuest(const std::string& login, const std::string& password,
        const std::string& fullName, const std::string& phoneNumber);

    bool createAdmin(const std::string& login, const std::string& password,
        const std::string& fullName, const std::string& phoneNumber);

    bool isValidPhoneNumber(std::string phone);
    bool isValidPassword(std::string password);
    bool isValidLogin(std::string login);
    bool isValidFullName(std::string fullName);

private:
  
};