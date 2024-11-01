#ifndef ABILITY_H
#define ABILITY_H

#include <vector>
#include <memory>
#include <random>
#include "GameStatus.h"

class Ability {
public:
    virtual ~Ability() {}
    virtual bool apply(GameStatus status) = 0;
    virtual std::string toString() const = 0;
};
#endif 
