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

	Box - рисуем прямоугольники, выводим текс в пределах границ.

***************************************************/
#pragma once
#include "../Position/Position.h"
#include "../Color/Color.h"
#include <vector>
#include <string>

/// Набор символов для рисования таблиц
//LT1: "┌" H1 : "─" RT1 : "┐" V1 : "│" LD1 : "└" RD1 : "┘" LV1 : "├" RV1 : "┤" DH1 : "┴" UH1 : "┬"C1 : "┼" 
#define Board_LT2 (char)201 //╔ левый верхний двойной
#define Board_H2 (char)205 //═ горизонтальный двойной
#define Board_RT2 (char)187 //╗ правый верхний двойной
#define Board_V2 (char)186 //║ вертикальный двойной
#define Board_LD2 (char)200 //╚ левый нижний двойной
#define Board_RD2 (char)188 //╝ правый нижний двойной
#define Board_LV2 (char)204 //╠ левый вертикальный двойной
#define Board_RV2 (char)185 //╣ правый вертикальный двойной
#define Board_DH2 (char)202 //╩ нижний горизонтальный двойной
#define Board_UH2 (char)203 //╦ верхний горизонтальный двойной
#define Board_C2 (char)206 //╬ центральный двойной

class Box
{
private:
	
	Position start;//Крайняя левая верхняя точка
	Position end;//Крайняя нижняя правая точка
	Position cur;//Текущее положение текста
	Color colBor; //Цвет окантовки
	Color colT;// Цвет текста и фона

	std::vector<std::string> splitWord(const std::string& s);
public:
	Box() : start(1, 1), cur(2, 2) { end.setConsoleSize(); }
	Box(int x, int y, int x2, int y2) : start(x, y), end(x2, y2), cur(x + 1, y + 1) {}
	Box(Position s, Position e) :start(s), end(e), cur(s.getX() + 1, s.getY() + 1) {}
	Box(Position s, int x, int y) :start(s), end(x,y), cur(s.getX() + 1, s.getY() + 1) {}
	Box(int x, int y, Position e) :start(x,y), end(e), cur(x + 1, y + 1) {}
	//~Box() { hide(); }
	/**
	 * @brief Возвращает строку с заданными параметрами
	 * @param s длинна строки
	 * @param r символ заполнения строки
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	inline static std::string getCharRow(int s, char r) { return std::string(s, r);}
	/**
	 * @brief Возвращает строку с заданными параметрами
	 * @param s длинна строки
	 * @param l первый символ строки
	 * @param c символ который печатается в середине
	 * @param r последний символ строки
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	inline static std::string getCharRow(int s, char l, char c, char r) {
		return l + std::string(s, c) + r;	}
	/**
	 * @brief Устанавливаем координаты коробки
	 * @param xs Позиция X верхней левой точки
	 * @param ys Позиция Y верхней левой точки
	 * @param xe Позиция X нижней правой точки
	 * @param ye Позиция Y нижней правой точки
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& setCoordinate(int x, int y, int x2, int y2);
	/**
	 * @brief Устанавливает цвет рамки
	 * @param c номер цвета
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& setColorBoard(int c);
	/**
	 * @brief Устанавливает цвет рамки
	 * @param c цветовая палитра
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& setColorBoard(const Color& c);
	/**
	 * @brief Устанавливает цвет рамки
	 * @param с1 - номер первого  цвета
	 * @param с2 - номер второго  цвета
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& setColorBoard(int с1, int с2);
	/**
	 * @brief Устанавливает цвет текста
	 * @param с - номер цвета
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& setColorText(int c);
	/**
	 * @brief Устанавливает цвет текста
	 * @param с1 - номер первого  цвета
	 * @param с2 - номер второго  цвета
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& setColorText(int с1, int с2);
	/**
	 * @brief Устанавливает цвет текста
	 * @param c цветовая палитра
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& setColorText(const Color& c);
	/**
	 * @brief Рисует сплошной квадрат в заданном диапазоне
	 * @param xs Позиция X верхней левой точки
	 * @param ys Позиция Y верхней левой точки
	 * @param xe Позиция X нижней правой точки
	 * @param ye Позиция Y нижней правой точки
	 */
	static void drawFillBox(int xs, int ys, int xe, int ye);
	inline void drawFillBox() { drawFillBox(start.getX() + 1, start.getY() + 1, end.getX() - 1, end.getY() - 1); };
	/**
	 * @brief Рисует сплошной квадрат в заданном диапазоне
	 * @param s Позиция верхней левой точки
	 * @param e Позиция нижней правой точки
	 */
	inline static void drawFillBox(Position& s, Position& e) { drawFillBox(s.getX(), s.getY(), e.getX(), e.getY()); }
	/**
	 * @brief Рисует рамку по сохраненным внутри объекта параметрам
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& drawBox();
	/**
	 * @brief Рисует рамку в заданном диапазоне
	 * @param xs Позиция X верхней левой точки
	 * @param ys Позиция Y верхней левой точки
	 * @param xe Позиция X нижней правой точки
	 * @param ye Позиция Y нижней правой точки
	 */
	static void drawBox(int xs, int ys, int xe, int ye);
	/**
	 * @brief Рисует рамку в заданном диапазоне
	 * @param s Позиция верхней левой точки
	 * @param e Позиция нижней правой точки
	 */
	inline static void drawBox(Position& s, Position& e) { drawBox(s.getX(), s.getY(), e.getX(), e.getY()); };
	/**
	 * @brief Печатает текст с переносом внутри рамки
	 * @param s Текст который необходимо напечатать
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */

	/// <summary>
	/// ыва
	/// </summary>
	/// <param name="s"> ыв</param>
	/// <returns> ыв</returns>
	Box& print(const std::string& s);
	/**
	 * @brief Скрывает содержимое внутри рамки
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& cls();
	/**
	 * @brief Скрывает рамку и все содержимое в ней
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& hide();
	/**
	 * @brief возвращает текущую позицию курсора в боксе
	 * @return возвращает текущую позицию курсора в боксе
	 */
	inline Position& getCurPoint() { return cur; }
	/**
	 * @brief Сбрасывает курсор в начало
	 * @return Ссылка на текущий объект Box для цепочки вызовов
	 */
	Box& resetCursor();
	/**
	* @brief Возвращает ширину бокса
	*/
	int width() { return end.getX() - start.getX(); }
};


