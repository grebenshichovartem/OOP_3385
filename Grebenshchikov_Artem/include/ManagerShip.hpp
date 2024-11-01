#ifndef MANAGERSHIP_HPP
#define MANAGERSHIP_HPP

#include <vector>
#include <memory>
#include "Ship.hpp"



class ManagerShip {
public:
    explicit ManagerShip(const std::vector<std::pair<int, int>>& lenAndCount);
    void registerShip(std::pair<int, int>);
    int getCountShip() const;
    Ship* getShip(int index);
    void deleteShip(int index);
    bool allShipDestroyed();
    ~ManagerShip();
private:
    std::vector<Ship*> ships;
};



#endif 