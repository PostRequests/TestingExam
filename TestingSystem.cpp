#include "TestingSystem.h"
#include "Menu.h"
#include <iostream>
#include <conio.h>

TestingSystem::TestingSystem() {
  
    // Загрузка данных
    userManager = userSaver.load();
    testManager = testSaver.load();
    sessionManager.loadFromFile("sessions.dat");

    currentUserLogin = "";
    isAdmin = false;
}

void TestingSystem::initializeAdmin() {
    if (userManager.users.empty()) {
        std::cout << "=== Первоначальная настройка системы ===" << std::endl;
        std::cout << "Создание учетной записи администратора:" << std::endl;

        std::string login, password, fullName, phone;

        std::cout << "Логин: ";
        std::cin >> login;
        std::cout << "Пароль: ";
        std::cin >> password;
        std::cin.ignore();
        std::cout << "ФИО: ";
        std::getline(std::cin, fullName);
        std::cout << "Телефон: ";
        std::getline(std::cin, phone);

        if (userManager.createAdmin(login, password, fullName, phone)) {
            userSaver.save(userManager);
            std::cout << "Администратор успешно создан!" << std::endl;
        }
        else {
            std::cout << "Ошибка при создании администратора!" << std::endl;
        }
    }
}

void TestingSystem::run() {
    initializeAdmin();

    Menu mainMenu(5, 5, "Система тестирования");
    mainMenu.addItem("Вход в систему", [this]() {
        std::string login, password;
        std::cout << "Логин: ";
        std::cin >> login;
        std::cout << "Пароль: ";
        std::cin >> password;

        // Поиск пользователя
        for (const auto& user : userManager.users) {
            if (user->getLogin() == login && user->checkPassword(password)) {
                currentUserLogin = login;
                isAdmin = (user->getRole() == "Admin");

                if (isAdmin) {
                    adminMenu();
                }
                else {
                    guestMenu();
                }
                return;
            }
        }
        std::cout << "Неверный логин или пароль!" << std::endl;
        });

    mainMenu.addItem("Регистрация", [this]() {
        std::string login, password, fullName, phone;

        std::cout << "=== Регистрация нового пользователя ===" << std::endl;
        std::cout << "Логин: ";
        std::cin >> login;
        std::cout << "Пароль: ";
        std::cin >> password;
        std::cin.ignore();
        std::cout << "ФИО: ";
        std::getline(std::cin, fullName);
        std::cout << "Телефон: ";
        std::getline(std::cin, phone);

        if (userManager.registerGuest(login, password, fullName, phone)) {
            userSaver.save(userManager);
            std::cout << "Регистрация успешна!" << std::endl;
        }
        else {
            std::cout << "Ошибка регистрации! Проверьте введенные данные." << std::endl;
        }
        });

    mainMenu.addItem("Выход", []() {
        std::cout << "До свидания!" << std::endl;
        });

    mainMenu.run();
}

void TestingSystem::guestMenu() {
    Menu guestMenu(5, 5, "Меню гостя: " + currentUserLogin);

    guestMenu.addItem("Пройти тестирование", [this]() {
        auto testNames = testManager.getListNameTest();
        if (testNames.empty()) {
            std::cout << "Нет доступных тестов!" << std::endl;
            return;
        }

        Menu testMenu(5, 5, "Выбор теста");
        for (const auto& testName : testNames) {
            testMenu.addItem(testName, [this, testName]() {
                takeTest(testName);
                });
        }
        testMenu.addItem("Назад", []() {});
        testMenu.run();
        });

    guestMenu.addItem("Просмотреть результаты", [this]() {
        viewTestResults();
        });

    guestMenu.addItem("Выход", [this]() {
        currentUserLogin = "";
        isAdmin = false;
        });

    guestMenu.run();
}

void TestingSystem::adminMenu() {
    Menu adminMenu(5, 5, "Меню администратора");

    adminMenu.addItem("Управление пользователями", [this]() {
        manageUsers();
        });

    adminMenu.addItem("Управление тестами", [this]() {
        manageTests();
        });

    adminMenu.addItem("Просмотр статистики", [this]() {
        viewStatistics();
        });

    adminMenu.addItem("Выход", [this]() {
        currentUserLogin = "";
        isAdmin = false;
        });

    adminMenu.run();
}

