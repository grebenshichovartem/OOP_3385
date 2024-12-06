#ifndef SHIP_HPP
#define SHIP_HPP

#include <vector>



enum class SegmentStatus {
    Whole,
    Damaged,
    Destroyed
};


class Ship{
public:
    Ship(int length, bool isHorizontally);
    void setHorizontally(bool isHorizontally);
    void setSegmentStatus(int index, SegmentStatus stat);
    bool getHorizontally() const;
    int getLength() const;
    SegmentStatus getSegmentStatus(int i) const;
    bool takeDamage(int indexSegment);
    bool isDestroyed() const;
    ~Ship();
private:
    int length;
    bool horizontally;
    std::vector<SegmentStatus> segments;
};


#endif 