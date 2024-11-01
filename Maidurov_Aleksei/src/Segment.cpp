//
// Created by MSI Catana GF66 on 11.10.2024.
//

#include <iostream>
#include "Segment.h"
#include "DebuggingException.h"

Segment::Segment() : status{SegmentStatus::Unharmed} {
}

void Segment::takeDamage(int damage_value) {
    if (damage_value != 1 && damage_value != 2) {
        throw DebuggingException{"Invalid damage value!"};
    }
    int raw_status{static_cast<int>(status) - damage_value};
    status = static_cast<SegmentStatus>(raw_status < 0 ? 0 : raw_status);
}

SegmentStatus Segment::getStatus() const { return status; }

void Segment::printStatus() const {
    switch (status) {
        case SegmentStatus::Unharmed:
            std::cout << "Unharmed\n";
            break;
        case SegmentStatus::Harmed:
            std::cout << "Harmed\n";
            break;
        case SegmentStatus::Destroyed:
            std::cout << "Destroyed\n";
    }
}
