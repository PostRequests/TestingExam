#pragma once
#include "TestSession.h"
#include <vector>
#include <string>
#include <memory>

class SessionManager {
private:
    std::vector<TestSession> sessions;

public:
    void addSession(const TestSession& session);
    std::vector<TestSession> getUserSessions(const std::string& userLogin) const;
    std::vector<TestSession> getTestSessions(const std::string& testName) const;
    std::vector<TestSession> getAllSessions() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};