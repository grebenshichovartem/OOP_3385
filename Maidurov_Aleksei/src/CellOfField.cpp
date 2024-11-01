//
// Created by MSI Catana GF66 on 14.10.2024.
//

#include "CellOfField.h"
#include "DebuggingException.h"

CellOfField::CellOfField(CellStatus status) : near_of_ship{false}, segment_ptr{nullptr} {
    if (status == CellStatus::Occupied) {
        throw DebuggingException{"The cell can't be occupied from the beginning!"};
    }
    this->status = status;
}

CellStatus CellOfField::getStatus() const { return status; }

void CellOfField::setStatus(CellStatus status) {
    if (this->status != CellStatus::Hidden && status == CellStatus::Hidden) {
        throw DebuggingException{"The cell can't become hidden!"};
    } else if (this->status == CellStatus::Occupied && status == CellStatus::Empty) {
        throw DebuggingException{"The occupied cell can't become empty!"};
    }
    this->status = status;
}

Segment *CellOfField::getSegment() { return segment_ptr; }

Segment *CellOfField::getSegment() const { return segment_ptr; }

void CellOfField::setSegment(Segment *segment_ptr) {
    if (segment_ptr == nullptr) { throw DebuggingException("Segment pointer can't be nullptr!"); }
    this->segment_ptr = segment_ptr;
}

bool CellOfField::isNearOfShip() const { return near_of_ship; }

void CellOfField::shipIsNear() { near_of_ship = true; }
