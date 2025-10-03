#pragma once
#include "TestSession.h"
#include <vector>
#include <string>
#include <memory>

class SessionManager {
private:
    std::vector<TestSession> sessions; // Список всех сессий

public:
    void addSession(const TestSession& session);
    std::vector<TestSession> getUserSessions(const std::string& userLogin) const; //Возвращает все сессии конкретного пользователя
    std::vector<TestSession> getTestSessions(const std::string& testName) const; //Возвращает все сессии по конкретному тесту
    std::vector<TestSession> getAllSessions() const; //Возвращает все сессии

    void saveToFile(const std::string& filename) const; //Сохраняет все сессии в файл
    void loadFromFile(const std::string& filename); // Загружает сессии из файла
};