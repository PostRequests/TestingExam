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

	Menu - позволяет конструировать меню, выводить 
		на экран.


***************************************************/
#pragma once
#include "../Color/Color.h"
#include "../Position/Position.h"
#include "../Box/Box.h"
#include "ItemM.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <conio.h>
class Menu
{
private:
	Position start;
	int cur;//Текущий выбранный номер элемента
	int count;//Количество всех элементов
	int width;//Ширина меню
	bool visible = false;//Отображает видимость меню на экране
	Color сSelected;//Цвет выделения пункта меню
	Color cDefault;//Основной цвет меню
	std::string head;//Заголовок меню
	std::vector<MenuItem> elem;//Элемент пункта меню
	Box xBox;//Область отрисовки поля ввода
	bool boxVisible;
	

	/**
	 * @brief Рассчитывает ширину меню, применяется при добавлении нового пункта меню
	 * @param s Текст пункта меню, относительно которого рассчитывается максимальный размер
	 */
	inline void calcWidth(std::string s) { width = ( (width>(int)s.length() + 3))? width: (int)s.length() + 2; }
	//Печатаем элементы меню
	void printElMenu();
	//Выводим на экран меню
	void show();
	//Перекрашиваем элемент меню
	void redrawItem(Color color);
	//Очищаем меню с экрана
	void hide() {  }
public:
	Menu() :start(2, 2), cur(0), count(0), width(0), head() {  сSelected.setColor(RedBG); }
	Menu(int x, int y, int cur, int count, int width, std::string h)
		: start(x + 1 , y + 1), cur(0), count(0), width(0)	{
		setHead(h);
		сSelected.setColor(RedBG);
	}
	Menu(int x, int y, std::string h) :Menu(x, y, 0, 0, 0, h) {}
	Menu(Position p) :Menu(p.getMinX(), p.getMinY(), 0, 0, 0, "") {}

	//Устанавливаем основной цвет меню
	/**
	 * @brief устанавливает 2 цвета меню, фона и цвета текста
	 * @param BG цвет заднего фона текста
	 * @param FG цвет текста
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& setColorText(int BG, int FG);
	/**
	 * @brief Добавляет новы пункт меню с заголовком но без действия при нажатии
	 * @param head текст заголовка меню
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	inline Menu& addItem(const std::string& head) { return addItem(head, nullptr); }
	/**
	 * @brief Добавляет новый пункт меню с заголовком и действием при нажатии Enter.
	 * @param head   - Заголовок пункта меню
	 * @param fEnter - Функция, которая выполняется при выборе этого пункта
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& addItem(const std::string& head, const std::function<void()>& fEnter);
	/**
	 * @brief Добавляет новый пункт меню с заголовком, действием при Enter и действием при переходе курсора.
	 * @param head  - Заголовок пункта меню
	 * @param fEnter - Функция, которая выполняется при нажатии Enter
	 * @param fmove - Функция, которая выполняется при переходе к пункту
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& addItem(const std::string& head, const std::function<void()>& fEnter, const std::function<void()>& fmove);
	/**
	 * @brief Задаёт координаты прямоугольной области (рамки), в которой будет отображаться меню.
	 * @param x   - Координата X левого верхнего угла
	 * @param y   - Координата Y левого верхнего угла
	 * @param x2  - Координата X правого нижнего угла
	 * @param y2  - Координата Y правого нижнего угла
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& setBox(int x, int y, int x2, int y2);
	/**
	 * @brief Устанавливает цвет бокса
	 * @param c1 цвет 1
	 * @param c2 цвет 2
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& setColorBox(int c1, int c2);
	/**
	 * @brief Устанавливает цвет бокса
	 * @param c1 цвет 1
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& setColorBox(int c1);
	/**
	 * @brief Задаёт область отрисовки меню через две позиции: начальную и конечную.
	 * @param s - Начальная позиция (левый верхний угол)
	 * @param e - Конечная позиция (правый нижний угол)
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& setBox(Position& s, Position& e);
	/**
	 * @brief Выводит заданный текст в текущей области меню (внутри рамки).
	 * @param text - Текст для вывода
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& printBox(const std::string& text);
	/**
	 * @brief Очищает область дополнительного текстового блока
	 */
	Menu& clsBox();
	/**
	 * @brief Устанавливает шапку меню
	 * @param h - Текст для установки шапки
	 * @return Ссылка на текущий объект Menu для цепочки вызовов
	 */
	Menu& setHead(std::string h);
	/**
	 * @brief Запускает меню
	 * @param r - закрывается ли меню после ввода
	 * @return возвращает выбранный элемент меню
	 */
	int run(bool r = false);
	/**
	 * @brief Позволяет получить ширину поля меню
	 * @return Возвращает ширину меню
	*/
	inline int getWidth() { return width + 3; }
	/**
	 * @brief Описание функции
	 * @return Возвращает элемент класса Box
	 */
	inline Box& getBox() { return xBox; }
	
};
