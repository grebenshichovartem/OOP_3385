#include "GameField.h"
#include "CustomExceptions.h"

void GameField::allocateMemory(int w, int h) {  
    field = new CellStatus*[h];  
    for (int i = 0; i < h; ++i) {  
        field[i] = new CellStatus[w];  
        std::fill(field[i], field[i] + w, CellStatus::Unknown); // Инициализация статуса клеток  
    }  
} 

void GameField::deallocateMemory() {  
    for (int i = 0; i < height; ++i) {  
        delete[] field[i];  
    }  
    delete[] field;  
}  

GameField::GameField(int width, int height) : width(width), height(height) {
    if (width <= 0 || height <= 0) {  
            throw std::invalid_argument("Длина и ширина должны быть положительными");  
    }  
    allocateMemory(width, height);  
}  


GameField::~GameField() {
    for (int i = 0; i < height; i++) {
        delete[] field[i];
    }
    delete[] field;
}

GameField::GameField(const GameField& other) : width(other.width), height(other.height), field(nullptr) {  
    allocateMemory(other.width, other.height); // выделяем память  
    for (int i = 0; i < height; ++i) {  
        std::copy(other.field[i], other.field[i] + width, field[i]); // глубокое копирование статуса клеток  
    }  
    shipPositions = other.shipPositions; // копируем позиции кораблей  
} 

 GameField& GameField::operator=(const GameField& other) {  
    if (this == &other) return *this; // Защита от самоприсваивания  

    // Освобождаем память  
    deallocateMemory();  

    // Копируем значения  
    width = other.width;  
    height = other.height;  

    allocateMemory(other.width, other.height);  
    for (int i = 0; i < height; ++i) {  
        std::copy(other.field[i], other.field[i] + width, field[i]);  
    }  
    shipPositions = other.shipPositions;  

    return *this;  
}  

GameField::GameField(GameField&& other) noexcept :  
    field(other.field), width(other.width), height(other.height), shipPositions(std::move(other.shipPositions)) {  
    other.field = nullptr; // Сброс указателя в nullptr  
    other.width = 0;  
    other.height = 0;  
} 

GameField& GameField::operator=(GameField&& other) noexcept {  
    if (this == &other) return *this; // Защита от самоприсваивания  

    // Освобождаем память  
    deallocateMemory();  

    // Перемещаем значения  
    field = other.field;  
    width = other.width;  
    height = other.height;  
    shipPositions = std::move(other.shipPositions);  

    other.field = nullptr; // Сброс указателя в nullptr  
    other.width = 0;  
    other.height = 0;  

    return *this;  
}  

bool GameField :: Chekship( int x, int y, int len,  bool Vertical){
    if(y >= height || y < 0 || x >= width || x < 0 )
        return false;
    int dy, dx;
    if (Vertical) {
        if(y + len > height)
            return false;
    }
    else{
        if (x + len > width)
            return false;
    }
    for (int i = -1; i <= len; i++) {
        for (int j = -1; j <= 1; j++){
            if (Vertical){
                dy = i;
                dx = j;
            }
            else{
                dy = j;
                dx = i;
            }
            if((y+dy >= 0) && (x+dx >= 0) && (y+dy < height) && (x+dx < width))
                if (field[y + dy][x+dx] != CellStatus::Unknown) 
                    return false;   
        }
    }   
    return true;   
}

void GameField::placeShip(Ship* ship, int x, int y) {
    if (Chekship(x, y, ship->getLength(),  ship->getOrientation())) {
        for (int i = 0; i < ship->getLength(); i++) {
            if (ship->getOrientation()){
                field[y + i][x] = CellStatus::Ship;
                shipPositions.emplace(std::make_pair(x, y + i), ship); // Сохраняем позицию сегмента  
            }
            else{
                field[y][x + i] = CellStatus::Ship;
                shipPositions.emplace(std::make_pair(x + i, y), ship); // Сохраняем позицию сегмента  
            }
        }
    }         
    else{
        throw GameFieldException("Неверное расположение корабля");
    }
}

bool GameField::attackCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw GameFieldException("Выстрел за границы поля");
    }

    if (field[y][x] == CellStatus::Ship) { // Если клетка содержит корабль  
        // Создаем пару ключей координат  
        std::pair<int, int> coords(x, y);  

        // Проверяем, есть ли корабль по этим координатам  
        auto it = shipPositions.find(coords); 

        if (it != shipPositions.end()) {  
            Ship* targetShip = it->second; // Получаем указатель на атакуемый корабль  
            if(targetShip->isDestroyed())
                return true;
            // Определяем индекс сегмента в корабле  
            int segmentIndex = -1; 
            while(field[y][x] == CellStatus::Ship ) {
                if (targetShip->getOrientation()) 
                    y--;
                else
                    x--;
                segmentIndex++;
                if(y<0 || x<0)
                    break;
            }
            it->second->shotSegment(segmentIndex);
            
            if(targetShip->isDestroyed()){
                std::cout << "Корабль уничтожен!"<< std::endl;
                return true; 
            }   
        }  
    }else
        std::cout << "Промах!";
    return false;
}  

void GameField::printField() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (field[y][x]) {
                case CellStatus::Unknown:
                    std::cout << "? ";
                    break;
                case CellStatus::Empty:
                    std::cout << "~ ";
                    break;
                case CellStatus::Ship:
                    int i=x;
                    int j=y;
                    std::pair<int, int> coords(i, j);  

                    auto it = shipPositions.find(coords); 
                    if (it != shipPositions.end()) {  
                        Ship* targetShip = it->second; // Получаем указатель на атакуемый корабль  
                         // Определяем индекс сегмента в корабле  
                        int segmentIndex = -1; 
                        while(field[j][i] == CellStatus::Ship ) {
                            if (targetShip->getOrientation()) 
                                j--;
                            else
                                i--;
                            segmentIndex++;
                            if(j<0 || i<0)
                                break;
                        }
                        auto status = it->second->getStatus(segmentIndex);
                        if(status == SegmentStatus::Destroyed){
                            std::cout << "X ";
                            break;
                        }
                        if(status == SegmentStatus::Damage){
                            std::cout << "D ";
                            break;
                        }
                        else{
                            std::cout << "S ";
                            break;
                        }
                    }
            }
        }
        std::cout << "\n";
    }
}


                    
                           

// Метод получения статуса клетки  
CellStatus GameField::GetStatus(int x, int y) const {  
    if (x < 0 || x >= width || y < 0 || y >= height) {  
        throw GameFieldException("Координаты вне поля");
    }  
    return field[y][x];  
}