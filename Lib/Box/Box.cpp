#include "Box.h"
void printRowChars(int s, char l, char c, char r) {
    std::cout << l;
    for (int i = 1; i < s - 1; i++)
        std::cout << c;
    std::cout << r;
}


void Box::drawBox(int xs, int ys, int xe, int ye) {
    system("chcp 866>nul");
    Position start{ xs, ys };
    start.go();
    int lengthX = xe - xs - 1; //Длинна строки
    int lengthY = ye - ys; //Количество строк
    std::string row = getCharRow(lengthX, Board_LT2, Board_H2, Board_RT2); //Устанавливаем верхнюю строку
    start.printLn(row);//Печатаем строку с переходом
    row = getCharRow(lengthX, Board_V2, ' ', Board_V2); //Устанавливаем центральную строку
    for (int i = 1; i < lengthY; i++)
        start.printLn(row);
    row = getCharRow(lengthX, Board_LD2, Board_H2, Board_RD2); //Устанавливаем нижнюю строку
    start.printLn(row);
    system("chcp 1251>nul");
}
Box& Box::drawBox() {
    colBor.colorize();
    drawBox(start.getX(), start.getY(), end.getX(), end.getY());
    colBor.reset();
    if (colT.getBG() != BlackBG) {
        cur.setY(end.getY() - 1);
        cls();
    }
    cur.restart();
    return*this;
}
void Box::drawFillBox(int xs, int ys, int xe, int ye) {
    int co = xe - xs + 1; //Ширина заполнения
    int li = ye - ys + 1; //Количество заполненных строк
    Position x{ xs,ys };
    std::string emp = getCharRow(co, ' '); //Пустая строка, для ускорения прорисовки
    for (int i = 0; i < li; i++)
        x.printLn(emp);
}
Box& Box::setColorBoard(int c) { 
    colBor.setColor(c); 
    colT.setColor(colBor.getBG());
    return *this;
}
Box& Box::setColorBoard(const Color& c) {
    colBor.setColor(c); 
    colT.setColor(colBor.getBG());
    return *this;
}
Box& Box::setColorBoard(int с1, int с2) { 
    colBor.setColor(с1, с2); 
    colT.setColor(colBor.getBG());
    return *this;
}
Box& Box::setColorText(int c) { 
    colT.setColor(c); 
    return *this;
}
Box& Box::setColorText(int с1, int с2) { 
    colT.setColor(с1, с2); 
    return *this;
}
Box& Box::setColorText(const Color& c) {
    colT.setColor(c);
    return *this;
}
Box& Box::print(const std::string& s) {
    colT.colorize();
    cur.go();//Перемещаем курсор в начальную позицию
    std::vector<std::string> words = splitWord(s);//Разбиваем текст на слова и переносы строк
    int col = cur.getX() - start.getMinX();//Текущая позиция в строке
    const int lineWidth = end.getX() - start.getX() - 1;//Ширина
    for (std::string& word : words) {
        if (word == "\n") {
            cur.nextLine();
            col = 0;
            continue;
        }
        if (col + word.size() > lineWidth) {//Проверяем, помещается ли слово в текущую строку
            if (col == 0 && word.size() > lineWidth) {//Разбиваем слишком длинное слово на части
                for (size_t i = 0; i < word.size(); i += lineWidth) {
                    std::string part = word.substr(i, lineWidth);
                    cur.print(part).nextLine();
                }
                col = 0;
                continue;
            }
            else {//Переносим на новую строку
                cur.nextLine();
                col = 0;
            }
        }
        cur.print(word);
        col += word.size();
        if (col < lineWidth && &word != &words.back()) {//Добавляем пробел после слова
            cur.print(" ");
            col++;
        }
    }
    colT.reset();
    return *this; 
}
std::vector<std::string> Box::splitWord(const std::string& s) {
    std::vector<std::string> result;
    std::string temp;
    for (char ch : s) {
        if (ch != ' ' && ch != '\n') {
            temp += ch;
        }
        else {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
            if (ch == '\n') 
                result.push_back("\n");
        }
    }
    if (!temp.empty()) //Добавляем последнее слово, если оно есть
        result.push_back(temp);
    return result;
}
Box& Box::cls() { 
    colT.colorize();
    Position s{ start };
    Position e{ cur };
    drawFillBox(s.plusX(1).plusY(1), e.setX(end.getX() - 1));
    cur.restart();
    colT.reset();
    return *this;
}
Box& Box::hide() {
    drawFillBox(start, end);
    return *this;
}
Box& Box::setCoordinate(int x, int y, int x2, int y2) {
    start.setPos(x, y).setStartX(x).setStartY(y);
    end.setPos(x2, y2).setStartX(x2).setStartY(y2);
    cur.setStartX(x + 1).setStartY(y + 1);
    return *this;
}
Box& Box::resetCursor() {
    cur.restart();
    return *this;
}