#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "FileWrapper.h"


class GameState;


class Game {
public:
    Game();
    void setState(std::unique_ptr<GameState> newState);
    std::shared_ptr<GameEntities> getGameEntities() const;

    int getInt();
    void defineState(const std::string& state);

    void startGame();
    void playerShoot();
    void useAbility();
    void turnEnemy();
    void runGameLoop();

    void load();
    void save();

private:
    std::unique_ptr<FileWrapper> fileWrapper;
    std::shared_ptr<GameEntities> entities;
    std::unique_ptr<GameState> currentState;
};


#endif