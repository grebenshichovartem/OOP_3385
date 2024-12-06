#ifndef MANAGERSHIP_HPP
#define MANAGERSHIP_HPP

#include <vector>
#include <memory>
#include "Ship.hpp"



class ShipManager {
public:
    explicit ShipManager(const std::vector<std::pair<int, int>>& lenAndCount);
    ShipManager();
    void registerShip(std::pair<int, int>);
    int getShipsCount() const;
    Ship* getShip(int index) const;
    void deleteShip(int i);
    bool allShipDestroyed();

    ShipManager& operator=(ShipManager&& other) noexcept;
    ShipManager(ShipManager&& other) noexcept;
    ~ShipManager();
private:
    std::vector<Ship*> ships;
};



#endif 