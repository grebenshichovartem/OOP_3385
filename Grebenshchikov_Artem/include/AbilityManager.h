#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include "Ability.h"
#include "memory"
#include "vector"



class AbilityManager {
private:
    std::vector<std::unique_ptr<Ability>> abilities;
public:
    AbilityManager();
    void addAbility();
    std::unique_ptr<Ability> getAbility();
};


#endif