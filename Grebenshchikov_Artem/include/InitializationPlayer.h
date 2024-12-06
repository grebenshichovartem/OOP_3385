#ifndef OOP_INITIALIZATION_GAME_H
#define OOP_INITIALIZATION_GAME_H

#include "GameState.h"



class InitializationPlayer : public GameState{
private:
    Game& game;
    void initFieldPlayer() const;
    void initShipManagerPlayer() const;
    void placeShipPlayer() const;

public:
    explicit InitializationPlayer(Game& game);
    void handle() override;
    std::string toString() override;
};


#endif
