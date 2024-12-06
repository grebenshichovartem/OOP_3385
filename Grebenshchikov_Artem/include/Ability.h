#ifndef ABILITY_H
#define ABILITY_H

#include <string>



enum class answerAbilities{
    BombardmentSuccess,
    BombardmentDestroyedShip,
    ScannerFoundShip,
    DoubleDamage,
    ScannerNotFoundShip
};


class Ability {
public:
    virtual ~Ability() = default;
    virtual std::string toString() = 0;
    virtual answerAbilities use() = 0;
};


#endif
