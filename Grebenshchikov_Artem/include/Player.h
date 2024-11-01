#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "GameField.hpp"
#include "ManagerShip.hpp"
#include "AbilityManager.h"



class Player {
private:
    GameField gameField;
    ManagerShip managerShip;
    AbilityManager abilityManager;
    ManagerShip initializeManagerShip();
    GameField initializeGameField();
    void placeShips();
public:
    Player();
    void printField() const;
    void movePlayer();
};


#endif
