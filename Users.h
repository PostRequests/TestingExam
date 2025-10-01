#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ctime>
class Users
{
protected:
    std::string login; // �����
    std::string pwd; // ������ 
    std::string fullName; // ������ ���
    std::string phoneNumber; // ���������� �����

public:
    Users(const std::string& login, const std::string& passwordHash,
        const std::string& fullName, const std::string& phoneNumber, bool hash);


    std::string getLogin() const; //���������� ������
    std::string getFullName() const;  //���������� ���
    std::string getPhoneNumber() const;  //���������� ����� ��������
    /// <summary>
    /// ������������� ������
    /// </summary>
    /// <param name="newPassword">����������� ������</param>
    /// <param name="hash">treue ���� ������ ����� �����������</param>
    void setPassword(const std::string& newPassword, bool hash = true);
    void setFullName(const std::string& fullName); //������������� ������ ���
    void setPhoneNumber(const std::string& phoneNumber); //������������� � ��������� ���������� ����� �� ������������

    virtual std::string getRole() const = 0; // ���������� "Admin" ��� "Guest"
    std::string ToString() const; //���������� ������ ��� ���������� � ����

    static std::string hashPassword(const std::string& password); // ����� ���������� ������

    bool checkPassword(const std::string& password) const;   // ����� ��� �������� ������
};
