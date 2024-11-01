//
// Created by MSI Catana GF66 on 14.10.2024.
//

#ifndef CELLOFFIELD_H
#define CELLOFFIELD_H

#include "Ship.h"

enum class CellStatus {
    Hidden, Empty, Occupied
};

class CellOfField {
private:
    CellStatus status;
    bool near_of_ship;
    Segment *segment_ptr;

public:
    explicit CellOfField(CellStatus status);

    [[nodiscard]] CellStatus getStatus() const;

    void setStatus(CellStatus status);

    [[nodiscard]] Segment *getSegment();

    [[nodiscard]] Segment *getSegment() const;

    void setSegment(Segment *segment_ptr);

    [[nodiscard]] bool isNearOfShip() const;

    void shipIsNear();
};


#endif //CELLOFFIELD_H
