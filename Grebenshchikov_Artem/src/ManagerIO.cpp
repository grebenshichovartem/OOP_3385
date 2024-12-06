#include "ManagerIO.h"
#include <limits>
#include <string>
#include "BattleshipException.h"



void ManagerIO::outputMassage(const std::string& massage) const {
    std::cout << massage;
}


char ManagerIO::inputCommand() const {
    char command = 0;
    std::cin >> command;
    return command;
}


std::string ManagerIO::inputString() const {
    std::string inString;
    std::cin >> inString;
    return inString;
}


int ManagerIO::inputInt() const {
    int number;
    while (true) {
        try {
            std::cin >> number;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InvalidInputError();
            }
            return number;
        } catch (InvalidInputError& e) {
            outputMassage(e.what());
        }
    }
}


std::pair<int,int> ManagerIO::inputPairInt() const {
    std::pair<int,int> coordinates;
    coordinates.first = inputInt();
    coordinates.second = inputInt();
    return coordinates;
}


void ManagerIO::printField(const std::shared_ptr<GameField>& gameField) const {
    for (int y = 0; y < gameField->getHeight(); y++) {
        for (int x = 0; x < gameField->getWidth(); x++) {
            if (gameField->getCellStatus(y, x) == CellStatus::Empty) {
                outputMassage("[ ]");
            } else if (gameField->getStatusShipCell(y, x) == SegmentStatus::Damaged) {
                outputMassage("[&]");
            } else if (gameField->getStatusShipCell(y, x) == SegmentStatus::Destroyed) {
                outputMassage("[x]");
            } else {
                outputMassage("[" + std::to_string(gameField->getCellIndex(y, x)) + "]");
            }
        }
        outputMassage("\n");
    }
}