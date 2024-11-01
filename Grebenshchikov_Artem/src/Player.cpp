#include "Player.h"
#include "BattleshipException.h"
#include "SafeInput.h"


Player::Player(): gameField(initializeGameField()), managerShip(initializeManagerShip()) {
    placeShips();
}


void Player::printField() const {
    for (int y = 0; y < gameField.getHeight(); y++) {
        for (int x = 0; x < gameField.getWidth(); x++) {
            if (gameField.getCellStatus(y, x) == CellStatus::Empty) {
                std::cout << '[' << ' ' << ']';
            } else if (gameField.getStatusShipCell(y, x) == SegmentStatus::Damaged) {
                std::cout << '[' << '&' << ']';
            } else if (gameField.getStatusShipCell(y, x) == SegmentStatus::Destroyed) {
                std::cout << '[' << 'x' << ']';
            } else {
                std::cout << '[' << gameField.getCellIndex(y, x) << ']';
            }
        }
        std::cout << std::endl;
    }
}


void Player::movePlayer() {
    int x, y;
    bool flagDoubleDamage = false;
    while (true) {
        std::cout << "\nВведите -1, если хотите воспользоваться способностью \n"
                     "Введите -2, если хотите выйти из игры \n"
                     "Иначе введите координаты для выстрела" << std::endl;
        x = safeInput();
        if (x == -3) {
            printField();
            std::cout << "Можете продолжить ввод" << std::endl;
            x = safeInput();
        }
        if (x == -1) {
            std::unique_ptr<Ability> ability;
            try {
                ability = abilityManager.getAbility();
                ability->printAbility();
                flagDoubleDamage = ability->use(gameField, managerShip);
            } catch (const NoAbilitiesError& e) {
                std::cout << e.what() << std::endl;
            }
            std::cout << '\n' << "Введите координаты для выстрела:" << std::endl;
            x = safeInput();
        } else if (x == -2) {
            std::cout << "Спасибо за игру!" << std::endl;
            break;
        }
        y = safeInput();
        while (true) {
            try {
                if (!gameField.checkCoordAtack(y, x)) {
                    throw OutOfBoundsAttackError();
                }
                break;
            } catch (const OutOfBoundsAttackError& e) {
                std::cout << e.what() << "\nВведите координаты повторно: ";
                x = safeInput();
                y = safeInput();
            }
        }
        if (flagDoubleDamage) {
            if (gameField.attackCell(y, x)){
                abilityManager.addAbility();
                std::cout << "Была добавлена способность" << std::endl;
            }
            flagDoubleDamage = false;
        }
        if (gameField.attackCell(y, x)){
            abilityManager.addAbility();
            std::cout << "Была добавлена способность" << std::endl;
        }
        if (managerShip.allShipDestroyed()) {
            std::cout << "Все корабли уничтожены. Спасибо за игру!" << std::endl;
            return;
        }
    }
}


ManagerShip Player::initializeManagerShip() {
    std::cout << "Введите количество кораблей для соответвующей длины:" << std::endl;
    std::vector<std::pair<int, int>> lenAndCount(4);
    for (int i = 0; i < 4; i++) {
        lenAndCount[i].first = i + 1;
        std::cout << "Для длины " << i + 1 << ": ";
        lenAndCount[i].second = safeInput();
    }
    return ManagerShip(lenAndCount);
}

GameField Player::initializeGameField() {
    std::cout << "Введите размеры поля: ";
    int width, height;
    while (true) {
        height = safeInput();
        width = safeInput();
        if (height > 0 && width > 0) {
            break;
        }
        std::cout << "Размеры поля должны быть положительными. Попробуйте снова: ";
    }
    return {width, height};
}


void Player::placeShips() {
    for (int i = 0; i < managerShip.getCountShip(); i++) {
        std::cout << "Для расстановки кораблей на поле введите координаты и ориентацию корабля длины: "
                  << managerShip.getShip(i)->getLength() << std::endl;
        int x, y, isHoriz;
        x = safeInput();
        y = safeInput();
        isHoriz = safeInput();
        gameField.placeShip(managerShip.getShip(i), y, x, isHoriz);
    }
}