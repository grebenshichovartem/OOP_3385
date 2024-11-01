#include "FieldCell.hpp"



FieldCell::FieldCell(Ship* ship, CellStatus status) : ship(ship), status(status){}


void FieldCell::setShip(Ship* ship) {
    this->ship = ship;
}


void FieldCell::setStatus(CellStatus cellStatus) {
    this->status = cellStatus;
}


void FieldCell::setIndexseg(int index) {
    indexseg = index;
}


CellStatus FieldCell::getStatus() const {
    return status;
}


Ship* FieldCell::getShip() const {
    return ship;
}


int FieldCell::getIndexseg() const {
    return indexseg;
}