#include <random>
#include "GameEntities.h"
#include <map>
#include "BattleshipException.h"


GameEntities::GameEntities(){
    managerIO = std::make_shared<ManagerIO>();
    gameFlags = std::make_shared<GameFlags>();
}


std::shared_ptr<ManagerIO> GameEntities::getManagerIO() const { return managerIO; }
void GameEntities::setManagerIO(const std::shared_ptr<ManagerIO>& mgrIO) { managerIO = mgrIO; }

std::shared_ptr<GameFlags> GameEntities::getGameFlags() const { return gameFlags; }
void GameEntities::setGameFlags(const std::shared_ptr<GameFlags>& gmFlags) { this->gameFlags = gmFlags; }

std::shared_ptr<GameField> GameEntities::getFieldPlayer() const { return fieldPlayer; }
void GameEntities::setFieldPlayer(const std::shared_ptr<GameField>& fldPlayer) { this->fieldPlayer = fldPlayer; }

std::shared_ptr<GameField> GameEntities::getFieldEnemy() const { return fieldEnemy; }
void GameEntities::setFieldEnemy(const std::shared_ptr<GameField>& fldEnemy) { this->fieldEnemy = fldEnemy; }

std::shared_ptr<ShipManager> GameEntities::getShipManagerPlayer() const { return shipManagerPlayer; }
void GameEntities::setShipManagerPlayer(const std::shared_ptr<ShipManager>& shpManagerPlayer) { this->shipManagerPlayer = shpManagerPlayer; }

std::shared_ptr<ShipManager> GameEntities::getShipManagerEnemy() const { return shipManagerEnemy; }
void GameEntities::setShipManagerEnemy(const std::shared_ptr<ShipManager>& shpManagerEnemy) { this->shipManagerEnemy = shpManagerEnemy; }

std::shared_ptr<AbilityManager> GameEntities::getAbilityManager() const { return abilityManager; }
void GameEntities::setAbilityManager(const std::shared_ptr<AbilityManager>& abltyManager) { this->abilityManager = abltyManager; }


