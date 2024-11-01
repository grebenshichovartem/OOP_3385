#include "BarrageAbility.h"
#include "CustomExceptions.h"

bool Barrage::apply(GameStatus status) {
    std::cout << "Обстрел активирован!" << std::endl;
    bool chek =true;
    Ship* ship;
    int randomSegment;
    std::mt19937 gen(std::random_device{}());
    while(chek){
        std::uniform_int_distribution<int> shipDist(0, status.manager->getShipsCount() - 1);
        ship = status.manager->getShip(shipDist(gen));
        if(! ship->isDestroyed())
            chek=false;
    }
    std::uniform_int_distribution<int> segmentDist(0, ship->getLength() - 1);
    while(!chek){
        randomSegment = segmentDist(gen);
        try {
            if(ship->getStatus(randomSegment) != SegmentStatus::Destroyed)
                chek=true;
            } catch (ShipManagerException& e) {
                std::cerr << e.what() << std::endl;
            }        
    }
    
    try {
        ship->shotSegment(randomSegment);
        } catch (ShipManagerException& e) {
            std::cerr << e.what() << std::endl;
        }

    if(ship->isDestroyed()){
                std::cout << "Корабль уничтожен!"<< std::endl;
                return true; 
            }
    return false;
}

std::string Barrage::toString() const {
    return "Barrage"; // Описание способности
}
