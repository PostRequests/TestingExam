#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ctime>
class Users
{
protected:
    std::string login; // Логин
    std::string pwd; // Пароль 
    std::string fullName; // Полное имя
    std::string phoneNumber; // Телефонный номер

public:
    Users(const std::string& login, const std::string& passwordHash,
        const std::string& fullName, const std::string& phoneNumber, bool hash);


    std::string getLogin() const; //Возвращает пароль
    std::string getFullName() const;  //Возвращает имя
    std::string getPhoneNumber() const;  //Возвращает номер телефона
    /// <summary>
    /// Устанавливает пароль
    /// </summary>
    /// <param name="newPassword">Необходимый пароль</param>
    /// <param name="hash">treue если пароль нужно зашифровать</param>
    void setPassword(const std::string& newPassword, bool hash = true);
    void setFullName(const std::string& fullName); //Устанавливает полное имя
    void setPhoneNumber(const std::string& phoneNumber); //Устанавливает и проверяет телефонный номер на соответствие

    virtual std::string getRole() const = 0; // Возвращает "Admin" или "Guest"
    std::string ToString() const; //Возвращает строку для сохранения в файл

    static std::string hashPassword(const std::string& password); // Метод шифрования пароля

    bool checkPassword(const std::string& password) const;   // Метод для проверки пароля
};
