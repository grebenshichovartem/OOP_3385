#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "Ability.h"
#include "ManagerIO.h"



class DoubleDamage : public Ability {
private:
    std::weak_ptr<ManagerIO> weakManagerIO;

public:
    explicit DoubleDamage(const std::shared_ptr<ManagerIO>& managerIO);
    std::string toString() override;
    answerAbilities use() override;
};


#endif
