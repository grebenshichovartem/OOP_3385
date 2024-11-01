#ifndef DOUBLE_DAMAGE_ABILITY_H
#define DOUBLE_DAMAGE_ABILITY_H

#include "Ability.h"

class DoubleDamage : public Ability {
public:
    bool apply(GameStatus status) override;
    std::string toString() const override;
};
#endif 

