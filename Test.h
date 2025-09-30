#pragma once
#include "Question.h"
#include <iostream>
#include <vector>
#include <string>
class Test
{
private:
	std::string testName; // �������� �����
	std::vector<Question> questions; // ������ ��������
public:
	Test(const std::string& name);

	void addQuestion(const Question& question);
	void removeQuestion(int index);

	Question& getQuestion(int index);
	std::string getTestName();

	int size();
};

