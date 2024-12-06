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
    int indexSeg{};
public:
    explicit FieldCell(Ship* ship = nullptr, CellStatus cellStatus = CellStatus::Empty);
    void setShip(Ship* ship);
    void setStatus(CellStatus cellStatus);
    void setIndexSeg(int index);
    CellStatus getStatus() const;
    Ship* getShip() const;
    int getIndexSeg() const;
};


#endif