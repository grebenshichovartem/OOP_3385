//
// Created by MSI Catana GF66 on 14.10.2024.
//

#include "BattleField.h"

#include <algorithm>
#include <ranges>
#include <iostream>

#include "DebuggingException.h"

BattleField::BattleField(unsigned width, unsigned height, FieldStatus status) {
    this->width = width;
    this->height = height;
    this->status = status;
    CellStatus cell_status = (status == FieldStatus::EnemyField ? CellStatus::Hidden : CellStatus::Empty);
    this->field = std::vector<std::vector<CellOfField> >
            (width, std::vector<CellOfField>(height, CellOfField{cell_status}));
}

BattleField::BattleField(BattleField const &other) {
    status = other.status;
    width = other.width;
    height = other.height;
    field = other.field;
    placed_ships = other.placed_ships;
}

BattleField &BattleField::operator=(const BattleField &other) {
    if (this != &other) {
        status = other.status;
        width = other.width;
        height = other.height;
        field = other.field;
        placed_ships = other.placed_ships;
    }
    return *this;
}

BattleField::BattleField(BattleField &&moved) noexcept {
    status = moved.status;
    width = moved.width;
    height = moved.height;
    field = std::move(moved.field);
    placed_ships = std::move(moved.placed_ships);
}

BattleField &BattleField::operator=(BattleField &&moved) noexcept {
    if (this != &moved) {
        status = moved.status;
        width = moved.width;
        height = moved.height;
        field = std::move(moved.field);
        placed_ships = std::move(moved.placed_ships);
    }
    return *this;
}

void BattleField::placeShip(Ship &ship, unsigned x, unsigned y, ShipOrientation orientation) {
    ship.setPos(x, y);
    ship.setOrientation(orientation);

    unsigned dx{1}, dy{0};
    if (orientation == ShipOrientation::Vertical) { std::swap(dx, dy); }
    if (y + (ship.getSize() - 1) * dy >= height || x + (ship.getSize() - 1) * dx >= width) {
        throw DebuggingException{"Going beyond the boundaries of the field when trying to put the ship!"};
    }
    for (unsigned i = 0; i < ship.getSize(); i++) {
        if (field[y + i * dy][x + i * dx].isNearOfShip()) {
            throw DebuggingException{"Ships cannot intersect or touch each other!"};
        } else {
            Segment *seg_ptr = &(ship[i]);
            field[y + i * dy][x + i * dx].setSegment(seg_ptr);
            if (status == FieldStatus::PlayerField) {
                field[y + i * dy][x + i * dx].setStatus(CellStatus::Occupied);
            }
        }
    }

    int size_x = ship.getSize() + 2;
    int size_y = 3;
    if (orientation == ShipOrientation::Vertical) { std::swap(size_x, size_y); }
    int int_x{static_cast<int>(x)}, int_y{static_cast<int>(y)};
    for (int i = int_y - 1; i < int_y - 1 + size_y; i++) {
        for (int j = int_x - 1; j < int_x - 1 + size_x; j++) {
            if (i < static_cast<int>(height) && j < static_cast<int>(width) && i >= 0 && j >= 0) {
                field[i][j].shipIsNear();
            }
        }
    }

    placed_ships[{x, y}] = &ship;
}

void BattleField::attackCell(unsigned x, unsigned y, int damage_value) {
    if (x >= width || y >= height) {
        throw DebuggingException{"Cell out of bounds"};
    }
    if (status == FieldStatus::EnemyField) {
        if (field[y][x].getSegment() == nullptr) {
            field[y][x].setStatus(CellStatus::Empty);
            std::cout << "Miss\n";
        } else {
            field[y][x].setStatus(CellStatus::Occupied);
            (field[y][x].getSegment())->takeDamage(damage_value);
            std::cout << "You dealed " << damage_value << " damage\n";
        }
    } else {
        if (field[y][x].getStatus() == CellStatus::Occupied) {
            (field[y][x].getSegment())->takeDamage(damage_value);
            std::cout << "Enemy dealed you " << damage_value << " damage at " << x << ", " << y << "\n";
        } else {
            std::cout << "Enemy missed at " << x << ", " << y << "\n";
        }
    }
}

bool BattleField::areAllShipsDestroyed() const {
    return std::ranges::all_of(placed_ships, [](const std::pair<std::array<unsigned, 2>, const Ship *> &pair) {
        return pair.second->isItDeath();
    });
}

bool BattleField::wasAnyShipDestroyedJustNow(unsigned x, unsigned y) const {
    if (x >= width || y >= height) {
        throw DebuggingException{"Cell out of bounds"};
    }

    bool accum{};
    for (unsigned i = 0; i < 4; i++) {
        if (placed_ships.contains({x - i, y})) {
            accum |= placed_ships.at({x - i, y})->wasItDestroyedJustNow();
        }
        if (placed_ships.contains({x, y - i})) {
            accum |= placed_ships.at({x, y - i})->wasItDestroyedJustNow();;
        }
    }
    return accum;
}

unsigned BattleField::getHeight() const { return height; }

unsigned BattleField::getWidth() const { return width; }

std::string BattleField::stringViewOfField() const {
    std::string string{};
    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            string += "| ";
            char symb;
            CellStatus cell_status = field[i][j].getStatus();
            if (cell_status == CellStatus::Hidden) {
                symb = ' ';
            } else if (cell_status == CellStatus::Empty) {
                symb = (status == FieldStatus::EnemyField ? 'o' : ' ');
            } else {
                SegmentStatus segment_status = field[i][j].getSegment()->getStatus();
                if (segment_status == SegmentStatus::Unharmed) {
                    symb = '2';
                } else if (segment_status == SegmentStatus::Harmed) {
                    symb = '1';
                } else {
                    symb = '#';
                }
            }
            string += symb;
            string += ' ';
        }
        string += "|\n";
    }
    return string;
}

void BattleField::printField() const {
    unsigned chars_in_row = 4 * width + 2; // "| c " * width + "|\n"
    std::string string_of_letters = "    ";
    for (char i = 'A'; i < ('A' + static_cast<char>(width)); i++) {
        string_of_letters += "  ";
        string_of_letters += i;
        string_of_letters += " ";
    }
    string_of_letters += " \n";
    std::cout << string_of_letters;
    std::string orig_string = stringViewOfField();
    for (unsigned index = 0, num = 1; num <= height; index += chars_in_row, num++) {
        std::cout << " " << std::to_string(num) << (num < 10 ? "  " : " ");
        std::cout << orig_string.substr(index, chars_in_row);
    }
}