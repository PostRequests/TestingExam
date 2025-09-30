#pragma once
#include "Test.h"
#include <string>
#include <vector>
class TestManager
{
private:
	std::vector<Test> tests;
public:
	void addTest(const Test& test);
	void removeTest(const std::string& testName);
	Test* getTest(const std::string& testName);
	std::vector<std::string> getListNameTest();
	

};

