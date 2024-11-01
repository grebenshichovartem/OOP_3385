//
// Created by MSI Catana GF66 on 13.10.2024.
//

#ifndef SHIP_H
#define SHIP_H
#include "Segment.h"
#include <vector>
#include <array>

enum class ShipOrientation {
    Horizontal, Vertical
};

class Ship {
private:
    unsigned size;
    mutable bool death_status;
    std::vector<Segment> segs;
    std::array<unsigned, 2> pos;
    ShipOrientation orientation;

public:
    explicit Ship(unsigned size);

    [[nodiscard]] bool wasItDeath() const;

    bool isItDeath() const; //also updates death_status

    [[nodiscard]] bool wasItDestroyedJustNow() const;

    void setOrientation(ShipOrientation orientation);

    void setPos(unsigned x, unsigned y);

    [[nodiscard]] ShipOrientation getOrientation() const;

    void printShipInfo() const;

    [[nodiscard]] unsigned getX() const;

    [[nodiscard]] unsigned getY() const;

    [[nodiscard]] unsigned getSize() const;

    Segment &operator[](unsigned index);
};

#endif //SHIP_H
