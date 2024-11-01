#include "ScannerAbility.h"
#include "CustomExceptions.h"

bool Scanner::apply(GameStatus status) {
    int x, y;
    bool chek= true;
    while(chek){
        std::cout << "\nВведите координату для начала сканирования (x y): ";
        std::cin >> x >> y;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Координаты проигнорированы "<< std::endl;
            continue;
            }
        chek=false;
    }
    std::cout << "Сканер активирован!" << std::endl;
    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            CellStatus stat;
            try {
                stat = status.fieldPlayer->GetStatus(y+i,x+j);
            } catch (GameFieldException& e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            if (stat == CellStatus::Ship){
                std::cout << "Корабль найден" << std::endl;
                return false;
            }     
        }
    }
    std::cout << "Корабль не найден" << std::endl;
    return  false;
}

std::string Scanner:: toString() const{
    return "Сканер"; // Описание способности
}