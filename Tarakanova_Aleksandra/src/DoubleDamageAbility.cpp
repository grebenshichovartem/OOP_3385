#include "DoubleDamageAbility.h"
#include "CustomExceptions.h"


bool DoubleDamage::apply(GameStatus status) {
    std::cout << "Двойной урон активирован!" << std::endl;
    int x, y;
    bool chek = true;
    while(chek){
        std::cout << "\nВведите координату для выстрела (x y): ";
        std::cin >> x >> y;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Координаты проигнорированы "<< std::endl;
            continue;
        }
        chek=false;
    }
    try {
        status.fieldPlayer->attackCell(x, y);
        if(status.fieldPlayer->attackCell(x, y))
            return true;    
    } catch (GameFieldException& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return false;
}


std::string DoubleDamage:: toString() const{
    return "Двойной урон"; // Описание способности
}