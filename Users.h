#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ctime>
class Users
{
protected:
protected:
    int id;
    std::string login;
    std::string passwordHash; // ������ �������� � ������������� ����
    std::string firstName;
    std::string lastName;
    std::string patronymic;
    std::string phoneNumber;
    bool isActive;

public:
    // ������������
    Users(int id, const std::string& login, const std::string& passwordHash,
        const std::string& firstName, const std::string& lastName,
        const std::string& patronymic, const std::string& phoneNumber);

    virtual ~Users() = default;

    // �������
    int getId() const;
    std::string getLogin() const;
    std::string getPasswordHash() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPatronymic() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;
    bool getIsActive() const;

    // �������
    void setPasswordHash(const std::string& newPasswordHash);
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setPatronymic(const std::string& patronymic);
    void setPhoneNumber(const std::string& phoneNumber);
    void setIsActive(bool active);

    // ����������� ������ ��� ������������
    virtual std::string getRole() const = 0;
    virtual bool canManageUsers() const = 0;
    virtual bool canManageTests() const = 0;
    virtual bool canTakeTests() const = 0;

    // ����������� ����� ��� ����������� ������
    static std::string hashPassword(const std::string& password);

    // ����� ��� �������� ������
    bool checkPassword(const std::string& password) const;
};
