#include "AbilityManager.h"
#include "BarrageAbility.h"
#include "DoubleDamageAbility.h"
#include "ScannerAbility.h"
#include "CustomExceptions.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

AbilityManager::AbilityManager() 
    : rng(std::random_device{}()) {
    abilities.push_back(std::make_unique<DoubleDamage>());
    abilities.push_back(std::make_unique<Scanner>());
    abilities.push_back(std::make_unique<Barrage>());

    std::shuffle(abilities.begin(), abilities.end(), rng);

}

void AbilityManager::initializeAbilityPool() {
    
    // Инициализация пула способностей (по одной каждого вида)
    abilityPool.push_back(std::make_unique<DoubleDamage>());
    abilityPool.push_back(std::make_unique<Scanner>());
    abilityPool.push_back(std::make_unique<Barrage>());
}

void AbilityManager::applyFirstAvailableAbility(GameStatus& status) {
    if (!abilities.empty()) {
        auto& ability = abilities.front(); // Получаем первую способность
        if (ability){
            try {
                if(ability->apply(status)) 
                    addAbility();
            } catch (AbilityManagerException& e) {
                std::cerr << e.what() << std::endl;
            }
            // Удаляем способность из списка
            abilities.erase(abilities.begin());
        } else {
            throw AbilityManagerException("Невозможно применить способность");
        }
    } else {
        throw AbilityManagerException("У игрока нет доступных способностей");
    }
}

void AbilityManager::addAbility() {
    initializeAbilityPool();
    if (!abilityPool.empty()) {
        int index = std::uniform_int_distribution<>(0, abilityPool.size() - 1)(rng);
        abilities.push_back(std::move(abilityPool[index])); 
        std::cout << "Добавлена способность: " << abilities.back()->toString() << std::endl; // Выводим информацию о способности
        abilityPool.clear();
    } else {
        throw AbilityManagerException("Пул способностей пуст");
    }
}