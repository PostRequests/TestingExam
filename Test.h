#pragma once
#include "Question.h"
#include <iostream>
#include <vector>
#include <string>
class Test
{
private:
	std::string testName; // Название теста
	std::vector<Question> questions; // Список вопросов
public:
	Test(const std::string& name);

	void addQuestion(const Question& question);
	void removeQuestion(int index);

	Question& getQuestion(int index);
	std::string getTestName();

	int size();
};

