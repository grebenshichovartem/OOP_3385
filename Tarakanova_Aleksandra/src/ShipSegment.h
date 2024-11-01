#ifndef SHIPSegment_H
#define SHIPSegment_H
#include <iostream>

enum class SegmentStatus{
    Whole,
    Damage,
    Destroyed
};

class ShipSegment{
private:
    SegmentStatus status;
public:
    ShipSegment() : status(SegmentStatus::Whole){}
    void setStatus(SegmentStatus segment);
    SegmentStatus getStatus(); 
    void shot();
};

#endif