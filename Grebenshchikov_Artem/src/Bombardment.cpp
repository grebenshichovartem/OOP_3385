#include <iostream>
#include "Bombardment.h"
#include "random"



void Bombardment::printAbility() {
    std::cout << "Была выбрана способность: Обстрел" << std::endl;
}


bool Bombardment::use(GameField& gameField, ManagerShip& manager) {
    while (true) {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, manager.getCountShip() - 1);

        Ship *targetShip = manager.getShip(distribution(generator));
        std::uniform_int_distribution<int> distribution2(0, targetShip->getLength() - 1);
        int lenindex = distribution2(generator);
        if (targetShip->getSegmentStatus(lenindex) != SegmentStatus::Destroyed) {
            targetShip->takeDamage(lenindex);
            if (manager.allShipDestroyed()) {
                std::cout << "Все корабли уничтожены. Спасибо за игру!" << std::endl;
                exit(0);
            }
            return false;
        }
    }
}