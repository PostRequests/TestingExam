#include "Position.h"
Position& Position::setX(int x){
	this->x = x;
	return *this;
}
Position& Position::setY(int y){
	this->y = y;
	return *this;
}
Position& Position::go() {
	std::cout << "\033[" << y << ";" << x << "H";
	return *this;
}
Position& Position::setPos(const Position& o) {
	*this = o;
	return *this;
}
Position& Position::goTo(int x, int y) {
	setPos(Position(x, y));
	return go();
}
Position& Position::goTo(const Position& o) {
	setPos(o);
	return go();
}
Position& Position::print(const std::string& s){
	go();
	std::cout << s;
	x += s.size();
	return *this;
}
Position& Position::printLn(const std::string& s) {
	go();
	std::cout << s;
	return nextLine();
}
Position& Position::printLn(const char s) {
	go();
	std::cout << s;
	return nextLine();
}
Position& Position::setConsoleSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
	else {
		x = -1;
		y = -1;
	}
	return *this;
}
Position& Position::nextLine(int line) {
	for (int i = 0; i < line; i++)
		y++;
	x = startX;
	return *this;
}
Position& Position::prevLine(int line) {
	for (int i = 0; i < line; i++)
		y--;
	x = startX;
	return *this;
}
Position& Position::restart() {
	x = startX;
	y = startY;
	return *this;
}
Position& Position::plusX(int x) {
	this->x += x;
	return*this;
}
Position& Position::plusY(int y) {
	this->y += y;
	return *this;
}
Position& Position::show(int x, int y) {
	moveTo(x, y);
	show();
	return *this;
}
Position& Position::setStartX(int x) { 
	this->startX = x; 
	return *this;
}
Position& Position::setStartY(int y) {
	this->startY = y; 
	return *this;
}