#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <vector>
#include <memory>
#include <random>
#include "Ability.h" // Предполагается, что у вас есть базовый класс Ability
#include "GameStatus.h" // Предполагается, что у вас есть класс GameStatus

class AbilityManager {
public:
    AbilityManager();

    void applyFirstAvailableAbility(GameStatus& status);
    void addAbility();


private:
    void initializeAbilityPool();

    std::vector<std::unique_ptr<Ability>> abilities; // Способности игрока
    std::vector<std::unique_ptr<Ability>> abilityPool; // Пул способностей
    std::mt19937 rng; // Генератор случайных чисел
};

#endif // ABILITYMANAGER_H
