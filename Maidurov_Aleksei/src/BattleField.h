//
// Created by MSI Catana GF66 on 14.10.2024.
//

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "CellOfField.h"
#include "ShipManager.h"
#include <map>
#include <string>

enum class FieldStatus { EnemyField, PlayerField };

class BattleField {
private:
    unsigned width, height;
    FieldStatus status;
    std::map<std::array<unsigned, 2>, const Ship *> placed_ships;
    std::vector<std::vector<CellOfField> > field;

public:
    BattleField(unsigned width, unsigned height, FieldStatus status);

    BattleField(BattleField const &other);

    BattleField &operator=(const BattleField &other);

    BattleField(BattleField &&moved) noexcept;

    BattleField &operator=(BattleField &&moved) noexcept;

    void placeShip(Ship &ship, unsigned x, unsigned y, ShipOrientation orientation);

    void attackCell(unsigned x, unsigned y, int damage_value);

    [[nodiscard]] bool areAllShipsDestroyed() const;

    [[nodiscard]] bool wasAnyShipDestroyedJustNow(unsigned x, unsigned y) const;

    [[nodiscard]] unsigned getWidth() const;

    [[nodiscard]] unsigned getHeight() const;

    [[nodiscard]] std::string stringViewOfField() const;

    void printField() const;
};


#endif //BATTLEFIELD_H
