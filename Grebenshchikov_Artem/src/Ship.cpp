#include <iostream>
#include "Ship.hpp"



Ship::Ship(int len, bool ishorizontally) : length(len), horizontally(ishorizontally), segments(len, SegmentStatus::Whole) {}


bool Ship::takeDamage(int indexSegment) {
    switch (segments[indexSegment]) {
        case SegmentStatus::Whole:
            segments[indexSegment] = SegmentStatus::Damaged;
            std::cout << "Сегмент коробля был поврежден" << std::endl;
            break;
        case SegmentStatus::Damaged:
            segments[indexSegment] = SegmentStatus::Destroyed;
            std::cout << "Сегмент коробля был уничтожен" << std::endl;
            if (isDestroyed()) {
                std::cout << "Корабль уничтожен" << std::endl;
                return true;
            }
            break;
        case SegmentStatus::Destroyed:
            std::cout << "Этот сегмент коробля уже уничтожен" << std::endl;
            break;
    }
    return false;
}


SegmentStatus Ship::getSegmentStatus(int i) {
    return segments[i];
}


bool Ship::isDestroyed() const {
    for (const auto &segment: segments)
        if (segment != SegmentStatus::Destroyed) {
            return false;
        }
    return true;
}



void Ship::setHorizontally(bool isHorisontally){
    horizontally = isHorisontally;
}


int Ship::getLength() const{
    return length;
}


bool Ship::getHorizontally() const{
    return horizontally;
}


Ship::~Ship() = default;