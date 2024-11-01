#ifndef DOUBLEDAMAGE_H
#define DOUBLEDAMAGE_H

#include "Ability.h"



class DoubleDamage : public Ability {
public:
    void printAbility() override;
    bool use(GameField& gameField, ManagerShip& manager) override;
};


#endif
