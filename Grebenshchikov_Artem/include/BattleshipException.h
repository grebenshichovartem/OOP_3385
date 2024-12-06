#ifndef BATTLESHIP_EXCEPTION_H
#define BATTLESHIP_EXCEPTION_H

#include <stdexcept>
#include <iostream>



class InvalidInputError : public std::runtime_error {
public:
    InvalidInputError() : std::runtime_error("Некорректный ввод. Ожидалось целое число.") {}
};


class NoAbilitiesError : public std::runtime_error {
public:
    NoAbilitiesError() : std::runtime_error("Нет доступных способностей для применения.") {}
};


class ShipPlacementError : public std::runtime_error {
public:
    ShipPlacementError() : std::runtime_error("Некорректные координаты расстановки корабля") {}
};


class OutOfBoundsAttackError : public std::runtime_error {
public:
    OutOfBoundsAttackError() : std::runtime_error("Атака выходит за границы игрового поля.") {}
};


class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& message)
            : std::runtime_error(message) {}
};


class LoadInFileException : public std::runtime_error {
public:
    explicit LoadInFileException(const std::string& message)
            : std::runtime_error(message) {}
};


#endif