#pragma once
#include "UserManager.h"
#include <filesystem>
#include <iostream>
#include <fstream>
namespace fs = std::filesystem;
class SaverUserManager
{
private:
	fs::path path;
public:
	SaverUserManager(const std::string& path);
	void save(UserManager& um);
	void save(Users& um);
	UserManager load();
};

