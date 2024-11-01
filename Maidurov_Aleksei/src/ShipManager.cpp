//
// Created by MSI Catana GF66 on 13.10.2024.
//

#include "ShipManager.h"
#include "DebuggingException.h"

ShipManager::ShipManager(unsigned size_of_vector, const std::vector<unsigned> &sizes) {
    if (size_of_vector != static_cast<unsigned>(sizes.size()) || size_of_vector == 0) {
        throw DebuggingException{"size_of_vector and its real size must match!"};
    }
    number_of_ships = size_of_vector;
    for (auto &size: sizes) {
        ships.emplace_back(size);
    }
}

Ship &ShipManager::getUnplacedShip(unsigned n) {
    if (n >= number_of_ships) { throw DebuggingException{"Ship index out of range"}; }
    return ships[n];
}

unsigned ShipManager::getNumberOfShips() const { return number_of_ships; }
