#pragma once
#include <map>
#include <string>
#include <vector>
class Question
{
private:
	std::string questionText; // Текст вопроса
	std::map<std::string, bool> answers; // Варианты ответов 
public:
	Question() {};
	
	void setQuestionText(const std::string& text);
	Question& addAnswer(const std::string& answer, bool isCorrect);
	void removeAnswer(const std::string& answer);

	std::string getQuestionText();
	std::vector<std::string> getAnswers() const;

	bool checkAnswer(const std::string& answer);
	bool checkQuestion(int countCorrect);

	std::string toString();
};

