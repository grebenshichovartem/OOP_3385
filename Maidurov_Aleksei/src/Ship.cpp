//
// Created by MSI Catana GF66 on 13.10.2024.
//

#include <iostream>
#include "Ship.h"
#include "DebuggingException.h"

Ship::Ship(unsigned size) : death_status{false}, pos{0, 0}, orientation{ShipOrientation::Horizontal} {
    if (size < 1 || size > 4) {
        throw DebuggingException("Ship size must be between 1 and 4.");
    }
    this->size = size;
    segs = std::move(std::vector<Segment>(size));
}

bool Ship::wasItDeath() const { return death_status; }

bool Ship::isItDeath() const {
    if (death_status) { return death_status; }
    for (unsigned i = 0; i < size; i++) {
        if (segs[i].getStatus() != SegmentStatus::Destroyed) { return death_status; }
    }
    death_status = true;
    return death_status;
}

bool Ship::wasItDestroyedJustNow() const {
    bool old_status = death_status;
    bool new_status = isItDeath();
    return (new_status && (old_status != new_status));
}


void Ship::setOrientation(ShipOrientation orientation) {
    this->orientation = orientation;
}

void Ship::setPos(unsigned x, unsigned y) {
    pos[0] = x;
    pos[1] = y;
}

ShipOrientation Ship::getOrientation() const { return orientation; }

void Ship::printShipInfo() const {
    std::cout << "Ship on " << pos[0] << " " << pos[1] << " has the following characteristics:\n";
    std::cout << "size: " << size << '\n';
    std::cout << "orientation: " << (orientation == ShipOrientation::Horizontal ? "Horizontal\n" : "Vertical\n");
    std::cout << "is it death: " << (isItDeath() ? "yes\n" : "no\n") << '\n';
}

unsigned Ship::getX() const { return pos[0]; }

unsigned Ship::getY() const { return pos[1]; }

unsigned Ship::getSize() const { return size; }

Segment &Ship::operator[](unsigned index) {
    if (index > size - 1) {
        throw DebuggingException("Ship index out of range.");
    }
    return segs[index];
}
