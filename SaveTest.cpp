#include "SaveTest.h"
// Вспомогательный метод для разделения строки
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
// Вспомогательный метод для разбора строки вопроса
Question parseQuestion(const std::string& line) {
    std::vector<std::string> parts = splitString(line, '~');

    if (parts.empty()) {
        throw std::exception("Неверный формат строки вопроса");
    }

    // Первая часть - текст вопроса
    std::string questionText = parts[0];
    Question question;
    question.setQuestionText(questionText);

    // Остальные части - ответы
    for (size_t i = 1; i < parts.size(); i++) {
        if (parts[i].length() < 2) {
            continue; // Пропускаем некорректные ответы
        }

        char marker = parts[i][0]; // Первый символ - маркер правильности
        std::string answerText = parts[i].substr(1); // Остальная часть - текст ответа

        bool isCorrect = (marker == '+');
        question.addAnswer(answerText, isCorrect);
    }

    return question;
}


SaveTest::SaveTest(const std::string& path)
{
    // Получаем абсолютный путь
    fs::path fullPath = std::filesystem::absolute(path);

    // Получаем путь к директории (без имени файла)
    fs::path dirPath = fullPath.parent_path();

    // Проверяем существует ли директория
    if (!std::filesystem::exists(fullPath)) {
        try {
            // Создаем все недостающие директории
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
        throw std::exception("Не удалось открыть файл");
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
        std::cout << "Ошибка при загрузке тестов: " << e.what() << std::endl;
        throw;
    }

    return manager;
}

