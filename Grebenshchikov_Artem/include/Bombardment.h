#ifndef BOMBARDMENT_H
#define BOMBARDMENT_H

#include "Ability.h"



class Bombardment : public Ability {
public:
    bool use(GameField& gameField, ManagerShip& manager) override;
    void printAbility() override;
};


#endif
