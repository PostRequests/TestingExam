#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ctime>
class Users
{
protected:
    std::string login;
    std::string pwd; // ������ 
    std::string fullName;
    std::string phoneNumber;

public:
    // ������������
    Users(const std::string& login, const std::string& passwordHash,
        const std::string& fullName, const std::string& phoneNumber);

    virtual ~Users() = default;

    // �������
    std::string getLogin() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;

    // �������
    void setPassword(const std::string& newPasswordHash);
    void setFullName(const std::string& fullName);
    void setPhoneNumber(const std::string& phoneNumber);

    //// ����������� ������ ��� ������������
    virtual std::string getRole() const = 0;
    std::string ToString() const;

    // ����������� ����� ��� ������
    static std::string hashPassword(const std::string& password);

    // ����� ��� �������� ������
    bool checkPassword(const std::string& password) const;
};
