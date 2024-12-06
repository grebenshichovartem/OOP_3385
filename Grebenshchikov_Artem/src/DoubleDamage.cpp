#include <iostream>
#include "DoubleDamage.h"



DoubleDamage::DoubleDamage(const std::shared_ptr<ManagerIO>& managerIO) : weakManagerIO(managerIO){}


std::string DoubleDamage::toString() {
    return "DoubleDamage";
}


answerAbilities DoubleDamage::use() {
    auto managerIO = weakManagerIO.lock();
    managerIO->outputMassage("Была выбрана способность DoubleDamage\n");
    return answerAbilities::DoubleDamage;
}