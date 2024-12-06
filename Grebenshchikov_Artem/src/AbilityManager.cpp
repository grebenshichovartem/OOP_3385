#include <random>
#include <algorithm>
#include "memory"
#include "AbilityManager.h"
#include "Bombardment.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "BattleshipException.h"



AbilityManager::AbilityManager(const std::shared_ptr<GameField>& gameField, const std::shared_ptr<ShipManager>& managerShip, const std::shared_ptr<ManagerIO>& managerIO) {
    abilityPatterns.push_back(std::make_shared<Bombardment>(managerShip, managerIO));
    abilityPatterns.push_back(std::make_shared<DoubleDamage>(managerIO));
    abilityPatterns.push_back(std::make_shared<Scanner>(gameField, managerIO));

    abilities = abilityPatterns;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(abilities.begin(), abilities.end(), generator);
}


AbilityManager::AbilityManager() = default;


void AbilityManager::addAbility() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(abilityPatterns.size()) - 1);

    abilities.push_back(abilityPatterns[distribution(generator)]);
}


std::shared_ptr<Ability> AbilityManager::createAbility(const std::string& abilityName) {
    if (abilityName == "Bombardment"){
        return  abilityPatterns[0];
    } else if (abilityName == "DoubleDamage") {
        return abilityPatterns[1];
    } else if (abilityName == "Scanner") {
        return abilityPatterns[2];
    } else {
        std::shared_ptr<Ability> ptr = nullptr;
        return ptr;
    }
}


std::shared_ptr<Ability> AbilityManager::getAbility() {
    if (abilities.empty()) {
        throw NoAbilitiesError();
    } else {
        auto abilityPtr = abilities.front();
        abilities.erase(abilities.begin());
        return abilityPtr;
    }
}


void AbilityManager::setAbility(const std::shared_ptr<Ability>& ability) {
    abilities.push_back(ability);
}


std::shared_ptr<Ability> AbilityManager::getAbility(int index) const {
    return abilities[index];
}


int AbilityManager::getAbilityCount() const{
    return (int)abilities.size();
}


void AbilityManager::updateAbilityMembers(const std::shared_ptr<GameField>& gameField, const std::shared_ptr<ShipManager>& managerShip, const std::shared_ptr<ManagerIO>& managerIO) {
    abilityPatterns.clear();
    abilityPatterns.push_back(std::make_shared<Bombardment>(managerShip, managerIO));
    abilityPatterns.push_back(std::make_shared<DoubleDamage>(managerIO));
    abilityPatterns.push_back(std::make_shared<Scanner>(gameField, managerIO));
    for (auto & ability : abilities) {
        for (const auto& abilityPattern : abilityPatterns) {
            if (typeid(*ability) == typeid(*abilityPattern)) {
                ability = abilityPattern; // Заменяем указатель в векторе
                break; // Выход из внутреннего цикла, если замена произошла
            }
        }
    }

}