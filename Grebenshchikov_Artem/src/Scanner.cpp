#include <iostream>
#include "Scanner.h"
#include "SafeInput.h"



void Scanner::printAbility() {
    std::cout << "Была выбрана способность: Сканер" << std::endl;
}


bool Scanner::use(GameField& gameField, ManagerShip& manager) {
    int x, y;
    std::cout << "Введите координаты верхнего левого угла квадрата 2x2" << std::endl;
    x = safeInput();
    y = safeInput();
    if (x < 0 || y < 0 || x >= gameField.getWidth() - 1 || y >= gameField.getHeight() - 1) {
        std::cout << "Координаты вне границ поля" << std::endl;
        return false;
    }

    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            int newX = x + dx;
            int newY = y + dy;

            if (gameField.getCellStatus(newY, newX) == CellStatus::Ship) {
                std::cout << "Был найден корабль" << std::endl;
                return false;
            }
        }
    }

    std::cout << "Не был найден корабль" << std::endl;
    return false;
}
