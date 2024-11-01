//
// Created by MSI Catana GF66 on 13.10.2024.
//

#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <map>
#include "Ship.h"


class ShipManager {
private:
    unsigned number_of_ships;
    std::vector<Ship> ships;

public:
    ShipManager(unsigned size_of_vector, const std::vector<unsigned>  &sizes);

    Ship &getUnplacedShip(unsigned n);

    [[nodiscard]] unsigned getNumberOfShips() const;
};


#endif //SHIPMANAGER_H
