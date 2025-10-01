#include "SaverUserManager.h"
SaverUserManager::SaverUserManager(std::string& path) {
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
            std::cerr << "Не удалось создать дерикторию: " << ex.what() << std::endl;
            throw;
        }
    }
    else this->path = fullPath;
}
void SaverUserManager::save(Users& um) {
    fs::path filename = path / (std::string(um.getLogin()) + ".usr");
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::exception("Не удалось открыть файл");
    }
    file << um.ToString() << std::endl;
    file.close();
}
void SaverUserManager::save(UserManager& um) {
    for (auto& us : um.users) {
        this->save(*us);
    }
}



UserManager SaverUserManager::load() {
    UserManager um;
    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cout << "Directory does not exist: " << path << std::endl;
        return um;
    }
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".usr") {
                std::ifstream file(entry.path());
                if (file.is_open()) {
                    std::string firstLine;
                    if (std::getline(file, firstLine)) {
                        // Парсим строку: Role~login~password~fullName~phoneNumber
                        std::vector<std::string> parts;
                        std::istringstream iss(firstLine);
                        std::string part;

                        // Разделяем строку по ~
                        while (std::getline(iss, part, '~')) {
                            parts.push_back(part);
                        }

                        // Проверяем что получили 5 частей
                        if (parts.size() == 5) {
                            std::string role = parts[0];
                            std::string login = parts[1];
                            std::string password = parts[2];
                            std::string fullName = parts[3];
                            std::string phoneNumber = parts[4];

                            // Создаем пользователя в зависимости от роли
                            bool success = false;
                            if (role == "Admin") {
                                success = um.createAdmin(login, password, fullName, phoneNumber);
                            }
                            else if (role == "Guest") {
                                success = um.registerGuest(login, password, fullName, phoneNumber);
                            }
                        }
                        
                    }
                    file.close();
                }
            }
        }
    }
    catch (const fs::filesystem_error& ex) {
        std::cerr << "Ошибка загрузки: " << ex.what() << std::endl;
    }

    return um;
}