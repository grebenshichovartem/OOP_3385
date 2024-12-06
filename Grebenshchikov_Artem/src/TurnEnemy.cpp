#include "TurnEnemy.h"
#include <random>



TurnEnemy::TurnEnemy(Game& game) : game(game){}


void TurnEnemy::handle() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distributionX(0, game.getGameEntities()->getFieldPlayer()->getWidth() - 1);
    int x = distributionX(generator);
    std::uniform_int_distribution<int> distributionY(0, game.getGameEntities()->getFieldPlayer()->getHeight() - 1);
    int y = distributionY(generator);
    if(game.getGameEntities()->getFieldPlayer()->attackCell(y, x)){
        if(game.getGameEntities()->getShipManagerPlayer()->allShipDestroyed()){
            game.getGameEntities()->getGameFlags()->setLoadAndNewGame(false);
            game.getGameEntities()->getManagerIO()->outputMassage("К сожалению вы проиграли! Хотите начать новую игру? Тогда нажмите n, иначе ` для загрузки сохраненной игры\n");
        }
    }
}


std::string TurnEnemy::toString() {
    return "TurnEnemy";
}