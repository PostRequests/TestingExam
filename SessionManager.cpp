#include "SessionManager.h"
#include <fstream>
#include <sstream>

void SessionManager::addSession(const TestSession& session) {
    sessions.push_back(session);
}

std::vector<TestSession> SessionManager::getUserSessions(const std::string& userLogin) const {
    std::vector<TestSession> result;
    for (const auto& session : sessions) {
        if (session.getUserLogin() == userLogin) {
            result.push_back(session);
        }
    }
    return result;
}

std::vector<TestSession> SessionManager::getTestSessions(const std::string& testName) const {
    std::vector<TestSession> result;
    for (const auto& session : sessions) {
        if (session.getTestName() == testName) {
            result.push_back(session);
        }
    }
    return result;
}

std::vector<TestSession> SessionManager::getAllSessions() const {
    return sessions;
}

void SessionManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::exception("Не удалось открыть файл для записи сессий");
    }

    for (const auto& session : sessions) {
        file << session.toString() << std::endl;
    }
    file.close();
}

void SessionManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    sessions.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string part;
        std::vector<std::string> parts;

        while (std::getline(iss, part, '~')) {
            parts.push_back(part);
        }

        if (parts.size() == 6) {

            TestSession session(parts[0], parts[1], static_cast<time_t>(std::stoll(parts[4])));
            session.setScore(std::stoi(parts[2]), std::stoi(parts[3]));
            if (parts[5] == "1") {
                session.markCompleted();
            }
            sessions.push_back(session);
        }
    }
    file.close();
}