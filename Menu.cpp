#include "Menu.h"

Menu::Menu(int x, int y, const std::string& title)
    : x(x), y(y), title(title), selected(0) {
}

Menu& Menu::addItem(const std::string& head, const std::function<void()>& fEnter) {
    items.push_back(head);
    actions.push_back(fEnter);
    return *this;
}

void Menu::clearScreen() {
    system("cls");
}

void Menu::display() {
    clearScreen();

    // ����� ���������
    std::cout << "\n\n";
    for (int i = 0; i < x; i++) std::cout << " ";
    std::cout << "=== " << title << " ===\n\n";

    // ����� ������� ����
    for (size_t i = 0; i < items.size(); i++) {
        for (int j = 0; j < x; j++) std::cout << " ";

        if (i == selected) {
            std::cout << "> " << items[i] << " <" << std::endl;
        }
        else {
            std::cout << "  " << items[i] << std::endl;
        }
    }

    std::cout << "\n\n����������� ������� ��� ���������, Enter ��� ������, Esc ��� ������";
}

void Menu::run() {
    char key;
    do {
        display();
        key = _getch();

        if (key == 72) { // ������� �����
            selected = (selected - 1 + items.size()) % items.size();
        }
        else if (key == 80) { // ������� ����
            selected = (selected + 1) % items.size();
        }
        else if (key == 13) { // Enter
            if (selected >= 0 && selected < actions.size()) {
                clearScreen();
                actions[selected]();
                if (selected != items.size() - 1) { // ���� �� ��������� ����� (�����)
                    std::cout << "\n\n������� ����� ������� ��� �����������...";
                    _getch();
                }
            }
        }
    } while (key != 27); // Esc ��� ������
}