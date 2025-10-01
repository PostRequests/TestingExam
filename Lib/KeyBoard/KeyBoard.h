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

    KeyBoard - Преобразует нажатия кнопок в класс KEY.

***************************************************/
#pragma once
#include <iostream>
#include <conio.h>      
#include <windows.h>    
enum class KEY {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    ESCAPE,
    ANY,
    CHARACTER,
    TAB,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    BACKSPACE,
    SPACE,
    C,
    X,
    V,
    DEL,
    F8
};

class KeyBoard
{
public:
    // Получить клавишу от пользователя
    static KEY getKey();
    // Проверяет, нажата ли какая-то клавиша
    static inline bool isKeyPressed() { return _kbhit() != 0;   }
    // Возвращает код последней нажатой клавиши (если нужно)
    static inline int getLastChar() { return static_cast<int>(_getch());  }
};

