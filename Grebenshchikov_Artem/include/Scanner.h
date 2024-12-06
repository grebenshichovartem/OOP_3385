#ifndef SCANNER_H
#define SCANNER_H

#include "Ability.h"
#include "GameField.hpp"
#include "ManagerIO.h"



class Scanner : public Ability {
    std::weak_ptr<GameField> weakGameField;
    std::weak_ptr<ManagerIO> weakManagerIO;
    int x, y;
public:
    explicit Scanner(const std::shared_ptr<GameField>& gameField, const std::shared_ptr<ManagerIO>& managerIO);
    std::string toString() override;
    answerAbilities use() override;
};


#endif