std::istream& operator >> (std::istream& in, GameEntities& gameEntities) {
    int fieldWidth, fieldHeight;
    if (!(in >> fieldWidth >> fieldHeight)) {
        throw LoadInFileException("Ошибка чтения размеров поля");
    }

    if (fieldWidth <= 0 || fieldHeight <= 0) {
        throw LoadInFileException("Неверные размеры поля");
    }

    std::shared_ptr<GameField> fieldPlayer = std::make_shared<GameField>(fieldWidth, fieldHeight);
    std::shared_ptr<GameField> fieldEnemy = std::make_shared<GameField>(fieldWidth, fieldHeight);

    std::shared_ptr<ShipManager> shipManagerPlayer = std::make_shared<ShipManager>();
    for (int y = 0; y < fieldPlayer->getHeight(); y++) {
        for (int x = 0; x < fieldPlayer->getWidth(); x++) {

            int cellStatus, indexSeg, horizontally, length, segmentStatus;

            if (!(in >> cellStatus)) {
                throw LoadInFileException("Ошибка чтения статуса клетки поля");
            }

            switch (cellStatus) {
                case 0:
                    fieldPlayer->getFieldCell(y, x)->setStatus(CellStatus::Unknown);
                    break;
                case 1:
                    fieldPlayer->getFieldCell(y, x)->setStatus(CellStatus::Empty);
                    break;
                case 2:
                    fieldPlayer->getFieldCell(y, x)->setStatus(CellStatus::Ship);

                    if (!(in >> length)) {
                        throw LoadInFileException("Ошибка чтения длины корабля");
                    }

                    if (length > 4 || length < 1) {
                        throw LoadInFileException("Неверная длина корабля");
                    }

                    if (!(in >> indexSeg)) {
                        throw LoadInFileException("Ошибка чтения индекса сегмента корабля в данной клетке");
                    }

                    if (indexSeg >= length || indexSeg < 0) {
                        throw LoadInFileException("Неверный индекс сегмента корабля в данной клетке");
                    }

                    if (indexSeg == 0) {
                        if (!(in >> horizontally)) {
                            throw LoadInFileException("Ошибка чтения ориентации корабля");
                        }

                        shipManagerPlayer->registerShip(std::make_pair(length, 1));
                        Ship* ship = shipManagerPlayer->getShip(shipManagerPlayer->getShipsCount() - 1);
                        ship->setHorizontally(horizontally > 0);
                        if (fieldPlayer->canPlaceShip(y, x, length, horizontally > 0)) {
                            throw LoadInFileException("Невозможно поставить корабль данным образом");
                        }
                        for (int i = 0; i < length; ++i) {
                            int checkX = x + (horizontally ? i : 0);
                            int checkY = y + (horizontally ? 0 : i);
                            fieldPlayer->getFieldCell(checkY, checkX)->setShip(ship);
                            fieldPlayer->getFieldCell(checkY, checkX)->setIndexSeg(i);
                            if (!(in >> segmentStatus)) {
                                throw LoadInFileException("Ошибка чтения статуса сегмента корабля");
                            }

                            ship->setSegmentStatus(i, static_cast<SegmentStatus>(segmentStatus));
                        }
                    }
                    break;
                default:
                    throw LoadInFileException("Неверный статус клетки поля");
            }
        }
    }

    std::shared_ptr<ShipManager> shipManagerEnemy = std::make_shared<ShipManager>();
    for (int y = 0; y < fieldEnemy->getHeight(); y++) {
        for (int x = 0; x < fieldEnemy->getWidth(); x++) {

            int cellStatus, indexSeg, horizontally, length, segmentStatus;

            if (!(in >> cellStatus)) {
                throw LoadInFileException("Ошибка чтения статуса клетки поля");
            }

            switch (cellStatus) {
                case 0:
                    fieldEnemy->getFieldCell(y, x)->setStatus(CellStatus::Unknown);
                    break;
                case 1:
                    fieldEnemy->getFieldCell(y, x)->setStatus(CellStatus::Empty);
                    break;
                case 2:
                    fieldEnemy->getFieldCell(y, x)->setStatus(CellStatus::Ship);

                    if (!(in >> length)) {
                        throw LoadInFileException("Ошибка чтения длины корабля");
                    }

                    if (length > 4 || length < 1) {
                        throw LoadInFileException("Неверная длина корабля");
                    }

                    if (!(in >> indexSeg)) {
                        throw LoadInFileException("Ошибка чтения индекса сегмента");
                    }

                    if (indexSeg >= length || indexSeg < 0) {
                        throw LoadInFileException("Неверный индекс сегмента");
                    }

                    if (indexSeg == 0) {
                        if (!(in >> horizontally)) {
                            throw LoadInFileException("Ошибка чтения ориентации корабля");
                        }

                        shipManagerEnemy->registerShip(std::make_pair(length, 1));
                        Ship* ship = shipManagerEnemy->getShip(shipManagerEnemy->getShipsCount() - 1);
                        ship->setHorizontally(horizontally > 0);
                        if (fieldEnemy->canPlaceShip(y, x, length, horizontally > 0)) {
                            throw LoadInFileException("Невозможно поставить корабль данным образом");
                        }
                        for (int i = 0; i < length; ++i) {
                            int checkX = x + (horizontally ? i : 0);
                            int checkY = y + (horizontally ? 0 : i);
                            fieldEnemy->getFieldCell(checkY, checkX)->setShip(ship);
                            fieldEnemy->getFieldCell(checkY, checkX)->setIndexSeg(i);
                            if (!(in >> segmentStatus)) {
                                throw LoadInFileException("Ошибка чтения статуса сегмента корабля");
                            }

                            ship->setSegmentStatus(i, static_cast<SegmentStatus>(segmentStatus));
                        }
                    }
                    break;
                default:
                    throw LoadInFileException("Неверный статус клетки поля");
            }
        }
    }

    int abilityCount;
    if (!(in >> abilityCount)) {
        throw LoadInFileException("Ошибка чтения количестве способностей");
    }

    if (abilityCount < 0) {
        throw LoadInFileException("Некорректное значения количества способностей");
    }

    std::shared_ptr<AbilityManager> abilityManager = std::make_shared<AbilityManager>(fieldEnemy, shipManagerEnemy, gameEntities.managerIO);
    for (int j = 0; j < 3; j++) {
        abilityManager->getAbility();
    }
    for (int i = 0; i < abilityCount; ++i) {
        std::string abilityType;

        if (!(in >> abilityType)) {
            throw LoadInFileException("Ошибка чтения типа способности");
        }

        try {
            auto ability = abilityManager->createAbility(abilityType);
            if (!ability) {
                throw LoadInFileException("Некорректный тип способности");
            }
            abilityManager->setAbility(ability);
        } catch (const std::exception& e) {
            throw LoadInFileException("Ошибка добавления способности:");
        }
    }

    gameEntities.fieldPlayer = std::move(fieldPlayer);
    gameEntities.fieldEnemy = std::move(fieldEnemy);
    gameEntities.shipManagerPlayer = std::move(shipManagerPlayer);
    gameEntities.shipManagerEnemy = std::move(shipManagerEnemy);
    gameEntities.abilityManager = std::move(abilityManager);
    gameEntities.managerIO = std::make_shared<ManagerIO>();
    gameEntities.gameFlags = std::make_shared<GameFlags>();

    return in;
}


