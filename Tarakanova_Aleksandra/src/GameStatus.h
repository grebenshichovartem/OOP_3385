#ifndef GAME_STATUS_H
#define GAME_STATUS_H

#include "GameField.h"

class GameStatus{
public:
    GameField* fieldPlayer;
    ShipManager* manager;
  
    GameStatus(GameField* fieldPlayer, ShipManager* manager); 
};

#endif