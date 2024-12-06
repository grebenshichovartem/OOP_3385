#ifndef BOMBARDMENT_H
#define BOMBARDMENT_H

#include "Ability.h"
#include "ShipManager.hpp"
#include "ManagerIO.h"



class Bombardment : public Ability {
    std::weak_ptr<ShipManager> weakShipManager;
    std::weak_ptr<ManagerIO> weakManagerIO;
public:
    explicit Bombardment(const std::shared_ptr<ShipManager>& shipManager, const std::shared_ptr<ManagerIO>& managerIO);
    std::string toString() override;
    answerAbilities use() override;
};


#endif
