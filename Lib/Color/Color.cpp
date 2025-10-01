#include "Color.h"
Color& Color::setColor(int c) {
	if (c == BG || c == FG) return *this;
	if (c >= BlackFG && c <= WhiteFG) //Если цвет в диапазоне цветов текста, устанавливаем цвет текста
		FG = c;
	else if (c >= BlackBG && c <= WhiteBG)//Если цвет в диапазоне цветов фона, устанавливаем цвет фона
		BG = c;
	else
		throw std::exception("Цвет вне диапазона!");
	return *this;
}
Color& Color::setColor(int с1, int с2) {
	setColor(с1);
	return setColor(с2);
}
Color& Color::setColor(const Color& c) {
	if (this->BG == c.BG && this->FG == c.FG) return *this;
	this->BG = c.BG;
	this->FG = c.FG;
	return* this;
}
Color& Color::colorize() {
	std::cout << "\x1b[" << BG << ';' << FG << 'm';
	return *this;
}
Color& Color::reset() {
	std::cout << "\x1b[" << 0 << 'm';
	return *this;
}