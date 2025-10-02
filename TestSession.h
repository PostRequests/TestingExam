#pragma once
#include "Test.h"
#include <string>
#include <ctime>

class TestSession {
private:
    std::string userLogin;
    std::string testName;
    int score;
    int maxScore;
    time_t date;
    bool completed;

public:
    TestSession(const std::string& userLogin, const std::string& testName, const time_t time);

    void setScore(int score, int maxScore);
    void markCompleted();

    std::string getUserLogin() const;
    std::string getTestName() const;
    int getScore() const;
    int getMaxScore() const;
    double getPercentage() const;
    std::string getGrade() const;
    time_t getDate() const;
    bool isCompleted() const;

    std::string toString() const;
};