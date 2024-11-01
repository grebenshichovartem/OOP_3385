#ifndef FIELD_CELL_HPP
#define FIELD_CELL_HPP

#include <memory>
#include "Ship.hpp"



enum class CellStatus {
    Unknown,
    Empty,
    Ship
};


class FieldCell{
private:
    Ship* ship;
    CellStatus status;
    int indexseg;
public:
    explicit FieldCell(Ship* ship = nullptr, CellStatus cellstatus = CellStatus::Empty);
    void setShip(Ship* ship);
    void setStatus(CellStatus cellStatus);
    void setIndexseg(int index);
    CellStatus getStatus() const;
    Ship* getShip() const;
    int getIndexseg() const;
};


#endif