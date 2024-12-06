#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include <vector>
#include <memory>
#include "Ship.hpp"
#include "FieldCell.hpp"



class GameField {
public:
    GameField(int width, int height);
    GameField();
    void placeShip(Ship*, int y, int x, int isHorizontally);
    bool attackCell(int y, int x);
    int getWidth() const;
    int getHeight() const;
    Ship* getShip(int y, int x) const;
    FieldCell* getFieldCell(int y, int x) const;
    int getCellIndex(int y, int x) const;
    SegmentStatus getStatusShipCell(int y, int x) const;
    CellStatus getCellStatus(int y, int x) const;
    bool checkCoordAttack(int y, int x) const;
    bool canPlaceShip(int y, int x, int length, bool isHorizontally) const;

    GameField(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(const GameField& other);
    GameField& operator=(GameField&& other) noexcept;
    ~GameField();
private:
    std::vector<std::vector<FieldCell*>> field;
    int width{}, height{};

};


#endif