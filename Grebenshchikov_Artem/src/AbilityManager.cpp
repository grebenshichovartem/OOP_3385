#include <random>
#include <algorithm>
#include <vector>
#include "AbilityManager.h"
#include "Bombardment.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "BattleshipException.h"



AbilityManager::AbilityManager() {
    abilities.emplace_back(std::make_unique<Bombardment>());
    abilities.emplace_back(std::make_unique<DoubleDamage>());
    abilities.emplace_back(std::make_unique<Scanner>());

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(abilities.begin(), abilities.end(), generator);
}




void AbilityManager::addAbility() {
    std::unique_ptr<Ability> bombardment = std::make_unique<Bombardment>();
    std::unique_ptr<Ability> doubleDamage = std::make_unique<DoubleDamage>();
    std::unique_ptr<Ability> scanner = std::make_unique<Scanner>();

    std::vector<std::unique_ptr<Ability>> randAbilities;
    randAbilities.push_back(std::move(bombardment));
    randAbilities.push_back(std::move(doubleDamage));
    randAbilities.push_back(std::move(scanner));

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, randAbilities.size() - 1);


    abilities.push_back(std::move(randAbilities[distribution(generator)]));
}


std::unique_ptr<Ability> AbilityManager::getAbility() {
    if (abilities.empty()) {
        throw NoAbilitiesError();
    }

    std::unique_ptr<Ability> ability = std::move(abilities.front());
    abilities.erase(abilities.begin());
    return ability;
}


