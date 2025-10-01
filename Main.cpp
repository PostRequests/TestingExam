#include <iostream>
#include "TestingSystem.h"
int main()
{
    system("chcp 1251>nul");

    try {
        TestingSystem system;
        system.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }
}

