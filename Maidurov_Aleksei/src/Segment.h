//
// Created by MSI Catana GF66 on 11.10.2024.
//

#ifndef SEGMENT_H
#define SEGMENT_H

enum class SegmentStatus {
    Unharmed = 2, Harmed = 1, Destroyed = 0
};

class Segment {
private:
    SegmentStatus status;

public:
    Segment();

    void takeDamage(int damage_value);

    [[nodiscard]] SegmentStatus getStatus() const;

    void printStatus() const;
};

#endif //SEGMENT_H
