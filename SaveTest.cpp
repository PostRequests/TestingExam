#include "SaveTest.h"
// ��������������� ����� ��� ���������� ������
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        if (!item.empty()) {
            result.push_back(item);
        }
    }

    return result;
}
// ��������������� ����� ��� ������� ������ �������
Question parseQuestion(const std::string& line) {
    std::vector<std::string> parts = splitString(line, '~');

    if (parts.empty()) {
        throw std::exception("�������� ������ ������ �������");
    }

    // ������ ����� - ����� �������
    std::string questionText = parts[0];
    Question question;
    question.setQuestionText(questionText);

    // ��������� ����� - ������
    for (size_t i = 1; i < parts.size(); i++) {
        if (parts[i].length() < 2) {
            continue; // ���������� ������������ ������
        }

        char marker = parts[i][0]; // ������ ������ - ������ ������������
        std::string answerText = parts[i].substr(1); // ��������� ����� - ����� ������

        bool isCorrect = (marker == '+');
        question.addAnswer(answerText, isCorrect);
    }

    return question;
}


SaveTest::SaveTest(const std::string& path)
{
    // �������� ���������� ����
    fs::path fullPath = std::filesystem::absolute(path);

    // �������� ���� � ���������� (��� ����� �����)
    fs::path dirPath = fullPath.parent_path();

    // ��������� ���������� �� ����������
    if (!std::filesystem::exists(fullPath)) {
        try {
            // ������� ��� ����������� ����������
            std::filesystem::create_directories(fullPath);
            this->path = fullPath;
        }
        catch (const fs::filesystem_error& ex) {
            std::cerr << "Error creating directory: " << ex.what() << std::endl;
            throw;
        }
    }
    else this->path = fullPath;
}

void SaveTest::save(Test& test)
{
    fs::path filename = path / (std::string(test.getTestName()) + ".tst");
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::exception("�� ������� ������� ����");
    }
    for (int i = 0; i < test.size(); i++)
    {
        file << test.getQuestion(i).toString() << std::endl;
    }
    file.close();
}

TestManager SaveTest::load() {
    TestManager manager;

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".tst") {
                std::string filename = entry.path().stem().string(); 
                Test test(filename);
                std::ifstream file(entry.path());
                std::string line;
                while (std::getline(file, line)) {
                    if (!line.empty()) {
                        Question question = parseQuestion(line);
                        test.addQuestion(question);
                    }
                }
                file.close();
                manager.addTest(test);
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "������ ��� �������� ������: " << e.what() << std::endl;
        throw;
    }

    return manager;
}

