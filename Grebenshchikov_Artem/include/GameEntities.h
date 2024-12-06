#ifndef OOP_GAME_ENTITIES_H
#define OOP_GAME_ENTITIES_H

#include <memory>
#include <iostream>
#include "ManagerIO.h"
#include "ShipManager.hpp"
#include "GameField.hpp"
#include "AbilityManager.h"
#include "GameFlags.h"



class GameEntities {
private:
    std::shared_ptr<ManagerIO> managerIO;
    std::shared_ptr<GameFlags> gameFlags;
    std::shared_ptr<GameField> fieldPlayer;
    std::shared_ptr<GameField> fieldEnemy;
    std::shared_ptr<ShipManager> shipManagerPlayer;
    std::shared_ptr<ShipManager> shipManagerEnemy;
    std::shared_ptr<AbilityManager> abilityManager;

public:
    GameEntities();

    std::shared_ptr<ManagerIO> getManagerIO() const;
    void setManagerIO(const std::shared_ptr<ManagerIO>& mgrIO);

    std::shared_ptr<GameFlags> getGameFlags() const;
    void setGameFlags(const std::shared_ptr<GameFlags>& gameFlags);

    std::shared_ptr<GameField> getFieldPlayer() const;
    void setFieldPlayer(const std::shared_ptr<GameField>& fieldPlayer);

    std::shared_ptr<GameField> getFieldEnemy() const;
    void setFieldEnemy(const std::shared_ptr<GameField>& fieldEnemy);

    std::shared_ptr<ShipManager> getShipManagerPlayer() const;
    void setShipManagerPlayer(const std::shared_ptr<ShipManager>& shipManagerPlayer);

    std::shared_ptr<ShipManager> getShipManagerEnemy() const;
    void setShipManagerEnemy(const std::shared_ptr<ShipManager>& shipManagerEnemy);

    std::shared_ptr<AbilityManager> getAbilityManager() const;
    void setAbilityManager(const std::shared_ptr<AbilityManager>& abilityManager);

    friend std::istream& operator >> (std::istream& in, GameEntities& gameState);
    friend std::ostream& operator << (std::ostream& os, const GameEntities& gameState);
};


#endif