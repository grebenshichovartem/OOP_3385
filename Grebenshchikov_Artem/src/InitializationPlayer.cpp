#include "InitializationPlayer.h"
#include "InitializationEnemy.h"



InitializationPlayer::InitializationPlayer(Game& game) : game(game){}


void InitializationPlayer::handle(){
    initFieldPlayer();
    initShipManagerPlayer();
    placeShipPlayer();
    game.getGameEntities()->setGameFlags(std::make_shared<GameFlags>());
    game.getGameEntities()->setAbilityManager(std::make_shared<AbilityManager>(game.getGameEntities()->getFieldEnemy(),
                                                                              game.getGameEntities()->getShipManagerEnemy(), game.getGameEntities()->getManagerIO()));
    game.setState(std::make_unique<InitializationEnemy>(game));
}


void InitializationPlayer::initFieldPlayer() const {
    game.getGameEntities()->getManagerIO()->outputMassage("Введите размеры поля\n");
    std::pair<int, int> sizeField;
    while (true) {
        sizeField = game.getGameEntities()->getManagerIO()->inputPairInt();
        if (sizeField.first > 1 && sizeField.second > 1)
            break;
    }
    game.getGameEntities()->setFieldPlayer(std::make_shared<GameField>(sizeField.first, sizeField.second));
}


void InitializationPlayer::initShipManagerPlayer() const{
    std::cout << "Введите количество кораблей для соответствующей длины:" << std::endl;
    std::vector<std::pair<int, int>> lenAndCount(4);
    for (int i = 0; i < 4; i++) {
        lenAndCount[i].first = i + 1;
        std::cout << "Для длины " << i + 1 << ": ";
        lenAndCount[i].second = game.getGameEntities()->getManagerIO()->inputInt();
    }
    game.getGameEntities()->setShipManagerPlayer(std::make_shared<ShipManager>(lenAndCount));
}


void InitializationPlayer::placeShipPlayer() const {
    int isHoriz;
    for (int i = 0; i < game.getGameEntities()->getShipManagerPlayer()->getShipsCount(); i++) {
        std::cout << "Для расстановки кораблей на поле введите координаты и ориентацию корабля длины: "
                  << game.getGameEntities()->getShipManagerPlayer()->getShip(i)->getLength() << std::endl;
        std::pair<int, int> coordinates;
        int count = 0;
        int x,y;
        while (count < 5) {
            count++;
            coordinates = game.getGameEntities()->getManagerIO()->inputPairInt();
            x = coordinates.first;
            y = coordinates.second;
            isHoriz = game.getGameEntities()->getManagerIO()->inputInt();
            if (game.getGameEntities()->getFieldPlayer()->canPlaceShip(y, x, game.getGameEntities()->getShipManagerPlayer()->getShip(i)->getLength(), isHoriz > 0)) {
                break;
            } else {
                game.getGameEntities()->getManagerIO()->outputMassage("Невозможно поставить корабль данным образом\n");
            }
        }
        if (count != 5) {
            game.getGameEntities()->getFieldPlayer()->placeShip(game.getGameEntities()->getShipManagerPlayer()->getShip(i), y, x, isHoriz);
        } else {
            game.getGameEntities()->getManagerIO()->outputMassage("Не удалось поставить корабль\n");
            game.getGameEntities()->getShipManagerPlayer()->deleteShip(i);
            i--;
        }
    }
}


std::string InitializationPlayer::toString() {
    return "InitializationPlayer";
}