#include "SaverUserManager.h"
SaverUserManager::SaverUserManager(const std::string& path) {
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
void SaverUserManager::save(Users& um) {
    fs::path filename = path / (std::string(um.getLogin()) + ".usr");
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename.string());
    }
    file << um.ToString() << std::endl;
    file.close();
    std::cout << filename;
}
void SaverUserManager::save(UserManager& um) {
    for (auto& us : um.users) {
        this->save(*us);
    }
}
UserManager SaverUserManager::load() {
    UserManager um;
    return um;
}