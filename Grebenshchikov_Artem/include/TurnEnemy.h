#ifndef OOP_TURN_ENEMY_H
#define OOP_TURN_ENEMY_H

#include "GameState.h"
#include "Game.h"



class TurnEnemy : public GameState{
private:
    Game& game;

public:
    explicit TurnEnemy(Game& game);
    void handle() override;
    std::string toString() override;
};


#endif
