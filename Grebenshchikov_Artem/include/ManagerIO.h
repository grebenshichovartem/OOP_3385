#ifndef OOP_MANAGER_IO_H
#define OOP_MANAGER_IO_H

#include "GameField.hpp"
#include <iostream>



class ManagerIO{
public:
    void printField(const std::shared_ptr<GameField>& gameField) const;
    std::string inputString() const;
    int inputInt() const;
    char inputCommand() const;
    void outputMassage(const std::string& massage) const;
    std::pair<int,int> inputPairInt() const;
};


#endif
