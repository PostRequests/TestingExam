/***************************************************
        ╔══════════════════════════════════╗
        ║      ЭКЗАМЕНАЦИОННАЯ РАБОТА      ║
        ╠══════════════════════════════════╣
        ║ Ученик академии "TOP"            ║
        ║ Группа: ВПД 411                  ║
        ║ Бородин Сергей Викторович        ║
        ╠══════════════════════════════════╣
        ║ Тема: Файловый менеджер на C++   ║
        ║                                  ║
        ╚══════════════════════════════════╝

    MenuItem - элемент меню, хранит в себе имя
        и два действия при наведении и нажатии.

***************************************************/
#pragma once
#include <string>
#include <functional>
#include "../Box/Box.h"
class MenuItem {
protected:
    std::string head; //Название менею
    std::function<void()> enter; //Действие при выборе элемента
    std::function<void()> move; //Действие при наведении на элемент меню

public:
    MenuItem()
        : head(""),  enter(nullptr), move(nullptr) {
    }
    MenuItem( const std::string& h, const std::function<void()>& e)
        : head(h), enter(e) {
    }
    MenuItem(const std::string& n, const std::function<void()>& e,
        const std::function<void()>& m)
        : head(n),  enter(e), move(m){
    }
    /*Устанавливает имя элемента*/
    inline void setHead(const std::string& h) { head = h; }
    /*Устанавливает лямбда выражение при нажатии через меню*/
    inline void setEnter(const std::function<void()>& e) { enter = e; };
    /*Устанавливает лямбда выражение при наведении через меню*/
    inline void setMove(const std::function<void()>& m) { move = m; };
    /*Возвращает имя элемента меню (string)*/
    inline std::string& getHead() { return head; }
    /*Запускает действие при нажатии через меню*/
    inline void onEnter() {if (enter) enter();}
    /*Запускает действие при наведении через меню*/
    inline void onMove() { if (move) move(); }
};

