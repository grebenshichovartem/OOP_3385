//кораблик
#ifndef SHIP_H
#define SHIP_H
#include "ShipSegment.h"

class Ship{
private:
    ShipSegment* segments;
    int len ;
    bool vertical;

public:
    Ship(int len, bool vertical);
    ~Ship();

    void shotSegment(int index);
    void setVertical(bool Vertical);
    SegmentStatus getStatus(int index) const;
    int getLength() const;
    bool getOrientation() const;
    bool isDestroyed() const;
};

#endif