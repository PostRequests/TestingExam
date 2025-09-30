#include "TestManager.h"

void TestManager::addTest(const Test& test)
{
    tests.push_back(test);
}

void TestManager::removeTest(const std::string& testName)
{
    for (int i = 0; i < tests.size(); i++)
    {
        if (testName == tests[i].getTestName()) {
            tests.erase(tests.begin() + i);
            break;
        }
    }
    
}

Test* TestManager::getTest(const std::string& testName)
{
    for (Test& t : tests) {
        if (testName == t.getTestName()) 
            return &t;
    }
    throw std::exception("Тест не найден");
}

std::vector<std::string> TestManager::getListNameTest()
{
    std::vector<std::string> result;
    for (Test& t : tests) {
        result.push_back(t.getTestName());
    }
    return result;
}
