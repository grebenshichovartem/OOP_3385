#ifndef OOP_GAME_STATE_H
#define OOP_GAME_STATE_H

#include "GameEntities.h"
#include "Game.h"

class Game;



class GameState{
public:
    virtual ~GameState() = default;
    virtual void handle() = 0;
    virtual std::string toString() = 0;
};


#endif