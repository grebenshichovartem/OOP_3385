#include "ShipSegment.h"

void ShipSegment::shot(){
    if (status == SegmentStatus::Whole) {
        status = SegmentStatus::Damage;
        std::cout << "Damage"<< std::endl;
    } else if (status == SegmentStatus::Damage) {
        status = SegmentStatus::Destroyed;
        std::cout << "Destroyed" << std::endl;     
    }
    else{
        std::cout<<"Повторное уничтожение!" << std::endl;            
    }
}

void ShipSegment::setStatus(SegmentStatus segment) {  
    status = segment; // Устанавливаем статус сегмента  
}  

SegmentStatus ShipSegment::getStatus() {  
    return status; // Возвращаем текущий статус сегмента  
}  

