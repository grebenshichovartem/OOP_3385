#include "ShipManager.hpp"



ShipManager::ShipManager(const std::vector<std::pair<int, int>>& lensAndCounts) {
    for (const auto lensAndCount : lensAndCounts) {
        registerShip(lensAndCount);
    }
}


ShipManager::ShipManager()= default;


void ShipManager::registerShip(std::pair<int, int> lenAndCount) {
    int len = lenAndCount.first;
    int count = lenAndCount.second;
    for (int i = 0; i < count; i++) {
        Ship* ship = new Ship(len, true);
        ships.push_back(ship);
    }
}


ShipManager& ShipManager::operator=(ShipManager&& other) noexcept {
    if (this == &other) return *this; // Защита от самоприсваивания
    ships = std::move(other.ships);
    return *this;
}


ShipManager::ShipManager(ShipManager&& other) noexcept : ships(std::move(other.ships)) {}


Ship* ShipManager::getShip(int i) const{
    return ships[i];
}


void ShipManager::deleteShip(int i) {
    ships.erase(ships.begin() + i);
}


int ShipManager::getShipsCount() const {
    return (int)ships.size();
}


bool ShipManager::allShipDestroyed() {
    for (int i = 0; i < getShipsCount(); i++) {
        if (!ships[i]->isDestroyed()) {
            return false;
        }
    }
    return true;
}

ShipManager::~ShipManager(){
    for (auto x : ships)
        delete x;
}