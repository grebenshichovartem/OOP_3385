#ifndef SCANNER_H
#define SCANNER_H

#include "Ability.h"



class Scanner : public Ability {
public:
    void printAbility() override;
    bool use(GameField& gameField, ManagerShip& manager) override;
};


#endif
