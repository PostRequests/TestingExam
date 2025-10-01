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

	Position - позволяет хранить и управлять координатами,
		так же писать текст с переходами.

***************************************************/
#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
class Position
{
private:
	int x; //Позиция х
	int y; //Позиция у
	int startX; //Позиция х изначальная
	int startY; //Позиция у изначальная
public:
	Position() : x(1), y(1), startX(1), startY(1) {}
	Position(const Position& o) : Position(o.x, o.y) {}
	Position(int x, int y) : x(x), y(y), startX(x), startY(y) {}
	
	/// Установка точки х без перехода
	Position& setX(int x);
	/// Установка точки у без перехода
	Position& setY(int y);
	/// Установка точки без перехода
	Position& setPos(const Position& o);
	/// Установка точки без перехода
	inline Position& setPos(int x, int y) { return setPos(Position(x, y)); }
	/// Переход по сохраненным координатам
	Position& go();
	/// Переход и сохранение новых координат
	Position& goTo(const Position& o);
	/// Переход и сохранение новых координат
	Position& goTo(int x, int y);
	/// Переход и сохранение новых координат
	inline Position& goTo() { return goTo(*this); }
	/// Печатает на экране текущие координаты
	inline void show() { std::cout << "[x:" << x << ",y:" << y << "]\n"; }
	/// Печатает на экране текущие координаты в указанном месте
	Position& show(int x, int y);
	/// Добавляет у + 1, без перехода
	Position& nextLine(int line = 1);
	/// Отнимает у 1 1, без перехода
	Position& prevLine(int line = 1);
	/// Добавляет у + 1, без перехода
	inline void operator++() { nextLine(); }
	/// Добавляет у + 1, без перехода
	inline void operator+=(int x) { nextLine(x); }
	/// Добавляет у - 1
	inline void operator--() { prevLine(); }
	/// Добавляет у - 1
	inline void operator-=(int x) { prevLine(x); }
	inline bool operator==(Position a) { return ((a.x == x && a.y == y) ? true : false); }
	/// Переходит по сохраненным координатам и печатает текст
	Position& print(const std::string& s);
	/// Переходит по сохраненным координатам и печатает текст, в конце переход на следующий уровень
	Position& printLn(const std::string& s);
	/// Переходит по сохраненным координатам и печатает текст, в конце переход на следующий уровень
	Position& printLn(const char s);
	///  Устанавливает координаты в точку размера консоли
	Position& setConsoleSize();
	/// Возвращает координаты по х
	inline int getX() { return x; }
	/// Возвращает координаты по у
	inline int getY() { return y; }
	// возвращает изначально установленную координату х
	inline int getMinX() { return startX; }
	// возвращает изначально установленную координату у
	inline int getMinY() { return startY; }
	Position& setStartX(int x);
	Position& setStartY(int y);
	/// Возвращение к первоначальным координатам
	Position& restart();
	//Перемещает курсор в указанную позицию
	inline static void moveTo(int x, int y) { std::cout << "\033[" << y << ";" << x << "H"; }
	//Добавляет к х определенное количество точек
	Position& plusX(int x);
	//Добавляет к у определенное количество точек
	Position& plusY(int y);
};

