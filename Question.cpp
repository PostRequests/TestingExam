#include "Question.h"

void Question::setQuestionText(const std::string& text) {
    questionText = text;
}

std::string Question::getQuestionText() {
    return questionText;
}

Question& Question::addAnswer(const std::string& answer, bool isCorrect) {
    answers[answer] = isCorrect;
    return *this;
}

void Question::removeAnswer(const std::string& answer) {
    answers.erase(answer);
}

bool Question::checkAnswer(const std::string& answer) {
    auto it = answers.find(answer);
    if (it != answers.end()) {
        return it->second; // Возвращаем true если ответ правильный
    }
    return false; // Ответ не найден
}

std::vector<std::string> Question::getAnswers() const {
    std::vector<std::string> result;
    for (const auto& pair : answers) {
        result.push_back(pair.first); 
    }
    return result;
}

bool Question::checkQuestion(int countCorrect) {
    int correct = 0;
    for (const auto& pair : answers) {
        if (pair.second)
            correct++;
    }
    return correct == countCorrect;
}

std::string Question::toString() {
    std::string r = questionText;
    for (const auto& pair : answers) {
        char isCorrect = (pair.second ? '+' : '-');
        r += "~" + std::string(1, isCorrect) + pair.first;
    }
    return r;  // Возвращаем копию - безопасно!
}
