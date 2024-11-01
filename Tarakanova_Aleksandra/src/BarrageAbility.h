#ifndef BARRAGE_ABILITY_H
#define BARRAGE_ABILITY_H

#include "Ability.h"

class Barrage : public Ability {
public:
    bool apply(GameStatus status) override;
    std::string toString() const override;
};


#endif 