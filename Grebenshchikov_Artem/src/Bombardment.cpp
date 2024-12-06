#include "Bombardment.h"
#include "random"



Bombardment::Bombardment(const std::shared_ptr<ShipManager>& shipManager, const std::shared_ptr<ManagerIO>& managerIO) : weakShipManager(shipManager), weakManagerIO(managerIO){}


std::string Bombardment::toString() {
    return "Bombardment";
}


answerAbilities Bombardment::use() {
    auto shipManager = weakShipManager.lock();
    auto managerIO = weakManagerIO.lock();
    managerIO->outputMassage("Была выбрана способность Bombardment\n");
    bool bombSuccess = true;
    while (bombSuccess) {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, shipManager->getShipsCount() - 1);

        Ship *targetShip = shipManager->getShip(distribution(generator));
        std::uniform_int_distribution<int> distribution2(0, targetShip->getLength() - 1);
        int lenIndex = distribution2(generator);
        if (targetShip->getSegmentStatus(lenIndex) != SegmentStatus::Destroyed) {
            if (targetShip->takeDamage(lenIndex))
                return answerAbilities::BombardmentDestroyedShip;
            bombSuccess = false;
        }
    }
    return answerAbilities::BombardmentSuccess;
}