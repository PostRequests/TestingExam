#include "TestSession.h"
#include <sstream>
#include <iomanip>

TestSession::TestSession(const std::string& userLogin, const std::string& testName)
    : userLogin(userLogin), testName(testName), score(0), maxScore(12),
    date(time(nullptr)), completed(false) {
}

void TestSession::setScore(int score, int maxScore) {
    this->score = score;
    this->maxScore = maxScore;
}

void TestSession::markCompleted() {
    completed = true;
}

std::string TestSession::getUserLogin() const { return userLogin; }
std::string TestSession::getTestName() const { return testName; }
int TestSession::getScore() const { return score; }
int TestSession::getMaxScore() const { return maxScore; }
bool TestSession::isCompleted() const { return completed; }
time_t TestSession::getDate() const { return date; }

double TestSession::getPercentage() const {
    return (maxScore > 0) ? (static_cast<double>(score) / maxScore) * 100 : 0;
}

std::string TestSession::getGrade() const {
    double percentage = getPercentage();
    if (percentage >= 95) return "12 (Отлично)";
    else if (percentage >= 90) return "11";
    else if (percentage >= 85) return "10";
    else if (percentage >= 80) return "9";
    else if (percentage >= 75) return "8";
    else if (percentage >= 70) return "7";
    else if (percentage >= 65) return "6";
    else if (percentage >= 60) return "5";
    else if (percentage >= 55) return "4";
    else if (percentage >= 50) return "3";
    else if (percentage >= 40) return "2";
    else if (percentage >= 25) return "1";
    else return "0 (Неудовлетворительно)";
}

std::string TestSession::toString() const {
    std::ostringstream oss;
    oss << userLogin << "~" << testName << "~" << score << "~"
        << maxScore << "~" << date << "~" << completed;
    return oss.str();
}