#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <conio.h>

class Menu {
private:
    std::vector<std::string> items;
    std::vector<std::function<void()>> actions;
    int x, y;
    std::string title;
    int selected;

public:
    Menu(int x, int y, const std::string& title);
    Menu& addItem(const std::string& head, const std::function<void()>& fEnter);
    void run();
    void display();
};