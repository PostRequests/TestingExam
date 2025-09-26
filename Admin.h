#pragma once
#include <ctime>
#include <string>
#include "Users.h"
class Admin : Users
{
private:
    std::time_t lastLogin;

public:
    Admin(int id, const std::string& login, const std::string& passwordHash,
        const std::string& firstName, const std::string& lastName,
        const std::string& patronymic, const std::string& phoneNumber);

    // �������
    std::time_t getLastLogin() const;
    std::string getLastLoginString() const;

    // ������ ��� ���������� ������� �����
    void updateLastLogin();

    // ���������������� ����������� ������
    std::string getRole() const override;
    bool canManageUsers() const override;
    bool canManageTests() const override;
    bool canTakeTests() const override;
};

