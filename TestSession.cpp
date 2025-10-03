#include "TestSession.h"
#include <sstream>
#include <iomanip>

TestSession::TestSession(const std::string& userLogin, const std::string& testName, const time_t ntime)
    : userLogin(userLogin), testName(testName), score(0), maxScore(12),
    date(ntime), completed(false) {

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





std::string TestSession::toString() const {
    std::ostringstream oss;
    oss << userLogin << "~" << testName << "~" << score << "~"
        << maxScore << "~" << date << "~" << completed;
    return oss.str();
}