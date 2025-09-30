#pragma once
#include "Test.h"
#include "TestManager.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
namespace fs = std::filesystem;
class SaveTest
{
private:
	fs::path path;
public:
	SaveTest(const std::string& path);
	void save(Test& test);
	TestManager load();
};

