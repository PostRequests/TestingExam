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



void TestingSystem::run() {

    Menu mainMenu(5, 5, "Система тестирования");
    mainMenu.addItem("Вход в систему", [this]() {
        std::string login, password;
        std::cout << "Логин: ";
        std::cin >> login;
        std::cout << "Пароль: ";
        std::cin >> password;
        auto user = userManager.getUser(login, password);
        if (user != nullptr) {
            isAdmin = (user->getRole() == "Admin");
            currentUserLogin = user->getLogin();
            if (isAdmin) {
                adminMenu();
            }
            else {
                guestMenu();
            }
            return;
        }

        std::cout << "Неверный логин или пароль!" << std::endl;
        system("pause>nul");
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
        system("pause>nul");
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
   
    Test* test = testManager.getTest(testName);
    TestSession session(currentUserLogin, testName, std::time(0));

    int correctAnswers = 0;
    int totalQuestions = test->size();

    std::cout << "=== Начало теста: " << testName << " ===" << std::endl;
    std::cout << "Количество вопросов: " << totalQuestions << std::endl;
    std::cout << "Для выхода введите 'exit' в любой момент\n" << std::endl;

    for (int i = 0; i < totalQuestions; i++) {
        Question& question = test->getQuestion(i);
        Menu menu(2,2, question.getQuestionText(), true);
           

        auto answers = question.getAnswers();
        for (size_t j = 0; j < answers.size(); j++) {
            menu.addItem(answers[j],[this](){});
        }
        int choice = menu.run();
        if (question.checkAnswer(answers[choice])) {
            correctAnswers++;
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
    system("pause>nul");
   
}
std::string timeToString(time_t timestamp) {
    std::tm timeInfo = {};
    errno_t err = localtime_s(&timeInfo, &timestamp);
    if (err != 0) {
        return "Не правильная дата";
    }

    std::ostringstream oss;
    oss << std::put_time(&timeInfo, "%H:%M:%S  %m.%d.%Y");
    return oss.str();
}
void TestingSystem::viewTestResults() {
    auto userSessions = sessionManager.getUserSessions(currentUserLogin);

    if (userSessions.empty()) {
        std::cout << "У вас пока нет результатов тестирования." << std::endl;
        system("pause>nul");
        return;
    }

    std::cout << "=== Ваши результаты тестирования ===" << std::endl;
    for (const auto& session : userSessions) {
        if (session.isCompleted()) {
            std::cout << "\nТест: " << session.getTestName() << std::endl;
            std::cout << "Баллы: " << session.getScore() << "/" << session.getMaxScore() << std::endl;
            std::cout << "Дата: " << timeToString(session.getDate()) << std::endl;
           
        }
    }
    system("pause>nul");
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
        system("pause>nul");
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
        system("pause>nul");
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
            if (session.isCompleted()) {
                completedTests++;
            }
        }

        std::cout << "=== Общая статистика ===" << std::endl;
        std::cout << "Всего пользователей: " << totalUsers << std::endl;
        std::cout << "Всего пройденных тестов: " << completedTests << std::endl;
        std::cout << "Всего тестов в системе: " << testManager.getListNameTest().size() << std::endl;
        system("pause>nul");
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
                if (session.isCompleted()) {
                    completed++;
                    avgScore += session.getScore();
                }
            }

            if (completed > 0) {
                avgScore /= completed;
            }

            std::cout << "\nТест: " << testName << std::endl;
            std::cout << "Пройдено раз: " << completed << std::endl;
            std::cout << "Средний балл: " << avgScore << "/12" << std::endl;
        }
        system("pause>nul");
        });

    statsMenu.addItem("По пользователям", [this]() {
        Menu menu(1,1, "Выберете пользователя");
        std::vector<std::string> users = userManager.getAllUserLogin();
        for (std::string user : users) {
            menu.addItem(user,[this, user](){
                auto allSessions = sessionManager.getAllSessions();

                for (const auto& session : allSessions) {
                    if (session.getUserLogin() == user) {
                        std::cout << "\nТест: " << session.getTestName() << std::endl;
                        std::cout << "Баллы: " << session.getScore() << "/" << session.getMaxScore() << std::endl;
                        std::cout << "Дата: " << timeToString(session.getDate()) << std::endl;
                    }
                }
                system("pause>nul");
                });
        }
        menu.addItem("Назад", []() {});
        menu.run();
        });

    statsMenu.addItem("Назад", []() {});
    statsMenu.run();
}