#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include "Ship.h"
#include <vector>

class ShipManager{
private:
    std::vector <Ship*> ships;
public:
    ShipManager(const std::vector<std::pair<int, int>>& shipSpecifications);
    ~ShipManager();

    int getShipsCount() const ;
    Ship* getShip(int index) const;
    bool isDestroyed();
};

#endif