#include "AbilityManager.h"
#include "CustomExceptions.h"

// Основная функция программы
int main() {
    system("chcp 65001");

    // Создание объекта GameField
    int width, height;
    std::cout << "Введите размеры поля (ширина длина): ";
    std::cin >> width >> height;
    GameField gameField(width, height);


    // Создание объекта ShipManager
    //std::vector<std::pair<int, int>> shipSpecs = {{1,1}};
    std::vector<std::pair<int, int>> shipSpecs = {{4, 1}, {3, 2}, {2, 3}, {1, 4}};
    ShipManager shipManager(shipSpecs);

    // Расстановка кораблей на поле
    int x, y;
    char orientation;
    bool Vertical = true;

    std::cout << "Расстановка кораблей:" << std::endl;
    for (int i=0; i<shipManager.getShipsCount(); i++) {
        bool placed = false;
        while (!placed) {
            std::cout << "Введите координаты для " << shipManager.getShip(i)->getLength() << "-сегментного корабля (x y): ";
            std::cin >> x >> y;
            if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Координаты проигнорированы "<< std::endl;
            continue;
            }
            if(shipManager.getShip(i)->getLength()!= 1){
                std::cout << "Введите его ориентацию: 1 - для вертикального, 0 - для горизонтального ";
                std::cin >> orientation;
                if(orientation=='0' || orientation=='1')
                    Vertical=(bool)orientation;
                else{
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Координаты проигнорированы "<< std::endl;
                    continue;
                }    
            }
            shipManager.getShip(i)->setVertical( Vertical);
             try {
                gameField.placeShip(shipManager.getShip(i), x, y);
                placed = true;
            } catch (GameFieldException& e) {
                std::cout << e.what() << std::endl;
            }
            
        }
    }

    std::cout << "\nТекущее состояние поля:" << std::endl;
    gameField.printField();
    // Игра
    char input;
    int cheking;
    AbilityManager manager;
    GameStatus status(&gameField, &shipManager);
    while (true) {
        std::cout << "\nВыберите действие: 2 - для вывода текущего состояния поля, 1 - для выстрела, 0 - для применения способности ";
        std::cin >> cheking;
        switch (cheking){
        case 0:
            try {
                manager.applyFirstAvailableAbility(status);
                break;
            } catch (AbilityManagerException& e) {
                std::cout << e.what() << std::endl;
            }
        case 1:
            std::cout << "\nВведите координату для выстрела (x y): ";
            std::cin >> x >> y;
            if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Координаты проигнорированы "<< std::endl;
            continue;
            }
            try{
                if(gameField.attackCell(x, y)==true){
                        manager.addAbility();
                }
            } catch (GameFieldException& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        case 2:
            std::cout << "\nТекущее состояние поля:" << std::endl;
            gameField.printField();
            break;
        default:
            std::cout << "\nНеизвестная команда!" << std::endl;
            break;
        }
        if (shipManager.isDestroyed()) {
            std::cout << "\nПоздравляю! Вы победили!" << std::endl;
            break;
        }
    }

    return 0;
}