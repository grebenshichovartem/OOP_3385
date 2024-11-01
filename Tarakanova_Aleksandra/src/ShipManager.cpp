#include "ShipManager.h"

ShipManager::ShipManager(const std::vector<std::pair<int, int>>& shipSpecifications) {  
    for (const auto& data : shipSpecifications) {
        int len = data.first; 
        int count = data.second;  
        for (int i = 0; i < count; i++) { 
            try {
                Ship* ship = new Ship(len,true);
                ships.push_back(ship); // По умолчанию вертикальные  
            } catch (std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }     
        }  
    }  
}

ShipManager::~ShipManager() {
    for (Ship* ship : ships) {
        delete ship;
    }
}

Ship* ShipManager::getShip(int index) const {  
    if (index >= 0 && index < ships.size()) {  
        return ships[index]; // Возвращает указатель на корабль  
    }  
    return nullptr; // Если индекс вне диапазона, возвращаем nullptr  
}  

int ShipManager::getShipsCount() const {  
    return ships.size(); // Возвращает количество кораблей  
}  

bool ShipManager::isDestroyed(){
    for(Ship* ship : ships){
        if(!ship->isDestroyed())
            return false;
    }
    return true;
}