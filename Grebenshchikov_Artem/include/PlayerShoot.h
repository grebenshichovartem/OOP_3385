#ifndef OOP_PLAYER_SHOOT_H
#define OOP_PLAYER_SHOOT_H

#include "GameState.h"
#include "Game.h"


class PlayerShoot: public GameState{
private:
    Game& game;

public:
    explicit PlayerShoot(Game& game);
    void handle() override;
    std::string toString() override;

};


#endif
