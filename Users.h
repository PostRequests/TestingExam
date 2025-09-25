#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <memory>
class Users
{
protected:
	int id;
	std::string login;
	std::string pwd;
	std::string fullName;
	std::string homeStreet;
	std::string phone;
public:
	Users(int id, std::string login, std::string pwd, std::string fullName,
		std::string homeStreet, std::string phone);
	virtual ~Users() = default;

	// Геттеры
	int getId() const;
	std::string getLogin() const;
	std::string getPWD() const;
	std::string getFullName() const;
	std::string getPhoneNumber() const;

	// Сеттеры
	int setId() const;
	std::string setLogin() const;
	std::string setPWD() const;
	std::string setFullName() const;
	std::string setPhoneNumber() const;


};

