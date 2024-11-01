#include "Ship.h"
#include "CustomExceptions.h"

Ship::Ship (int len, bool Vertical) : len(len), vertical(Vertical){
    if(len < 1 || len > 4){
        throw ShipManagerException("Невозможная длина");
    }
    segments = new ShipSegment[len];
}

Ship::~Ship(){
    delete[] segments;
}

void Ship::shotSegment(int index){
    if(index<0 || index>len)
        throw ShipManagerException("Некорректный индекс");
    segments[index].shot();
}

SegmentStatus Ship::getStatus(int index) const {
    if(index<0 || index>len)
        throw ShipManagerException("Некорректный индекс");
    return segments[index].getStatus();
}

int Ship::getLength() const {
    return len;
}

void Ship::setVertical(bool Vertical){
    vertical=Vertical;
}

bool Ship::getOrientation() const {
    return vertical;
}

bool Ship::isDestroyed() const {
    for (int i = 0; i < len; i++) {
        if (segments[i].getStatus() != SegmentStatus::Destroyed) {
            return false;
        }
    }
    return true;
}