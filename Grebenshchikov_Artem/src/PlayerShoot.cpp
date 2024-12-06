#include "PlayerShoot.h"
#include "TurnEnemy.h"
#include "InitializationEnemy.h"



PlayerShoot::PlayerShoot(Game& game) : game(game){}


void PlayerShoot::handle() {
    game.getGameEntities()->getManagerIO()->outputMassage("Введите координаты для выстрела\n");
    game.getGameEntities()->getGameFlags()->setUseAbility(false);
    std::pair<int, int> coordinates;
    while (true) {
        coordinates = game.getGameEntities()->getManagerIO()->inputPairInt();
        if (coordinates.first > 0 || coordinates.first < game.getGameEntities()->getFieldEnemy()->getWidth() || coordinates.second > 0 || coordinates.second < game.getGameEntities()->getFieldEnemy()->getHeight())
            break;
    }

    if (game.getGameEntities()->getGameFlags()->getDoubleDamage()) {
        game.getGameEntities()->getGameFlags()->setDoubleDamage(false);
        if (game.getGameEntities()->getFieldEnemy()->attackCell(coordinates.second, coordinates.first)) {
            game.getGameEntities()->getManagerIO()->outputMassage("Добавлена новая способность\n");
            game.getGameEntities()->getAbilityManager()->addAbility();
        }
    }
    if (game.getGameEntities()->getFieldEnemy()->attackCell(coordinates.second, coordinates.first)) {
        game.getGameEntities()->getManagerIO()->outputMassage("Добавлена новая способность\n");
        game.getGameEntities()->getAbilityManager()->addAbility();
    }
    if (game.getGameEntities()->getShipManagerEnemy()->allShipDestroyed()) {
        game.getGameEntities()->getManagerIO()->outputMassage("Все корабли уничтожены! Победа в раунде за вами\nНачинается новый раунд!\n");
        game.setState(std::make_unique<InitializationEnemy>(game));
        return;
    }
    game.setState(std::make_unique<TurnEnemy>(game));
}


std::string PlayerShoot::toString() {
    return "PlayerShoot";
}