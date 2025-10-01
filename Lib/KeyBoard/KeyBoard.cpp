#include "KeyBoard.h"

KEY KeyBoard::getKey() {
    int key = _getch(); 
    if (key == 0 || key == 0xE0) 
        key = _getch();
    
    switch (key) {
    case 72: return KEY::UP;
    case 80: return KEY::DOWN;
    case 75: return KEY::LEFT;
    case 77: return KEY::RIGHT;
    case 13: return KEY::ENTER;
    case 27: return KEY::ESCAPE;
    case 9:  return KEY::TAB;
    case 8:  return KEY::BACKSPACE;
    case 59:  return KEY::F1;
    case 60:  return KEY::F2;
    case 61:  return KEY::F3;
    case 62:  return KEY::F4;
    case 63:  return KEY::F5;
    case 64:  return KEY::F6;
    case 65:  return KEY::F7;
    case 66:  return KEY::F8;
    case 32:  return KEY::SPACE;
    case 83:  return KEY::DEL;
    case 99:case 67: case 241: case 209: return KEY::C;
    case 120:case 88: case 247: case 215: return KEY::X;
    case 118:case 86: case 236: case 204: return KEY::V;
        
    default: return KEY::ANY;
    }
}