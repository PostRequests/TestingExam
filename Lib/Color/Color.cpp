#include "Color.h"
Color& Color::setColor(int c) {
	if (c == BG || c == FG) return *this;
	if (c >= BlackFG && c <= WhiteFG) //���� ���� � ��������� ������ ������, ������������� ���� ������
		FG = c;
	else if (c >= BlackBG && c <= WhiteBG)//���� ���� � ��������� ������ ����, ������������� ���� ����
		BG = c;
	else
		throw std::exception("���� ��� ���������!");
	return *this;
}
Color& Color::setColor(int �1, int �2) {
	setColor(�1);
	return setColor(�2);
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