std::ostream& operator<<(std::ostream& os, const GameEntities& gameEntities) {
    os << gameEntities.fieldPlayer->getWidth() << " " << gameEntities.fieldPlayer->getHeight() << std::endl;

    for (int y = 0; y < gameEntities.fieldPlayer->getHeight(); y++) {
        for (int x = 0; x < gameEntities.fieldPlayer->getWidth(); x++) {
            switch (gameEntities.fieldPlayer->getCellStatus(y, x)) {
                case CellStatus::Unknown:
                    os << 0 << ' ';
                    break;
                case CellStatus::Empty:
                    os << 1 << ' ';
                    break;
                case CellStatus::Ship:
                    os << '\n' << 2 << ' ';
                    os << gameEntities.fieldPlayer->getShip(y, x)->getLength() << ' ';
                    os << gameEntities.fieldPlayer->getCellIndex(y, x) << ' ';
                    if (gameEntities.fieldPlayer->getCellIndex(y, x) == 0) {
                        os << gameEntities.fieldPlayer->getShip(y, x)->getHorizontally() << ' ';
                        for (int i = 0; i < gameEntities.fieldPlayer->getShip(y, x)->getLength(); i++) {
                            int checkX = x + (gameEntities.fieldPlayer->getShip(y, x)->getHorizontally() ? i : 0);
                            int checkY = y + (gameEntities.fieldPlayer->getShip(y, x)->getHorizontally() ? 0 : i);

                            switch (gameEntities.fieldPlayer->getStatusShipCell(checkY, checkX)) {
                                case SegmentStatus::Whole:
                                    os << 0 << ' ';
                                    break;
                                case SegmentStatus::Damaged:
                                    os << 1 << ' ';
                                    break;
                                case SegmentStatus::Destroyed:
                                    os << 2 << ' ';
                                    break;
                            }
                        }
                        os << '\n';
                        break;
                    }
            }
        }
    }
    os << '\n' << '\n';

    for (int y = 0; y < gameEntities.fieldEnemy->getHeight(); y++) {
        for (int x = 0; x < gameEntities.fieldEnemy->getWidth(); x++) {
            switch (gameEntities.fieldEnemy->getCellStatus(y, x)) {
                case CellStatus::Unknown:
                    os << 0 << ' ';
                    break;
                case CellStatus::Empty:
                    os << 1 << ' ';
                    break;
                case CellStatus::Ship:
                    os << '\n' << 2 << ' ';
                    os << gameEntities.fieldEnemy->getShip(y, x)->getLength() << ' ';
                    os << gameEntities.fieldEnemy->getCellIndex(y, x) << ' ';
                    if (gameEntities.fieldEnemy->getCellIndex(y, x) == 0) {
                        os << gameEntities.fieldEnemy->getShip(y, x)->getHorizontally() << ' ';
                        for (int i = 0; i < gameEntities.fieldEnemy->getShip(y, x)->getLength(); ++i) {
                            int checkX = x + (gameEntities.fieldEnemy->getShip(y, x)->getHorizontally() ? i : 0);
                            int checkY = y + (gameEntities.fieldEnemy->getShip(y, x)->getHorizontally() ? 0 : i);

                            switch (gameEntities.fieldEnemy->getStatusShipCell(checkY, checkX)) {
                                case SegmentStatus::Whole:
                                    os << 0 << ' ';
                                    break;
                                case SegmentStatus::Damaged:
                                    os << 1 << ' ';
                                    break;
                                case SegmentStatus::Destroyed:
                                    os << 2 << ' ';
                                    break;
                            }
                        }
                    }
                    os << '\n';
                    break;
            }
        }
    }
    os << '\n';
    
    // Вывод способностей
    os << gameEntities.abilityManager->getAbilityCount() << std::endl;
    for (int i = 0; i < gameEntities.abilityManager->getAbilityCount(); i++) {
        auto ability = gameEntities.abilityManager->getAbility(i);
        if (ability) {
            os << ability->toString() << std::endl;
        } else {
            os << -1 << std::endl;
        }
    }
    return os;
}