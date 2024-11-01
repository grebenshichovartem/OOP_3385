#ifndef ABILITY_H
#define ABILITY_H


#include "GameField.hpp"
#include "ManagerShip.hpp"



class Ability {
public:
    virtual ~Ability() = default;
    virtual void printAbility() = 0;
    virtual bool use(GameField& gameField, ManagerShip& manager) = 0;
};


#endif
