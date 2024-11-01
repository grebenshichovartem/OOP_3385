
#ifndef GAME_FIELD_H  
#define GAME_FIELD_H  

#include "ShipManager.h"  
#include <map>  
#include <stdexcept>  
#include <iostream>  

enum class CellStatus {  
    Unknown, // неизвестно  
    Empty,   // свободно  
    Ship     // занято  
};  

class GameField {  
private:  
    CellStatus** field; // клетки  
    int width;  
    int height;  
    std::map<std::pair<int, int>, Ship*> shipPositions;  
    static GameField* instance_;

    void allocateMemory(int w, int h);
    void deallocateMemory();    

public:  
    GameField(int width, int height);  
    ~GameField();
    GameField(const GameField& other);
    GameField& operator=(const GameField& other);  //копирование
    GameField(GameField&& other)noexcept;
    GameField& operator=(GameField&& other) noexcept; //перемещение
    void placeShip(Ship* ship, int x, int y);  
    bool attackCell(int x, int y);  
    void printField() const;  
    bool Chekship(int x, int y, int len, bool Vertical);
    CellStatus GetStatus(int x , int y) const; // Метод получения статуса клетки  
};  

#endif