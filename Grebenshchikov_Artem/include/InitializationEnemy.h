#ifndef OOP_INITIALIZATION_ENEMY_H
#define OOP_INITIALIZATION_ENEMY_H

#include "GameState.h"



class InitializationEnemy : public  GameState{
private:
    Game& game;
    void initFieldEnemy() const;
    void initShipManagerEnemy() const;
    void placeShipEnemy();

public:
    explicit InitializationEnemy(Game& game);
    void handle() override;
    std::string toString() override;
};

#endif
