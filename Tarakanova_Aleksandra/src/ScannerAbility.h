#ifndef SCANNER_ABILITY_H
#define SCANNER_ABILITY_H

#include "Ability.h"

class Scanner : public Ability {
public:
    bool apply(GameStatus status) override;
    std::string toString() const override;
};

#endif