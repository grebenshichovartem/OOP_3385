#include "GameFlags.h"



GameFlags::GameFlags() : doubleDamage(false), useAbility(false), loadAndNewGame(false){}


void GameFlags::setDoubleDamage(bool flag) {
    doubleDamage = flag;
}


bool GameFlags::getDoubleDamage() const {
    return doubleDamage;
}


void GameFlags::setUseAbility(bool flag) {
    useAbility = flag;
}


bool GameFlags::getUseAbility() const {
    return useAbility;
}


void GameFlags::setLoadAndNewGame(bool flag) {
    loadAndNewGame = flag;
}


bool GameFlags::getLoadAndNewGame() const {
    return loadAndNewGame;
}
