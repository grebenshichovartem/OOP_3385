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
    Ship(int length, bool ishorizontally);
    void setHorizontally(bool isHorisontally);
    bool getHorizontally() const;
    int getLength() const;
    SegmentStatus getSegmentStatus(int i);
    bool takeDamage(int indexsegment);
    bool isDestroyed() const;
    ~Ship();
private:
    int length;
    bool horizontally;
    std::vector<SegmentStatus> segments;
};


#endif 