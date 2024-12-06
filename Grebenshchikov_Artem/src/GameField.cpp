#include <iostream>
#include <memory>
#include "GameField.hpp"
#include "BattleshipException.h"



GameField::GameField(int height, int width) : width(width), height(height), field(height, std::vector<FieldCell*>(width)) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto* cell = new FieldCell();
            field[y][x] = cell;
        }
    }
}


GameField::GameField() = default;


bool GameField::checkCoordAttack(int y, int x) const {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return false;
    }
    return true;
}


void GameField::placeShip(Ship* ship, int y, int x, int isHorizontally) {
    ship->setHorizontally(isHorizontally > 0);
    for (int i = 0; i < ship->getLength(); i++) {
        int currentY = y + (ship->getHorizontally() ? 0 : i);
        int currentX = x + (ship->getHorizontally() ? i : 0);
        field[currentY][currentX]->setStatus(CellStatus::Ship);
        field[currentY][currentX]->setShip(ship);
        field[currentY][currentX]->setIndexSeg(i);
    }
}


bool GameField::attackCell(int y, int x) {
    try {
        if (!checkCoordAttack(y, x)) {
            throw OutOfBoundsAttackError();
        }
    } catch (const OutOfBoundsAttackError& e) {
        std::cout << e.what() << std::endl;
    }
    if (getCellStatus(y, x) == CellStatus::Ship) {
        return field[y][x]->getShip()->takeDamage(field[y][x]->getIndexSeg());
    }
    std::cout << "По этим координатам корабля нет" << std::endl;
    return false;

}

bool GameField::canPlaceShip(int y, int x, int length, bool isHorizontally) const {
    for (int i = 0; i < length; ++i) {
        int checkX = x + (isHorizontally ? i : 0);
        int checkY = y + (isHorizontally ? 0 : i);
        if ((checkX < 0) || (checkX >= getWidth()) || (checkY < 0) || (checkY >= getHeight())) {
            return false;
        }
    }
    int startX = x - 1;
    int endX = isHorizontally ? x + length : x + 1;
    int startY = y - 1;
    int endY = isHorizontally ? y + 1 : y + length;
    for (int dy = startY; dy <= endY; dy++) {
        for (int dx = startX; dx <= endX; dx++) {
            if (dy >= 0 && dx >= 0 && dy < getHeight() && dx < getWidth()) {
                if (getCellStatus(dy, dx) == CellStatus::Ship) {
                    return false;
                }
            }
        }
    }
    return true;
}


int GameField::getWidth() const {
    return width;
}


int GameField::getHeight() const {
    return height;
}


Ship* GameField::getShip(int y, int x) const {
    return field[y][x]->getShip();
}


CellStatus GameField::getCellStatus(int y, int x) const {
    return field[y][x]->getStatus();
}


int GameField::getCellIndex(int y, int x) const {
    return field[y][x]->getIndexSeg();
}


GameField::GameField(const GameField& other) = default;


GameField::GameField(GameField&& other) noexcept : width(other.width), height(other.height), field(std::move(other.field)) {}


GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        field = (other.field);
    }
    return *this;
}


GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        field = std::move(other.field);
    }
    return *this;
}


SegmentStatus GameField::getStatusShipCell(int y, int x) const {
    return field[y][x]->getShip()->getSegmentStatus(field[y][x]->getIndexSeg());
}


FieldCell* GameField::getFieldCell(int y, int x) const {
    return field[y][x];
}


GameField::~GameField() {
    for(const auto& y : field) {
        for (auto x : y) {
            delete x;
        }
    }
}