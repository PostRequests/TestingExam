#include "Test.h"
Test::Test(const std::string& name)
    : testName(name){}

void Test::addQuestion(const Question& question)
{
    questions.push_back(question);
}

void Test::removeQuestion(int index)
{
    if (index >= 0 && index < questions.size()) {
        questions.erase(questions.begin() + index);
    }
}

Question& Test::getQuestion(int index)
{
    if (index < 0 || index >= questions.size()) {
        throw std::exception("Индекс за пределами допустимого");
    }
    return questions[index];

}

std::string Test::getTestName()
{
    return this->testName;
}

int Test::getScore(int curQuest)
{
    double scoreInPercent = 12 / (double)this->size();
    int result = curQuest * scoreInPercent;
    return result;
}

int Test::size() {
    return questions.size();
}