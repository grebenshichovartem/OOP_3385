#include "ManagerShip.hpp"



ManagerShip::ManagerShip(const std::vector<std::pair<int, int>>& lensAndCounts) {
    for (const auto lensAndCount : lensAndCounts) {
        registerShip(lensAndCount);
    }
}


void ManagerShip::registerShip(std::pair<int, int> lenAndCount) {
    int len = lenAndCount.first;
    int count = lenAndCount.second;
    for (int i = 0; i < count; i++) {
        Ship* ship = new Ship(len, true);
        ships.push_back(ship);
    }
}


Ship* ManagerShip::getShip(int i) {
    return ships[i];
}


int ManagerShip::getCountShip() const {
    return (int)ships.size();
}


bool ManagerShip::allShipDestroyed() {
    for (int i = 0; i < getCountShip(); i++) {
        if (!ships[i]->isDestroyed()) {
            return false;
        }
    }
    return true;
}

ManagerShip::~ManagerShip(){
    for (auto x : ships)
        delete x;
}