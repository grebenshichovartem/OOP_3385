#include <iostream>
#include "DoubleDamage.h"



void DoubleDamage::printAbility() {
    std::cout << "Была выбрана способность: Двойной урон" << '\n' << "Введите координаты" << std::endl;
}


bool DoubleDamage::use(GameField& gameField, ManagerShip& manager) {
    return true;
}