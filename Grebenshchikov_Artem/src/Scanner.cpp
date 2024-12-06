#include <iostream>
#include "Scanner.h"



Scanner::Scanner(const std::shared_ptr<GameField>& gameField, const std::shared_ptr<ManagerIO>& managerIO) : weakGameField(gameField), weakManagerIO(managerIO), x(0), y(0){}


std::string Scanner::toString() {
    return "Scanner";
}


answerAbilities Scanner::use() {
    auto gameField = weakGameField.lock();
    auto managerIO = weakManagerIO.lock();
    managerIO->outputMassage("Выбрана способность Scanner - введите координаты для сканирования области 2x2\n");
    std::pair<int, int> coord;
    int counter = 0;
    while (counter < 40) {
        counter++;
        coord = managerIO->inputPairInt();
        x = coord.first;
        y = coord.second;
        if (!(x > 0 && x < (gameField->getWidth()) && y > 0 && y < (gameField->getHeight()))) {
            break;
        } else {
            managerIO->outputMassage("Ни одна клетка из области с данными координатами не лежит в поле");
        }
    }

    if (counter != 40) {
        for (int dy = 0; dy < 2; dy++) {
            for (int dx = 0; dx < 2; dx++) {
                int newX = x + dx;
                int newY = y + dy;
                if (newX < gameField->getWidth() && newY < gameField->getHeight()) {
                    if (gameField->getCellStatus(newY, newX) == CellStatus::Ship)
                        return answerAbilities::ScannerFoundShip;
                } else {
                    continue;
                }
            }
        }
    }
    return answerAbilities::ScannerNotFoundShip;
}
