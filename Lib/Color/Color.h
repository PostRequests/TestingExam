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

	Color - хранит 2 цвета фон и текста, 
	управляет своими цветами.

***************************************************/
#pragma once
#include <iostream>
#include <string>
#define BlackBG  40   // Фоновый черный
#define BlackFG  30   // Текстовый черный
#define RedBG  41     // Фоновый красный
#define RedFG  31     // Текстовый красный
#define GreenBG  42   // Фоновый зеленый
#define GreenFG  32   // Текстовый зеленый
#define YellowBG  43  // Фоновый желтый
#define YellowFG  33  // Текстовый желтый
#define BlueBG  44    // Фоновый синий
#define BlueFG  34    // Текстовый синий
#define MagentaBG  45 // Фоновый пурпурный
#define MagentaFG  35 // Текстовый пурпурный
#define CyanBG  46    // Фоновый циановый
#define CyanFG  36    // Текстовый циановый
#define WhiteBG  47   // Фоновый белый
#define WhiteFG  37   // Текстовый белый

class Color
{
private:
	int BG; //цвет фона
	int FG; //цвет текста
public:
	Color(): BG(BlackBG), FG(WhiteFG){}
	Color(int c1, int c2) : BG(BlackBG), FG(WhiteFG) { setColor(c1,c2); }
	Color(int c1) : BG(BlackBG), FG(WhiteFG) { setColor(c1); }
	~Color() { reset(); }
	/**
	 * @brief  Присваиваем цвет другого элемента
	 * @param c - Номер цвета
	 * @param c2 - Номер цвета2
	 * @return Ссылка на текущий цвет для цепочки вызовов
	 */
	Color& setColor(int с1, int с2);
	/**
	 * @brief  Присваиваем цвет другого элемента
	 * @param c - Номер цвета 
	 * @return Ссылка на текущий цвет для цепочки вызовов
	 */
	Color& setColor(int c);
	/**
	 * @brief  Присваиваем цвет другого элемента
	 * @param c - Цветовая схема другого элемента
	 * @return Ссылка на текущий цвет для цепочки вызовов
	 */
	Color& setColor(const Color& c);
	/**
	 * @brief Геттер фонового цвета
	 * @return Возвращает номер цвета фона
	 * @return Ссылка на текущий цвет для цепочки вызовов
	 */
	inline int getBG() { return BG; }
	/**
	 * @brief Геттер текстового цвета
	 * @return Возвращает номер цвета текста
	 */
	inline int getFG() { return FG; }
	/**
	 * @brief Оператор присвоения цвета
	 */
	inline void operator= (Color c) { setColor(c); }
	/**
	 * @brief Раскрашиваем консоль в сохраненные в объект цвета
	 * @return Ссылка на текущий цвет для цепочки вызовов
	 */
	Color& colorize();
	/**
	* @brief Устанавливаем цвет текста или фона
	* @param с - Номер цвета
	* @param с1 - Номер цвета 2
	* @return Ссылка на текущий цвет для цепочки вызовов
	*/
	inline static void colorize(int c, int c1) { std::cout << "\x1b[" << c << ';' << c1 << 'm'; }
	/**
	* @brief Устанавливаем цвет текста или фона
	* @param с - Номер цвета 
	*/
	inline static void colorize(int c) { std::cout << "\x1b[" << c << 'm'; }
	/**
	* @brief Устанавливаем цвет текста в RGB формате
	* @param r - Оттенок красного
	* @param g - Оттенок Зеленого
	* @param b - Оттенок синего
	*/
	inline static void colorizeRGB_FG(int r, int g, int b) { std::cout << "\x1b[38;2;" << r << ";" << g << ";" << b << "m"; }
	/**
	* @brief Устанавливаем цвет фона в RGB формате
	* @param r - Оттенок красного
	* @param g - Оттенок Зеленого
	* @param b - Оттенок синего
	*/
	inline static void colorizeRGB_BG(int r, int g, int b) { std::cout << "\x1b[48;2;" << r << ";" << g << ";" << b << "m"; }
	/**
	 * @brief Сбрасывает цвет консоли, не изменяя при этом значения переменной
	 * @return Ссылка на текущий цвет для цепочки вызовов
	 */
	Color& reset();
	/**
	 * @brief Возвращает цвет в формате string
	 */
	inline std::string string() { return "\x1b[" + std::to_string(BG) + ';' +std::to_string(FG) + "m";}
	/**
	 * @brief Возвращает цвет 0 в формате string
	 */
	inline std::string string0() { return "\x1b[0m"; }
};

