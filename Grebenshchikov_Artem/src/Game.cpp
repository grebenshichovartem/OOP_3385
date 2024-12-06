#include "Game.h"
#include <utility>
#include <map>
#include "PlayerShoot.h"
#include "UseAbility.h"
#include "TurnEnemy.h"
#include "InitializationPlayer.h"
#include "BattleshipException.h"



Game::Game() {
    entities = std::make_shared<GameEntities>();
}


void Game::setState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
    currentState->handle();
}


std::shared_ptr<GameEntities> Game::getGameEntities() const{
    return entities;
}


void Game::playerShoot() {
    if (entities->getGameFlags()->getLoadAndNewGame()) {
        setState(std::make_unique<PlayerShoot>(*this));
    } else {
        entities->getManagerIO()->outputMassage("Игровые сущности еще не инициализированы.\nЧтобы иметь возможность "
                                           "выполнить какие-либо игровые действия,\nнужно сохраниться или загрузить сохраненную игру\n");
    }
}


void Game::useAbility() {
    if (entities->getGameFlags()->getLoadAndNewGame()) {
        setState(std::make_unique<UseAbility>(*this));
    } else {
        entities->getManagerIO()->outputMassage("Игровые сущности еще не инициализированы.\nЧтобы иметь возможность "
                                           "выполнить какие-либо игровые действия,\nнужно сохраниться или загрузить сохраненную игру\n");
    }
}


void Game::turnEnemy() {
    if (entities->getGameFlags()->getLoadAndNewGame()) {
        setState(std::make_unique<TurnEnemy>(*this));
    } else {
        entities->getManagerIO()->outputMassage("Игровые сущности еще не инициализированы.\nЧтобы иметь возможность "
                                           "выполнить какие-либо игровые действия,\nнужно сохраниться или загрузить сохраненную игру\n");
    }
}


void Game::startGame() {
    setState(std::make_unique<InitializationPlayer>(*this));
}


void Game::load() {
    try {
        std::string newState;
        fileWrapper = std::make_unique<FileWrapper>("save.txt");
        fileWrapper->read(newState, entities);
        defineState(newState);
        entities->getGameFlags()->setLoadAndNewGame(true);
    } catch (const FileException& e) {
        std::cerr << "File error: " << e.what() << std::endl;
    } catch (const LoadInFileException& error) {}
}


void Game::save() {
    if (entities->getGameFlags()->getLoadAndNewGame()) {
        try {
            fileWrapper = std::make_unique<FileWrapper>("save.txt");
            fileWrapper->write(currentState->toString(), entities);
        } catch (const FileException& e) {
            std::cerr << "File error: " << e.what() << std::endl;
        } catch (const LoadInFileException &error) {}
    } else {
        entities->getManagerIO()->outputMassage("Игровые сущности еще не инициализированы.\nЧтобы иметь возможность "
                                           "выполнить какие-либо игровые действия,\nнужно сохраниться или загрузить сохраненную игру\n");
    }
}


void Game::runGameLoop() {
    while (true) {
        entities->getManagerIO()->outputMassage("Выберете одно из следующих действий:\n");
        entities->getManagerIO()->outputMassage(" n - Новая игра\n ` - Загрузить игру\n ^ - Сохранить игру\n");
        entities->getManagerIO()->outputMassage(" p - Вывод вашего поля\n o - Вывод поля врага\n s - Выстрел игрока\n");
        entities->getManagerIO()->outputMassage(" a - Использование способности\n e - Выстрел врага\n q - Выйти из игры\n");
        char command = entities->getManagerIO()->inputCommand();

        // Обработка команд
        switch (command) {
            case 'n':
                startGame();  // Инициализация новой игры
                break;
            case '`':
                load();
                break;
            case '^':
                save();
                break;
            case 'p':
                if (entities->getGameFlags()->getLoadAndNewGame()) {
                    entities->getManagerIO()->printField(entities->getFieldPlayer());
                } else {
                    entities->getManagerIO()->outputMassage("Игровые сущности еще не инициализированы.\nЧтобы иметь возможность "
                                                       "выполнить какие-либо игровые действия,\nнужно сохраниться или загрузить сохраненную игру\n");
                }
                break;
            case 'o':
                if (entities->getGameFlags()->getLoadAndNewGame()) {
                    entities->getManagerIO()->printField(entities->getFieldEnemy());
                } else {
                    entities->getManagerIO()->outputMassage("Игровые сущности еще не инициализированы.\nЧтобы иметь возможность "
                                                       "выполнить какие-либо игровые действия,\nнужно сохраниться или загрузить сохраненную игру\n");
                }
                break;
            case 's':
                playerShoot();
                break;
            case 'a':
                if (entities->getGameFlags()->getUseAbility())
                    entities->getManagerIO()->outputMassage("В этом ходу уже была использована способность\n");
                else
                    useAbility();
                break;
            case 'e':
                turnEnemy();
                break;
            case 'q':
                return;
            default:
                entities->getManagerIO()->outputMassage("Неверная команда\n");
                break;
        }
    }
}


int Game::getInt() {
    std::string input = entities->getManagerIO()->inputString();
    if (input == "l") {
        load();
        return -1;
    } else if (input == "s") {
        save();
        return getInt();
    } else {
        try {
            int x = std::stoi(input); // Преобразование в int, если возможно
            return x;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: введено недопустимое значение." << std::endl;
        }
    }
    return getInt();
}


void Game::defineState(const std::string& stateName) {
    if (stateName == "InitializationPlayer")
        setState(std::make_unique<InitializationPlayer>(*this));
    else if (stateName == "PlayerShoot")
        setState(std::make_unique<PlayerShoot>(*this));
    else if (stateName == "InitializationEnemy") {
        // Игнорируем состояние InitializationEnemy
    } else if (stateName == "TurnEnemy")
        setState(std::make_unique<TurnEnemy>(*this));
    else if (stateName == "UseAbility")
        setState(std::make_unique<UseAbility>(*this));
    else
        throw std::runtime_error("Неверное состояние");
}
