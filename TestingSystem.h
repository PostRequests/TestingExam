#pragma once
#include "UserManager.h"
#include "TestManager.h"
#include "SessionManager.h"
#include "SaverUserManager.h"
#include "SaveTest.h"
#include "Option.h"
#include <memory>

class TestingSystem {
private:
    UserManager userManager; //Отвечает за всех пользователей
    TestManager testManager; //Хранит в себе тесты
    SessionManager sessionManager = SessionManager(); //Заопинает кто какие тесты проходил
    SaverUserManager userSaver = SaverUserManager(Option::pathUsers); //Сохраняет/загружает пользователей в файл
    SaveTest testSaver = SaveTest(Option::pathTests); // Сохраняет/загружает тесты в файл

    std::string currentUserLogin; //Аунтефецированный логин пользователя
    bool isAdmin;// true если вошел админ, false если гость

    void guestMenu(); //Показывает меню для обычных пользователей (гостей)
    void adminMenu(); //Показывает меню для администратора
    /// <summary>
    /// Запускает прохождение теста для текущего пользователя
    /// </summary>
    /// <param name="testName">Название теста который нужно пройти</param>
    void takeTest(const std::string& testName);
    void viewTestResults(); //Показывает все результаты тестов текущего пользователя
    void manageUsers(); //Меню для управления пользователями (только для админа)
    void manageTests(); //Меню для управления тестами (только для админа)
    void viewStatistics(); // Показывает статистику по всей системе (только для админа)

public:
    TestingSystem(); //Создает систему тестирования и загружает все данные
    void run(); // Запускает главное меню системы
};