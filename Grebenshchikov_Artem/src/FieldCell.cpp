#include "FieldCell.hpp"



FieldCell::FieldCell(Ship* ship, CellStatus cellStatus) : ship(ship), status(cellStatus){}


void FieldCell::setShip(Ship* newShip) {
    ship = newShip;
}


void FieldCell::setStatus(CellStatus cellStatus) {
    this->status = cellStatus;
}


void FieldCell::setIndexSeg(int index) {
    indexSeg = index;
}


CellStatus FieldCell::getStatus() const {
    return status;
}


Ship* FieldCell::getShip() const {
    return ship;
}


int FieldCell::getIndexSeg() const {
    return indexSeg;
}