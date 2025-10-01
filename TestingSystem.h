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
    UserManager userManager = UserManager();
    TestManager testManager = TestManager();
    SessionManager sessionManager = SessionManager();
    SaverUserManager userSaver = SaverUserManager(Option::pathUsers);
    SaveTest testSaver = SaveTest(Option::pathTests);

    std::string currentUserLogin;
    bool isAdmin;

    void initializeAdmin();
    void guestMenu();
    void adminMenu();
    void takeTest(const std::string& testName);
    void viewTestResults();
    void manageUsers();
    void manageTests();
    void viewStatistics();

public:
    TestingSystem();
    void run();
};