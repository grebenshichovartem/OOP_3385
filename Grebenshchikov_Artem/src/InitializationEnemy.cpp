#include "InitializationEnemy.h"
#include <random>



InitializationEnemy::InitializationEnemy(Game& game) : game(game){}


void InitializationEnemy::handle() {
    initFieldEnemy();
    initShipManagerEnemy();
    placeShipEnemy();
    game.getGameEntities()->getGameFlags()->setLoadAndNewGame(true);
}


void InitializationEnemy::initFieldEnemy() const {
    game.getGameEntities()->setFieldEnemy(std::make_shared<GameField>(game.getGameEntities()->getFieldPlayer()->getHeight(),
                                                                     game.getGameEntities()->getFieldPlayer()->getWidth()));
}


void InitializationEnemy::initShipManagerEnemy() const {
    game.getGameEntities()->setShipManagerEnemy(std::make_shared<ShipManager>());
    for (int i = 0; i < game.getGameEntities()->getShipManagerPlayer()->getShipsCount(); i++) {
        game.getGameEntities()->getShipManagerEnemy()->registerShip(std::make_pair<int, int>(game.getGameEntities()->getShipManagerPlayer()->getShip(i)->getLength(), 1));
    }
}


void InitializationEnemy::placeShipEnemy(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distributionOrient(0, 1);
    std::uniform_int_distribution<int> distributionX(0, game.getGameEntities()->getFieldEnemy()->getWidth() - 1);
    std::uniform_int_distribution<int> distributionY(0, game.getGameEntities()->getFieldEnemy()->getHeight() - 1);

    for (int i = 0; i < game.getGameEntities()->getShipManagerEnemy()->getShipsCount(); i++) {
        int x, y, orient;
        int count = 0;
        while (count < 10000) {
            count++;
            x = distributionX(generator);
            y = distributionY(generator);
            orient = distributionOrient(generator);
            if (game.getGameEntities()->getFieldEnemy()->canPlaceShip(y, x, game.getGameEntities()->getShipManagerEnemy()->getShip(i)->getLength(), orient)) {
                break;
            }
        }
        if (count != 10000)
            game.getGameEntities()->getFieldEnemy()->placeShip(game.getGameEntities()->getShipManagerEnemy()->getShip(i), y, x, orient);
        else {
            game.getGameEntities()->getShipManagerEnemy()->deleteShip(i);
            i--;
        }
    }
    game.getGameEntities()->getAbilityManager()->updateAbilityMembers(game.getGameEntities()->getFieldEnemy(),
                                                                 game.getGameEntities()->getShipManagerEnemy(), game.getGameEntities()->getManagerIO());
}


std::string InitializationEnemy::toString() {
    return "InitializationEnemy";
}