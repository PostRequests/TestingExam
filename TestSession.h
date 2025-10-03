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

    void setScore(int score, int maxScore); //Устанавливает количество набранных баллов и максимально возможный балл.
    void markCompleted(); //Отмечает тест как завершенный.

    std::string getUserLogin() const; //Кто проходил тест?
    std::string getTestName() const; // Какой тест
    int getScore() const; // Сколько баллов набрал
    int getMaxScore() const; //сколько можно было набрать максимум
    time_t getDate() const; //Когда проходили тест
    bool isCompleted() const; //Тест уже завершен

    std::string toString() const; //Преобразует все данные в одну строку специального формата
};