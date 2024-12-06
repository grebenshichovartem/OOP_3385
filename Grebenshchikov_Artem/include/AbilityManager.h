#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include "Ability.h"
#include "memory"
#include "vector"
#include "GameField.hpp"
#include "ShipManager.hpp"
#include "ManagerIO.h"


class AbilityManager {
public:
    AbilityManager(const std::shared_ptr<GameField>& gameField, const std::shared_ptr<ShipManager>& managerShip, const std::shared_ptr<ManagerIO>& managerIO);
    AbilityManager();
    void addAbility();
    std::shared_ptr<Ability> createAbility(const std::string& abilityName);
    void setAbility(const std::shared_ptr<Ability>& ability);
    std::shared_ptr<Ability> getAbility();
    std::shared_ptr<Ability> getAbility(int index) const;
    int getAbilityCount() const;
    void updateAbilityMembers(const std::shared_ptr<GameField>& gameField, const std::shared_ptr<ShipManager>& managerShip, const std::shared_ptr<ManagerIO>& managerIO);

private:
    std::vector<std::shared_ptr<Ability>> abilityPatterns;
    std::vector<std::shared_ptr<Ability>> abilities;
};


#endif