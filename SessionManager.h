#pragma once
#include "TestSession.h"
#include <vector>
#include <string>
#include <memory>

class SessionManager {
private:
    std::vector<std::shared_ptr<TestSession>> sessions;

public:
    void addSession(const TestSession& session);
    std::vector<std::shared_ptr<TestSession>> getUserSessions(const std::string& userLogin) const;
    std::vector<std::shared_ptr<TestSession>> getTestSessions(const std::string& testName) const;
    std::vector<std::shared_ptr<TestSession>> getAllSessions() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};