void TestingSystem::takeTest(const std::string& testName) {
    try {
        Test* test = testManager.getTest(testName);
        TestSession session(currentUserLogin, testName);

        int correctAnswers = 0;
        int totalQuestions = test->size();

        std::cout << "=== Начало теста: " << testName << " ===" << std::endl;
        std::cout << "Количество вопросов: " << totalQuestions << std::endl;
        std::cout << "Для выхода введите 'exit' в любой момент\n" << std::endl;

        for (int i = 0; i < totalQuestions; i++) {
            Question& question = test->getQuestion(i);

            std::cout << "\nВопрос " << (i + 1) << ": " << question.getQuestionText() << std::endl;

            auto answers = question.getAnswers();
            for (size_t j = 0; j < answers.size(); j++) {
                std::cout << "  " << (j + 1) << ". " << answers[j] << std::endl;
            }

            std::cout << "\nВаш ответ (введите номер): ";
            std::string input;
            std::cin >> input;

            if (input == "exit") {
                std::cout << "Тестирование прервано." << std::endl;
                return;
            }

            try {
                int choice = std::stoi(input) - 1;
                if (choice >= 0 && choice < answers.size()) {
                    if (question.checkAnswer(answers[choice])) {
                        correctAnswers++;
                        std::cout << "✓ Правильно!" << std::endl;
                    }
                    else {
                        std::cout << "✗ Неправильно!" << std::endl;
                    }
                }
                else {
                    std::cout << "✗ Неправильный номер ответа!" << std::endl;
                }
            }
            catch (...) {
                std::cout << "✗ Неверный ввод!" << std::endl;
            }
        }

        int score = test->getScore(correctAnswers);
        session.setScore(score, 12);
        session.markCompleted();
        sessionManager.addSession(session);
        sessionManager.saveToFile("sessions.dat");

        std::cout << "\n=== Результаты тестирования ===" << std::endl;
        std::cout << "Правильных ответов: " << correctAnswers << "/" << totalQuestions << std::endl;
        std::cout << "Баллы: " << score << "/12" << std::endl;
        std::cout << "Оценка: " << session.getGrade() << std::endl;
        std::cout << "Процент правильных ответов: " << session.getPercentage() << "%" << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void TestingSystem::viewTestResults() {
    auto userSessions = sessionManager.getUserSessions(currentUserLogin);

    if (userSessions.empty()) {
        std::cout << "У вас пока нет результатов тестирования." << std::endl;
        return;
    }

    std::cout << "=== Ваши результаты тестирования ===" << std::endl;
    for (const auto& session : userSessions) {
        if (session->isCompleted()) {
            std::cout << "\nТест: " << session->getTestName() << std::endl;
            std::cout << "Баллы: " << session->getScore() << "/" << session->getMaxScore() << std::endl;
            std::cout << "Оценка: " << session->getGrade() << std::endl;
            std::cout << "Процент: " << session->getPercentage() << "%" << std::endl;
            //std::cout << "Дата: " << std::ctime(&session->getDate());
        }
    }
}

void TestingSystem::manageUsers() {
    Menu userMenu(5, 5, "Управление пользователями");

    userMenu.addItem("Просмотр всех пользователей", [this]() {
        std::cout << "=== Список пользователей ===" << std::endl;
        for (const auto& user : userManager.users) {
            std::cout << "Логин: " << user->getLogin() << std::endl;
            std::cout << "ФИО: " << user->getFullName() << std::endl;
            std::cout << "Телефон: " << user->getPhoneNumber() << std::endl;
            std::cout << "Роль: " << user->getRole() << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        });

    userMenu.addItem("Создать администратора", [this]() {
        std::string login, password, fullName, phone;

        std::cout << "=== Создание администратора ===" << std::endl;
        std::cout << "Логин: ";
        std::cin >> login;
        std::cout << "Пароль: ";
        std::cin >> password;
        std::cin.ignore();
        std::cout << "ФИО: ";
        std::getline(std::cin, fullName);
        std::cout << "Телефон: ";
        std::getline(std::cin, phone);

        if (userManager.createAdmin(login, password, fullName, phone)) {
            userSaver.save(userManager);
            std::cout << "Администратор успешно создан!" << std::endl;
        }
        else {
            std::cout << "Ошибка при создании администратора!" << std::endl;
        }
        });

    userMenu.addItem("Назад", []() {});
    userMenu.run();
}

void TestingSystem::manageTests() {
    Menu testMenu(5, 5, "Управление тестами");

    testMenu.addItem("Просмотр тестов", [this]() {
        auto testNames = testManager.getListNameTest();
        if (testNames.empty()) {
            std::cout << "Нет доступных тестов!" << std::endl;
            return;
        }

        std::cout << "=== Список тестов ===" << std::endl;
        for (const auto& name : testNames) {
            Test* test = testManager.getTest(name);
            std::cout << "Название: " << name << std::endl;
            std::cout << "Количество вопросов: " << test->size() << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        });

    testMenu.addItem("Создать тест", [this]() {
        std::string testName;
        std::cout << "Введите название теста: ";
        std::cin.ignore();
        std::getline(std::cin, testName);

        Test newTest(testName);

        int questionCount;
        std::cout << "Количество вопросов: ";
        std::cin >> questionCount;
        std::cin.ignore();

        for (int i = 0; i < questionCount; i++) {
            Question q;
            std::string questionText;

            std::cout << "\nВопрос " << (i + 1) << ": ";
            std::getline(std::cin, questionText);
            q.setQuestionText(questionText);

            int answerCount;
            std::cout << "Количество ответов: ";
            std::cin >> answerCount;
            std::cin.ignore();

            for (int j = 0; j < answerCount; j++) {
                std::string answerText;
                char isCorrect;

                std::cout << "Ответ " << (j + 1) << ": ";
                std::getline(std::cin, answerText);
                std::cout << "Правильный? (y/n): ";
                std::cin >> isCorrect;
                std::cin.ignore();

                q.addAnswer(answerText, (isCorrect == 'y' || isCorrect == 'Y'));
            }

            newTest.addQuestion(q);
        }

        testManager.addTest(newTest);
        testSaver.save(newTest);
        std::cout << "Тест успешно создан!" << std::endl;
        });

    testMenu.addItem("Назад", []() {});
    testMenu.run();
}

void TestingSystem::viewStatistics() {
    Menu statsMenu(5, 5, "Просмотр статистики");

    statsMenu.addItem("Общая статистика", [this]() {
        auto allSessions = sessionManager.getAllSessions();
        int completedTests = 0;
        int totalUsers = userManager.users.size();

        for (const auto& session : allSessions) {
            if (session->isCompleted()) {
                completedTests++;
            }
        }

        std::cout << "=== Общая статистика ===" << std::endl;
        std::cout << "Всего пользователей: " << totalUsers << std::endl;
        std::cout << "Всего пройденных тестов: " << completedTests << std::endl;
        std::cout << "Всего тестов в системе: " << testManager.getListNameTest().size() << std::endl;
        });

    statsMenu.addItem("Статистика по тестам", [this]() {
        auto testNames = testManager.getListNameTest();
        if (testNames.empty()) {
            std::cout << "Нет доступных тестов!" << std::endl;
            return;
        }

        for (const auto& testName : testNames) {
            auto testSessions = sessionManager.getTestSessions(testName);
            int completed = 0;
            double avgScore = 0;

            for (const auto& session : testSessions) {
                if (session->isCompleted()) {
                    completed++;
                    avgScore += session->getScore();
                }
            }

            if (completed > 0) {
                avgScore /= completed;
            }

            std::cout << "\nТест: " << testName << std::endl;
            std::cout << "Пройдено раз: " << completed << std::endl;
            std::cout << "Средний балл: " << avgScore << "/12" << std::endl;
        }
        });

    statsMenu.addItem("Экспорт в файл", [this]() {
        sessionManager.saveToFile("statistics_export.dat");
        std::cout << "Статистика экспортирована в файл statistics_export.dat" << std::endl;
        });

    statsMenu.addItem("Назад", []() {});
    statsMenu.run();
}