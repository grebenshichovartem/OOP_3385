#include <iostream>
#include "Ship.hpp"



Ship::Ship(int len, bool isHorizontally) : length(len), horizontally(isHorizontally), segments(len, SegmentStatus::Whole) {}


bool Ship::takeDamage(int indexSegment) {
    switch (segments[indexSegment]) {
        case SegmentStatus::Whole:
            segments[indexSegment] = SegmentStatus::Damaged;
            std::cout << "Сегмент корабля был поврежден" << std::endl;
            break;
        case SegmentStatus::Damaged:
            segments[indexSegment] = SegmentStatus::Destroyed;

            if (isDestroyed()) {
                std::cout << "Корабль уничтожен" << std::endl;
                return true;
            } else {
                std::cout << "Сегмент корабля был уничтожен" << std::endl;
            }
            break;
        case SegmentStatus::Destroyed:
            std::cout << "Этот сегмент корабля уже уничтожен" << std::endl;
            break;
    }
    return false;
}


SegmentStatus Ship::getSegmentStatus(int i) const {
    return segments[i];
}


void Ship::setSegmentStatus(int index, SegmentStatus stat) {
    segments[index] = stat;
}


bool Ship::isDestroyed() const {
    for (const auto &segment: segments)
        if (segment != SegmentStatus::Destroyed) {
            return false;
        }
    return true;
}



void Ship::setHorizontally(bool isHorizontally){
    horizontally = isHorizontally;
}


int Ship::getLength() const{
    return length;
}


bool Ship::getHorizontally() const{
    return horizontally;
}


Ship::~Ship() = default;